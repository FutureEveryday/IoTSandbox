#include <FastLED.h>

//LIGHT INTERFACE VARIABLES
#define dataPinInterface 7                        // Pin that controls the tile LEDs on the interface
#define numLedsInterface 10                       // Amount of LEDs in the interface
CRGB ledsInterface[numLedsInterface];             // Class that controls LEDs according to CRGB reference
int lookupTableLeds[] = {6, 9, 7, 8, 5, 0, 1, 4, 3, 2}; // Array that couples the LED number of the strip to the correct tile

//SERIAL COMMUNICATION VARIABLES
// Values containing data which will be sent to the receiver arduino
#define byteArraySize 16                          // Size of the array that is sent over Serial
uint8_t byteArray[byteArraySize];                 // Array that is sent over Serial

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

//////////// DIRECT CONTROLS //////////////
//TELEVION TILE VARIABLES
#define televisionSwitchPin 10                    // Digital pin to check if television is ON or OFF
#define televisionChannelUpPin 51                 // Digital pin to check if CHANNEL UP is pressed
#define televisionChannelDownPin 49               // Digital pin to check if CHANNEL DOWN is pressed
#define televisionVolumePotPin A9                 // Analog pin that controls VOLUME of television
int televisionChannelSelected = 0;                // Integer that represents the selected channel
int lastStateTelevisionChannelUp;
int lastStateTelevisionChannelDown;

//AUDIO TILE VARIABLES
#define audioOnOffPin 39                          // ?????
#define audioLocationSwitch 41                    // Digital pin to check if audio is ON or OFF
#define audioGenreUpPin 35                        // Digital pin to check if GENRE UP is pressed
#define audioGenreDownPin 37                      // Digital pin to check if GENRE DOWN is pressed
#define audioVolumePotPin A7                      // Analog pin that controls the VOLUME of audio
int audioGenreSelected = 0;                       // Digital pin to check if CHANNEL UP is pressed
int lastStateAudioGenreDown = 0;
int lastStateAudioGenreUp = 0;
int audioSwitchPinLastState;
int audioOnOff;

//BLINDS TILE VARIABLES
#define blindsSliderPin A2                        // Analog pin to check where blinds need to go

//AMBIENT TILE VARIABLES
//encoder variables
#include<Encoder.h>                               // Encoder determines the POSITION of the ambient lighting
#define encoderPin1 20                            // Digital pin for encoder pin 1
#define encoderPin2 21                            // Digital pin for encoder pin 2
Encoder myEnc(encoderPin1, encoderPin2);          // Class "encoder" that assigns pins
long oldPosition  = -999;
int rangeConst = 0;
unsigned long lastTime;
long encValue;
//remaining variables
#define ambientSwitchPin 31                       // Digital pin to check if ambient lighting is ON or OFF
#define ambientPotPin A5                          // Analog pin that controls the BRIGHTNS of the ambient lighting
#define ambientSliderPin A3                       // Analog pin the controls the width of the ambient lighting

//DIRECTIONAL LIGHTS PINS
#define directionalLivingSwitchPin 2              // Digital pin to turn direct light living room ON or OFF
#define directionalSleepingSwitchPin 27           // Digital pin to turn direct light bedroom ON or OFF
int directionalLivingSwitchPinLastState = 0;
int directionalLightLivingOnOff = 0;              // State that represent if directional light living room is ON or OFF
int directionalSleepingSwitchPinLastState = 0;
int directionalLightSleepingOnOff = 0;            // State that represent if directional light bedroom is ON or OFF

//////////// PRESET CONTROLS (EMGERGENT FUNCTIONALITY) //////////////

//EMERGENT FUNCTIONALITY TILES VARIABLES
#define emergentAmbilightSwitchPin 53             // Digital pin to turn on MOVIE MODE (ambient lights to certain position and brightness and tv on)
int emergentAmbilightOnOff = 2;
int emergentAmbilightLastState;
#define emergentAmbilightBlindsSwitchPin 43       // Digital pin to turn on COZY DINNER (blinds and ambient lights move to certain position)
int  emergentAmbilightBlindsOnOff = 2;
int  emergentAmbilightBlindsLastState;
#define emergentTvAudioSwitchPin 45               // Digital pin to turn on TV OVER AUDIO (tv audio is heard over distributed audio system, when tv is turned on)
int emergentTvAudioOnOff = 2;
int emergentTvAudioPinLastState;
#define emergentDiscoOrganSwitchPin 33            // Digital pin to turn on DISCO (ambient lights interact with audio)
int emergentDiscoOrganOnOff = 2;
int emergentDiscoOrganLastState;

unsigned long lastTimeDisco;

//LED STRIP VARIABLES
int middle = 0;
//int range = 0;
//int warmcold = 0;
//int tmpCalc;
//int differencePixel = 0;

//  //ANALOG VARIABLES
//int sliderPinAmbient = A3;
//int valueSliderAmbient = 0;
//int potPinAmbient = A5;
//int valuePotAmbient = 0;

//DIGITAL VARIABLES
int ambientOn = 0;
int programAmbient = 23;
int ambientOnState = 0;

//DIGITAL PINS FOR CHECKING presence OF TILES
#define arrayLengthPresence 10
int pinsPresence[] = {32, 48, 30, 44, 34, 46, 42, 36, 38, 40};
int presenceCheckArray[10];

//DIGITAL PINS FOR PROGRAMMING INTERFACE
#define arrayLengthProgramming 10
int pinsProgramming[] = {52, 6, 50, 5, 29, 23, 26, 24, 22, 28};
int programmingCheckArray[10];

//ARRAY FOR LIGHTSTRIP INTERFACE
#define arrayLengthLeds 10
int ledsArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int brightness = 120;
unsigned long lastTimeProgrammingLeds;

//PROGRAMMING MODE
#define programmingPin 9
boolean programmingModeActive = false;
//These arrays are keeping track of the state change of all the programming buttons which are beneath each tile
int lastStatePins[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int pushStatePins[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
// This array stores whether the pins are involved in a active emergent functionality connection
int programmingStatePins[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//This array stores whether the emergent functionality tiles are programmed or not 0:Tv/Audio 1:Ambilight 2:Ambilight + Blinds 3:DiscoOrgan
boolean connectionsTiles[] = {0, 0, 0, 0};
boolean fadeIn = true;

void setup() {
  //Add neopixel strip, light beneath interface tiles
  FastLED.addLeds<NEOPIXEL, dataPinInterface>(ledsInterface, numLedsInterface);
  //Communication to computer
  Serial.begin(115200);
  //  //Communication to receiverDuinoLight arduino
  Serial1.begin(115200);
  //  //Communicating with receiverDuinoMedia
  //  Serial2.begin(115200);

  //PINMODES
  //ambient
  pinMode(ambientSwitchPin, INPUT);
  digitalWrite(ambientSwitchPin, HIGH);
  pinMode(ambientPotPin, INPUT);
  pinMode(ambientSliderPin, INPUT);

  // Proramming pin
  pinMode(programmingPin, INPUT);
  digitalWrite(programmingPin, HIGH);

  // blinds
  pinMode(blindsSliderPin, INPUT);

  //Audio
  pinMode(audioOnOffPin, INPUT);
  digitalWrite(audioOnOffPin, HIGH);
  pinMode(audioLocationSwitch, INPUT);
  digitalWrite(audioLocationSwitch, HIGH);
  pinMode(audioGenreUpPin, INPUT);
  digitalWrite(audioGenreUpPin, HIGH);
  pinMode(audioGenreDownPin, INPUT);
  digitalWrite(audioGenreDownPin, HIGH);
  pinMode(audioVolumePotPin, INPUT);

  //Directional light
  pinMode(directionalLivingSwitchPin, INPUT);
  digitalWrite(directionalLivingSwitchPin, HIGH);
  pinMode(directionalSleepingSwitchPin, INPUT);
  digitalWrite(directionalSleepingSwitchPin, HIGH);

  //Television
  pinMode(televisionSwitchPin, INPUT);
  digitalWrite(televisionSwitchPin, HIGH);
  pinMode(televisionChannelUpPin, INPUT);
  digitalWrite(televisionChannelUpPin, HIGH);
  pinMode(televisionChannelDownPin, INPUT);
  digitalWrite(televisionChannelDownPin, HIGH);
  pinMode(televisionVolumePotPin, INPUT);

  //Directional light tiles
  pinMode(directionalLivingSwitchPin, INPUT);
  digitalWrite(directionalLivingSwitchPin, HIGH);
  pinMode(directionalSleepingSwitchPin, INPUT);
  digitalWrite(directionalSleepingSwitchPin, HIGH);

  //Emergent switch pins
  pinMode(emergentAmbilightSwitchPin, INPUT);
  digitalWrite(emergentAmbilightSwitchPin, HIGH);
  pinMode(emergentAmbilightBlindsSwitchPin, INPUT);
  digitalWrite(emergentAmbilightBlindsSwitchPin, HIGH);
  pinMode(emergentTvAudioSwitchPin, INPUT);
  digitalWrite(emergentTvAudioSwitchPin, HIGH);
  pinMode(emergentDiscoOrganSwitchPin, INPUT);
  digitalWrite(emergentDiscoOrganSwitchPin, HIGH);

  // Set all presence pins to input and engage the pullup resistors
  for (int i = 0; i < arrayLengthPresence; i++) {
    pinMode(pinsPresence[i], INPUT);
    digitalWrite(pinsPresence[i], HIGH);
  }
  for (int i = 0; i < arrayLengthProgramming; i++) {
    pinMode(pinsProgramming[i], INPUT);
    digitalWrite(pinsProgramming[i], HIGH);
  }
}

void loop() {

  byteArray[startByte] = 'A';               // Use a double "check byte", i.e. A and B as indicators for the Processing sketch to start receiving the rest of the bytes
  byteArray[endByte]   = 'B';               // "A" is the start byte and "B" is the end byte
    
  // Check whether tiles are currently present or not
  checkProgrammingAndPresence();    // This function checks which tiles are present and lights the tile LEDs accordingly

  // Check if programming mode is currently active
  checkProgrammingMode();           // This function checks if programming mode is enabled, if so the LEDs act accordingly (pulsating)

  //Tiles
  ambientTile();                    // Calls the function for the ambient tile
  directionalLightTiles();          // Calls the function for the directional lighting tile
  televisionTile();                 // Calls the function for the television tile
  audioTile();                      // Calls the function for the audio tile
  blindsTile();                     // Calls the function for the blinds tile
  emergentFunctionalityTiles();     // Calls the function for the emergent functionality tiles

  //Functions related to sending data to receiver arduino
  sendByteArray();                  // Calls the function for sending the byte array

  programmingTiles();               // Calls the function for when the programming mode is activated
}

// Sending the byte array containing all the tile values to the Processing sketch over USB
void sendByteArray() {
  if (millis() - lastTime > 50) {       // Send a byte array every 50 milliseconds (20 times/second)
    Serial.write(byteArray, byteArraySize); // Write bytes in byteArray with total length 'byteArraySize'
//        for (int i = 0; i < byteArraySize; i++) {
//        Serial.print(byteArray[i]);   // When sending directly to Processing
//        Serial.print('\t');           // When sending directly to Processing
//        Serial.write(byteArray[i]);   // When sending directly to other Arduino
//        Serial.write('\t');           // When sending directly to other Arduino
//        }
//        Serial.println();
    lastTime = millis();                // Set lastTime back to current time
  }
}


