// Code that controls the audio and the television

// ReceiverDuinoLight sends array to this arduino with required values over Serial....?

#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)

#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

boolean newVal = false;

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

#define NR_BYTES 4
byte byteArray[NR_BYTES];
byte inputByteArray[NR_BYTES];

// VARIABLES REQUIRED FOR THIS CODE
// music
int speakerStatus = byteArray[6];; // on or off
int songSelect = byteArray[8];;
int audioVolume = byteArray[9];
int roomSelect = byteArray[7];; // if on: plays either in living or in sleep
// tv
int tvStatus = byteArray[10]; // on or off
int prevTvStatus;
int channelSelect = byteArray[11];
int tvVolume = byteArray[12];

int volMax;
int volMin = 70;
int outputVolume; // separate volMax for TV and audio

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200); // receives the array from the interface over this serial

//  if (! musicPlayer.begin()) { // initialise the music player
//    // Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
//    while (1);
//  }
//
//  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT)) {
//    //Serial.println(F("DREQ pin is not an interrupt pin"));
//  }
  
  Serial1.setTimeout(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (newVal) {
    for (int i = 0; i < NR_BYTES; i++) {
      Serial.print(byteArray[i]);
      Serial.print('\t');
    }
    Serial.println();
    newVal = false;
  }

//  if (byteArray[6] == 1) {
//    audioControl();
//  }
//  if (byteArray[10] == 1) {
//    televisionControl();
//  }
//
//  volumeControl();

}
void serialEvent1() { // if data comes in, write incoming data to array
  if (Serial1.available() >= NR_BYTES) {
    if (Serial1.read() == 65) {
      //if this is true then we have received the complete string
      Serial1.readBytes(inputByteArray, NR_BYTES - 1);
      //  Print values for review
      for (int i = 0; i < NR_BYTES - 1; i++)  byteArray[i] = inputByteArray[i];
//      brightness = byteArray[0];
      newVal = true;
    }
  }
}
