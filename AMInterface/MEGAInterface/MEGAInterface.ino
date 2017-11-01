#include <FastLED.h>

//LIGHT INTERFACE VARIABLES
#define dataPinInterface 7                        // Pin that controls the tile LEDs on the interface
#define numLedsInterface 10                       // Amount of LEDs in the interface
CRGB ledsInterface[numLedsInterface];             // Class that controls LEDs according to CRGB reference
int lookupTableLeds[] = {6,9,7,8,5,0,1,4,3,2};    // Array that couples the LED number of the strip to the correct tile

//SERIAL COMMUNICATION VARIABLES
// Values containing data which will be sent to the receiver arduino
#define byteArraySize 21                          // Size of the array that is sent over Serial
uint8_t byteArray[byteArraySize];                 // Array that is sent over Serial
//lookup table which position in the byteArray contains which variable
//byteArray - 0: Constant value used in the receiver arduino to check if the array is received correctly
//byteArray - 1: ambientSwitchPin, 0 or 1, is the ambient tile switched on or not
//byteArray - 2: encValue, the encoder value
//byteArray - 3: ambientSliderPin, a value between 0 and 255 containing the slider value (range) for the ambient tile
//byteArray - 4: ambientPotPin, a value between 0 and 255 containing the pot value (intencity) for the ambient tile
//byteArray - 5: blindsSliderPin, a value between 0 and 255 containing the slider value (directional control) for the blinds
//byteArray - 6: audioOnOff, 0 or 1, is the audio tile switched on or not
//byteArray - 7: audioLocationSwitch, 0 or 1, is the location of the audio in the living or the sleeping area
//byteArray - 8: audioGenreSelected, between 0 and 5, determaining the genre which is slected
//byteArray - 9: audioVolumePotPin. a value between 0 and 70 determaining the volume of the music
//byteArray - 10: televisionSwitchPin, between 0 and 1, determining if the television is switched on or not
//byteArray - 11: televisionChannelSelected, a value between 0 and 5, determaining the channel which is slected
//byteArray - 12: televisionVolumePotPin, a value between 30 and 70, determaining the volume of the tv audio
//byteArray - 13: directionalLightLivingOnOff, between 0 and 1, is the lighting in the living room switched on or not
//byteArray - 14: directionalLightSleepingOnOff, between 0 and 1, is the lighting in the sleeping area switched on or not

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
int pinsPresence[] = {32,48,30,44,34,46,42,36,38,40};
int presenceCheckArray[10];

//DIGITAL PINS FOR PROGRAMMING INTERFACE
#define arrayLengthProgramming 10
int pinsProgramming[] = {52,6,50,5,29,23,26,24,22,28};
int programmingCheckArray[10];

//ARRAY FOR LIGHTSTRIP INTERFACE
#define arrayLengthLeds 10
int ledsArray[] = {0,0,0,0,0,0,0,0,0,0};

int brightness = 120;
unsigned long lastTimeProgrammingLeds;

//PROGRAMMING MODE 
#define programmingPin 9
boolean programmingModeActive = false;
//These arrays are keeping track of the state change of all the programming buttons which are beneath each tile
int lastStatePins[] = {0,0,0,0,0,0,0,0,0,0};
int pushStatePins[] = {2,2,2,2,2,2,2,2,2,2};
// This array stores whether the pins are involved in a active emergent functionality connection
int programmingStatePins[] = {0,0,0,0,0,0,0,0,0,0};
//This array stores whether the emergent functionality tiles are programmed or not 0:Tv/Audio 1:Ambilight 2:Ambilight + Blinds 3:DiscoOrgan
boolean connectionsTiles[] = {0,0,0,0};
boolean fadeIn = true;

void setup() {
  //Add neopixel strip, light beneath interface tiles
  FastLED.addLeds<NEOPIXEL, dataPinInterface>(ledsInterface, numLedsInterface);
  //Communication to computer
  Serial.begin(115200);
  //Communication to receiverDuinoLight arduino
  Serial1.begin(115200);
  //Communicating with receiverDuinoMedia
  Serial2.begin(115200);

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
  pinMode(blindsSliderPin,INPUT);

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
  for(int i=0;i<arrayLengthPresence;i++){
    pinMode(pinsPresence[i], INPUT);
    digitalWrite(pinsPresence[i],HIGH);
  }
   for(int i=0;i<arrayLengthProgramming;i++){
    pinMode(pinsProgramming[i], INPUT);
    digitalWrite(pinsProgramming[i],HIGH);
  }
}

void loop() {

  // Check whether tiles are currently present or not
  checkProgrammingAndPresence();

  // Check if programming mode is currently active
  checkProgrammingMode();
  
    //Tiles
    ambientTile();
    directionalLightTiles();
    televisionTile();
    audioTile();
    blindsTile();
    emergentFunctionalityTiles();
    
    //Functions related to sending data to receiver arduino
    createByteArray();
    sendByteArray();

    programmingTiles();
}

// Create the byte array
void createByteArray(){
  //First value is the check value
  byteArray[0] = 'A';
  for(int i = 17 ; i < byteArraySize-1; i++){
    byteArray[i] = 0; 
  }
  for(int i=0;i<byteArraySize-1;i++){
    Serial.print(byteArray[i]);
    Serial.print("  ");
  }
  Serial.println();
}

// Sending the byte array containing all the tile values to the receiverLight arduino via serial 1
void sendByteArray(){
   if(millis()-lastTime > 50){
    Serial1.write(byteArray, byteArraySize);
    lastTime = millis();
  }
}

// 1 = 30
// 2 = 44
// 3 = 34
// 4 = 38

// Check which tiles are present and put the results in an array
void checkProgrammingAndPresence(){
  static unsigned long prevT = millis();
  unsigned long dif = 100;
  if((unsigned long) millis() - prevT> dif){
    for(int i=0;i<arrayLengthPresence;i++){
      presenceCheckArray[i] = !digitalRead(pinsPresence[i]);
//      Serial.print(presenceCheckArray[i]);
      
      programmingCheckArray[i] = !digitalRead(pinsProgramming[i]);
//        Serial.print(pinsPresence[i]);
//    Serial.print("  ");
  
    }
    Serial.println();
    prevT= millis();
    showLeds();
  }
}

void showLeds(){

  //If programming mode is active, pulsate the leds to reflect this in the interface
    if(brightness < 200 && fadeIn == true && programmingModeActive == true){
       brightness += 20;
    }else{
       fadeIn = false;
    }
    if(brightness > 40 && fadeIn == false && programmingModeActive == true){
       brightness -= 20;  
    }else{
       fadeIn = true;
     }
     lastTimeProgrammingLeds = millis();
   
   FastLED.setBrightness(brightness);
   
   //This for loop loops through all the leds and decides whether they are programmed, being programmed, connected or disconnected
  for(int i=0;i<numLedsInterface;i++){
    // check if the tiles are present
    if(presenceCheckArray[i] == 1){
      // check if the programming mode is activated
      if(programmingModeActive == true){
       // Check if a programming connection is made, which turns the leds green
       if(programmingStatePins[i] == 1 && checkButtonPressed() == true){
          ledsInterface[lookupTableLeds[i]] = CRGB::Green;
       }else if(pushStatePins[i] % 4 == 0){
          ledsInterface[lookupTableLeds[i]] = CRGB::Red;
        }else{
          ledsInterface[lookupTableLeds[i]] = CRGB( brightness, brightness, brightness);
        }
       }else{
        if(i == 2){
            if(emergentAmbilightOnOff % 4 == 0 && connectionsTiles[1] == 1){
               ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
            }else{
              ledsInterface[lookupTableLeds[i]] = CRGB::White;
            }
          }else if(i == 3){
            if(emergentAmbilightBlindsOnOff % 4 == 0 && connectionsTiles[2] == 1){
               ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
            }else{
              ledsInterface[lookupTableLeds[i]] = CRGB::White;
            }
          }else if(i == 4){
            if(emergentTvAudioOnOff % 4 == 0 && connectionsTiles[0] == 1){
               ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
             }else{
              ledsInterface[lookupTableLeds[i]] = CRGB::White;
            }
          }else if(i == 8){
            if(emergentDiscoOrganOnOff % 4 == 0 && connectionsTiles[3] == 1){
               ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
            }else{
              ledsInterface[lookupTableLeds[i]] = CRGB::White;
            }
          }else{
            ledsInterface[lookupTableLeds[i]] = CRGB::White;   
          }
       }
      }else{
        ledsInterface[lookupTableLeds[i]] = CRGB::Black;
      }
  }
   FastLED.show();
}

// check if the interface is in programming mode
boolean checkProgrammingMode(){
  if(!digitalRead(programmingPin) == 1){
    programmingModeActive = true;
  }else{
    programmingModeActive = false;
    for(int i=0;i<10;i++){
      pushStatePins[i] = 2;
    }
  }
}

//check for all the programming pins whether they are pressed or not
int checkButtonPressed(){
  for(int i=0;i<arrayLengthProgramming;i++){
    if(pushStatePins[i] != 2){
      return false;
      break;
    }
  }
  return true;
}

