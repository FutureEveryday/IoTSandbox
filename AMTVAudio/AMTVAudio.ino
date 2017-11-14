/*
  This Arduino receives the 15-byte long array from the interface over USB and controls the television and audio of the house.
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

// Television HX8357 Variable
#include <TFT_HX8357.h>        // Hardware-specific library
TFT_HX8357 tft = TFT_HX8357(); // Invoke custom library

// SD chip select
#define SDC_CS 53

#define BU_BMP 1 // Temporarily flip the TFT coords for standard Bottom-Up bit maps
#define TD_BMP 0 // Draw inverted Top-Down bitmaps in standard coord frame

// Audio VS1053 Variables
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)

#define SHIELD_RESET  -1       // VS1053 reset pin (unused!)
#define SHIELD_CS     7        // VS1053 chip select pin (output)
#define SHIELD_DCS    6        // VS1053 Data/command select pin (output)

#define CARDCS 4               // Card chip select pin
#define DREQ 3                 // VS1053 Data request, ideally an Interrupt pin

boolean fullStringReceived = false;     // Check value that prevents loop from running until full array of bytes has been received

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

#define NR_BYTES 4
byte byteArray[NR_BYTES];
byte inputByteArray[NR_BYTES];

// VARIABLES REQUIRED FOR THIS CODE
// AUDIO
int speakerStatus;                  // Audio ON or OFF
int songSelect;                     // Audio GENRE SELECT
int audioVolume;                    // Audio VOLUME
int roomSelect;                     // Indicates ROOM SELECTION where music is playes

// TELEVISION
int tvStatus;                       // Television ON or OFF
int prevTvStatus;                   // Previous state of television, else it keeps on drawing new bitmaps
int channelSelect;                  // Television CHANNEL SELECTION
int tvVolume;                       // Television VOLUME

int volMax;                         // Maximum volume of audio
int volMin = 70;                    // Minimum volume of audio
int outputVolume;                   // Separate volMax for TV and audio

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);            // receives the array from the interface over this serial
  Serial1.setTimeout(5);

  tft.init(); // Initialise the display (various parameters configured)

  //  if (! musicPlayer.begin()) { // initialise the music player
  //    // Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
  //    while (1);
  //  }
  //
  //  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT)) {
  //    //Serial.println(F("DREQ pin is not an interrupt pin"));
  //  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (fullStringReceived) {
    for (int i = 0; i < NR_BYTES; i++) {
      Serial.print(byteArray[i]);
      Serial.print('\t');
    }
    Serial.println();

    int speakerStatus             = byteArray[5];
    int songSelect                = byteArray[6];
    int audioVolume               = byteArray[7];
    int roomSelect                = byteArray[8];

    // TELEVISION
    int tvStatus                  = byteArray[9];
    int channelSelect             = byteArray[10];
    int tvVolume                  = byteArray[11];

    if (speakerStatus == 1) {
      audioControl();
    }
    if (tvStatus == 1){
      televisionControl();
    }

    volumeControl();

  }
  fullStringReceived = false;
}
void serialEvent1() { // if data comes in, write incoming data to array
  if (Serial1.available() >= NR_BYTES) {
    if (Serial1.read() == 65) {
      //if this is true then we have received the complete string
      Serial1.readBytes(inputByteArray, NR_BYTES - 1);
      //  Print values for review
      for (int i = 0; i < NR_BYTES - 1; i++)  byteArray[i] = inputByteArray[i];
      //      brightness = byteArray[0];
      fullStringReceived = true;
    }
  }
}
