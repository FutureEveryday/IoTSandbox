/*
  This Arduino receives the 16-byte long array from the interface over USB and controls the lights and blinds of the house.
  It also transmits the array to the other Arduino (Audio and Television, now MediaDuino) over Serial TX2.
*/

/*
  Byte array in order of incoming (w/o startbyte "A", or "65" & startbyte "B", or 66)
  0: Startbyte "A"
  AMBIENT LIGHTS
  1: Ambient lighting ON/OFF
  2: Ambient lighting POSITION
  3: Ambient lighting WIDTH
  4: Ambient lighting BRIGHTNESS
      BLINDS
      5: Blinds DIRECTION & SPEED
          AUDIO
          6: Audio ON/OFF
          7: Audio ROOM SELECT
          8: Audio GENRE SELECT
          9: Audio VOLUME
              TELEVISION
              10: Television ON/OFF
              11: Television CHANNEL SELECT
              12: Television VOLUME
                  DIRECTIONAL LIGHTS
                  13: Directional lighting LIVING ON/OFF
                  14: Directional lighting BEDROOM ON/OFF
                      15: Endbyte "B"
*/

#define NR_BYTES 16                     // Amount of bytes to receive over USB
byte byteArray[NR_BYTES];

//lookup table which position in the byteArray contains which variable
int startByte = 0;                  // Startbyte 1 > "A"
int ambientOnOffByte = 1;           // ambientSwitch, 0 or 1, is the ambient lighting switched on or not
int ambientLocationByte = 2;        // ambientPot, a value between 0 and 255 containing the pot value (intensity) for the ambient tile
int ambientWidthByte = 3;           // ambientSlider, a value between 0 and 255 containing the slider value (range) for the ambient tile
int ambientBrightnessByte = 4;      // ambientBrightness, a value between 0 and 255 containing the potmeter value (brightness) for the ambient tile
int blindsLeftRightByte = 5;        // blindsLeftRight, an analog value that is used to determine direction and speed of blinds
int audioOnOffByte = 6;             // audioOnOff, 0 or 1, is the audio tile switched on or not
int audioLocationByte = 7;          // audioLocation, 0 or 1, music in the bedroom or in the living room
int audioGenreByte = 8;             // audioGenre, a value from 0 - 5
int audioVolumeByte = 9;            // audioVolume, a value between 0 and 255 containing the potmeter value (volume) for the audio tile
int televisionOnOffByte = 10;       // televisionOnOff, 0 or 1, is the television switched on or not
int televisionChannelByte = 11;     // televisionChannelSelect, a value from 0 - 5
int televisionVolumeByte = 12;      // televisionVolume, a value between 0 and 255 containing the potmeter value (volume) for the television tile
int directionalLightByte1 = 13;     // directionalLight, 0 or 1, light is switch on or not
int directionalLightByte2 = 14;     // directionalLight, 0 or 1, light is switch on or not
int endByte = 15;                   // Endbyte 15 > "B"

boolean fullStringReceived = false;     // Check value that prevents loop from running until full array of bytes has been received

unsigned long lastTime;                 // This is a timer used for sending byte array at regular intervals
int intervalTime = 50;

//#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

// LED CONTROLS
#define NUM_LEDSAmbient 242             // The amount of LEDs in the ambient lighting (in house 242)
#define DATA_PINAmbient 6               // The output pin that controls the ambient lighting (should be 5)
CRGB ledsAmbient[NUM_LEDSAmbient];
#define NUM_LEDSDirLiving 14            // The amount of LEDs in the direct lighting > living room
#define DATA_PINDirLiving 5             // The output pin that controls the the direct lighting > living room
CRGB ledsDirLiving[NUM_LEDSDirLiving];
#define NUM_LEDSDirSleep 14             // The amount of LEDs in the direct lighting > bedroom (CHECK IF MAKING THIS 14 PRESENTS A PROBLEM)
#define DATA_PINDirSleep 4              // The output pin that controls the the direct lighting > bedroom
CRGB ledsDirSleep[NUM_LEDSDirSleep];

// MOTOR CONTROL
int stopButtonLeft = 52;                // Assign pin 52 to stop button left
int stopButtonRight = 53;               // Assign pin 53 to stop button right

int motorLeft = 3;                      // Assign pin 2 to H-Bridge CW
int motorRight = 2;                     // Assign pin 3 to H-Bridge CCW
int PWMSpeed = 7;                       // Assign pin 7 to PWM input H-Bridge
int turningDirection;                   // Blinds go left or right

int maxPosLeft = 1;             // Make boolean for max position left
int maxPosRight = 1;            // Make boolean for max position right
boolean goBlindsLeft = false;
boolean goBlindsRight = false;

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
  Serial2.begin(115200);                // Set baudrate for TX1 that is sending to the MediaDuino (NOW performing as incoming data port)

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
  pinMode(stopButtonLeft, INPUT_PULLUP);
  pinMode(stopButtonRight, INPUT_PULLUP);
}

void loop() {
  if (fullStringReceived) {                     // When a whole array of bytes has come in, newVal is true and prints the array

    //    // Print array of bytes that was received over serial //
    //    for (int i = 0; i < NR_BYTES; i++) {
    //      Serial.print(byteArray[i]);
    //      Serial.print('\t');
    //    }
    //    Serial.println();
    //    ////////////////////////////////////////////////////////

    assignBytes();

    blindsControl();                        // Call function to control the blinds
    directionalLights();                    // Call function to control the directional lights
    ambientLightControl();                  // Call function to control the ambient lighting

    FastLED.show();                         // Show what ledstrips need to show based on input

    sendByteArray();                        // Send received byte array to AMTVAudio
  }
  fullStringReceived = false;
}

void serialEvent() {
  if (Serial.available() > 0) {
    Serial.readBytes(byteArray, NR_BYTES);

    // CHECK START AND END VALUES AS CONDITIONS TO SAY THAT FULL STRING HAS BEEN RECEIVED
    if (byteArray[0] = 65 && byteArray[15] == 66) {
      fullStringReceived = true;
    }
  }
}

//// Sending the byte array containing all the tile values from the interface to the receiverLight arduino via serial 1
void sendByteArray() {
  if (millis() - lastTime > intervalTime) {
    byteArray[startByte] = 'A';
    byteArray[endByte] = 'B';
    Serial2.write(byteArray, NR_BYTES);
    lastTime = millis();
  }
}
