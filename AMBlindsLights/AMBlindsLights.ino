/*
  This Arduino receives the 15-byte long array from the interface over USB and controls the lights and blinds of the house.
  It also transmits the array to the other Arduino (Audio and Television, now MediaDuino) over Serial TX2.
*/

/*
  Byte array in order of incoming (w/o startbyte "A", or "65")
  AMBIENT LIGHTS
  0: Ambient lighting ON/OFF
  1: Ambient lighting POSITION
  2: Ambient lighting WIDTH
  3: Ambient lighting BRIGHTNESS
      BLINDS
      4: Blinds DIRECTION & SPEED
          AUDIO  
          5: Audio ON/OFF
          6: Audio ROOM SELECT
          7: Audio GENRE SELECT
          8: Audio VOLUME
              TELEVISION
              9: Television ON/OFF
              10: Television CHANNEL SELECT
              11: Television VOLUME
                  DIRECTIONAL LIGHTS
                  12: Directional lighting LIVING ON/OFF
                  13: Directional lighting BEDROOM ON/OFF
*/

#define NR_BYTES 21                     // Amount of bytes to receive over USB
byte byteArray[NR_BYTES];
byte inputByteArray[NR_BYTES];

boolean fullStringReceived = false;     // Check value that prevents loop from running until full array of bytes has been received

unsigned long lastTime;

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

// LED CONTROLS
#define NUM_LEDSAmbient 72              // The amount of LEDs in the ambient lighting (in house 242)
#define DATA_PINAmbient 5               // The output pin that controls the ambient lighting (should be 5)
CRGB ledsAmbient[NUM_LEDSAmbient];
#define NUM_LEDSDirLiving 14            // The amount of LEDs in the direct lighting > living room
#define DATA_PINDirLiving 4             // The output pin that controls the the direct lighting > living room
CRGB ledsDirLiving[NUM_LEDSDirLiving];
#define NUM_LEDSDirSleep 14              // The amount of LEDs in the direct lighting > bedroom (CHECK IF MAKING THIS 14 PRESENTS A PROBLEM)
#define DATA_PINDirSleep 6              // The output pin that controls the the direct lighting > bedroom
CRGB ledsDirSleep[NUM_LEDSDirSleep];

// MOTOR CONTROLS
int stopButtonLeft = 52;                // Assign pin 52 to stop button left
int stopButtonRight = 53;               // Assign pin 53 to stop button right

int motorLeft = 2;                      // Assign pin 2 to H-Bridge CW
int motorRight = 3;                     // Assign pin 3 to H-Bridge CCW
int PWMSpeed = 7;                       // Assign pin 7 to PWM input H-Bridge
int turningDirection;                   // Blinds go left or right

boolean maxPosLeft = false;             // Make boolean for max position left
boolean maxPosRight = false;            // Make boolean for max position right

// VARIABLES NECESSARY FOR THIS ARDUINO
// AMBIENT LIGHTS
int encValue;                           // Position of the ambient lighting
int middle;                             // Indicates the middle of the lit part
int brightness;                         // Brightness of the light
int range;                              // Width of the lightarray
int ambientOnState;

// DIRECTIONAL LIGHTS
int livingRoom;                         // Living room lights ON or OFF
int bedRoom;                            // Bedroom lights ON or OFF

// BLINDS
int valueBlinds;                        // Value used for controlling of the blinds
boolean reverse;                        // Boolean to indicate forward or backward of motor
int speed;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PINAmbient>(ledsAmbient, NUM_LEDSAmbient);
  FastLED.addLeds<NEOPIXEL, DATA_PINDirLiving>(ledsDirLiving, NUM_LEDSDirLiving);
  FastLED.addLeds<NEOPIXEL, DATA_PINDirSleep>(ledsDirSleep, NUM_LEDSDirSleep);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  Serial.begin(115200);                 // Set baudrate at which bytes are coming in from Interface
  Serial1.begin(115200);                // Set baudrate for TX1 that is sending to the MediaDuino (NOW performing as incoming data port)
  Serial1.setTimeout(5);                // Set an interval time at which Serial2 is checked
//  Serial2.begin(115200);                // Set baudrate for TX2 that is sending to the MediaDuino

  // DEFINE PINMODES FOR LIGHTS
  pinMode(DATA_PINAmbient, OUTPUT);
  pinMode(DATA_PINDirSleep, OUTPUT);
  pinMode(DATA_PINDirLiving, OUTPUT);

  FastLED.clear();

  for (int i = 0; i < NUM_LEDSAmbient; i++) {
    ledsAmbient[i] = CRGB(0, 0, 0);
  }

  for (int i = 0; i < NUM_LEDSDirLiving; i++) {
    ledsDirLiving[i] = CRGB(0, 0, 0);
  }

  for (int i = 0; i < NUM_LEDSDirSleep; i++) {
    ledsDirSleep[i] = CRGB(0, 0, 0);
  }

  FastLED.show();

  // DEFINE PINMODES FOR BLINDS
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(PWMSpeed, OUTPUT);
  pinMode(maxPosLeft, INPUT_PULLUP);
  pinMode(maxPosRight, INPUT_PULLUP);
}

void loop() {
  if (fullStringReceived) {                     // When a whole array of bytes has come in, newVal is true and prints the array
//    for (int i = 0; i < NR_BYTES; i++) {
//      Serial.print(byteArray[i]);
//      Serial.print('\t');
//    }
//    Serial.println();

    //  sendByteArray();                        // Send received byte array to AMTVAudio

    // ASSIGNING OF BYTES TO INTEGERS
    // AMBIENT LIGHTING
    ambientOnState      = byteArray[0];                          // ON or OFF               (0 or 1)
//    Serial.print(ambientOnState);
//    Serial.print(" ");
    middle              = map(byteArray[1], 0, 255, 0, NUM_LEDSAmbient);     // LOCATION                (0 - 255)
    middle = constrain(middle, 0, NUM_LEDSAmbient);
//    Serial.print(middle);
//    Serial.print(" ");
//    Serial.print(byteArray[1]);
//    Serial.print(" ");
    range               = map(byteArray[2], 0, 255, 5, 50);     // WIDTH of LIGHTS         (0 - 100)
//    Serial.print(range);
//    Serial.println(" ");
    brightness          = map(byteArray[3], 0, 255, 0, 150);     // BRIGHTNESS              (0 - 100)
//    Serial.print(brightness);
//    Serial.println(" ");

    // BLINDS
    valueBlinds         = byteArray[4];     // DIRECTION and SPEED     (0 - 255)

    // DIRECTIONAL LIGHTS
    livingRoom          = byteArray[12];
    bedRoom             = byteArray[13];

//    blindsControl();                        // Call function to control the blinds
//    directionalLights();                    // Call function to control the directional lights
    ambientLightControl();                  // Call function to control the ambient lighting

  }
  fullStringReceived = false;
}

void serialEvent1() {                     // This function receives incoming serial data over RX2 when available, but check at least 20 times/sec
  if (Serial1.available() >= NR_BYTES) {  // If data is coming in over serial1, start listening
    if (Serial1.read() == 65) {           // When value 65 has been received, continue to receive all consecutive values
      Serial1.readBytes(inputByteArray, NR_BYTES);  // Build array from incoming bytes with NR_BYTES-length
      for (int i = 0; i < NR_BYTES - 1; i++)  byteArray[i] = inputByteArray[i];
    }
    fullStringReceived = true;            // Full string is received, now go to loop
  }
}

//// Sending the byte array containing all the tile values from the interface to the receiverLight arduino via serial 1
void sendByteArray() {
  if (millis() - lastTime > 50) {
    Serial2.write(byteArray, NR_BYTES);
    lastTime = millis();
  }
}
