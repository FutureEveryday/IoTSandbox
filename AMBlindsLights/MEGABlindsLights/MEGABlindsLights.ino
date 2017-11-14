#include <FastLED.h>

#define NUM_LEDSAmbient 242
#define DATA_PINAmbient 7
CRGB ledsAmbient[NUM_LEDSAmbient];
#define NUM_LEDSDirLiving 14
#define DATA_PINDirLiving 6
CRGB ledsDirLiving[NUM_LEDSDirLiving];
#define NUM_LEDSDirSleep 5
#define DATA_PINDirSleep 3
CRGB ledsDirSleep[NUM_LEDSDirSleep];

#define NR_BYTES 21
byte byteArray[NR_BYTES];
byte inputByteArray[NR_BYTES];

boolean newVal = false;

//VARIABLES NECESSARY FOR THIS ARDUINO
int encValue;
int middle;
int brightness;
int valueSliderAmbient;
int valuePotAmbient;
int ambientOnState;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PINAmbient>(ledsAmbient, NUM_LEDSAmbient);
  FastLED.addLeds<NEOPIXEL, DATA_PINDirLiving>(ledsDirLiving, NUM_LEDSDirLiving);
  FastLED.addLeds<NEOPIXEL, DATA_PINDirSleep>(ledsDirSleep, NUM_LEDSDirSleep);
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.setTimeout(5);
  Serial3.begin(115200);
}

void loop() {
  if (newVal) {
    for (int i = 0; i < NR_BYTES; i++) {
      Serial.print(byteArray[i]);
      Serial.print('\t');
    }
    Serial.println();
    newVal = false;
  }

//VARIABLES NECESSARY FOR THIS ARDUINO
  //AMBIENT TILE
ambientOnState = byteArray[0];
encValue = byteArray[1];
middle = byteArray[2];
brightness = byteArray[0];
valueSliderAmbient = byteArray[0];
valuePotAmbient = byteArray[0];
ambientOnState = byteArray[0];

  ambientLightControl();
  motorControl();
}

void serialEvent1() {
  if (Serial3.available() >= NR_BYTES){
    if(Serial3.read() == 65) {
      //if this is true then we have received the complete string
      Serial3.readBytes(inputByteArray, NR_BYTES-1);
      //  Print values for review
      for (int i = 0; i < NR_BYTES-1; i++)  byteArray[i] = inputByteArray[i];
      brightness = byteArray[0];
      newVal = true;
    }
  }
}
