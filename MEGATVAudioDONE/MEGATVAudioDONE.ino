/*
  This Arduino receives the 16-byte long array from the other MEGA inside the house over Serial RX1 and controls the television and audio of the house.
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

#define NR_BYTES 15                     // Amount of bytes to receive over Serial RX2
byte byteArray[NR_BYTES];

//lookup table which position in the byteArray contains which variable
int audioOnOffByte = 5;             // audioOnOff, 0 or 1, is the audio tile switched on or not
int audioLocationByte = 6;          // audioLocation, 0 or 1, music in the bedroom or in the living room
int audioGenreByte = 7;             // audioGenre, a value from 0 - 5
int audioVolumeByte = 8;            // audioVolume, a value between 0 and 255 containing the potmeter value (volume) for the audio tile
int televisionOnOffByte = 9;       // televisionOnOff, 0 or 1, is the television switched on or not
int televisionChannelByte = 10;     // televisionChannelSelect, a value from 0 - 5
int televisionVolumeByte = 11;      // televisionVolume, a value between 0 and 255 containing the potmeter value (volume) for the television tile
int directionalLightByte1 = 12;     // directionalLight, 0 or 1, light is switch on or not
int directionalLightByte2 = 13;     // directionalLight, 0 or 1, light is switch on or not
int endByte = 14;                   // Endbyte 15 > "B"

boolean fullStringReceived = false;     // Check value that prevents loop from running until full array of bytes has been received

// Television HX8357 Variable
//#include <TFT_HX8357.h>                 // Hardware-specific library
//TFT_HX8357 tft = TFT_HX8357();          // Invoke custom library

// SD chip select
//#define SDC_CS 53
//
//#define BU_BMP 1 // Temporarily flip the TFT coords for standard Bottom-Up bit maps
//#define TD_BMP 0 // Draw inverted Top-Down bitmaps in standard coord frame

#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define BREAKOUT_RESET  9               // VS1053 reset pin (output)
#define BREAKOUT_CS     10              // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8               // VS1053 Data/command select pin (output)

#define SHIELD_RESET  -1                // VS1053 reset pin (unused!)
#define SHIELD_CS     7                 // VS1053 chip select pin (output)
#define SHIELD_DCS    6                 // VS1053 Data/command select pin (output)

#define CARDCS 4                        // Card chip select pin
#define DREQ 3                          // VS1053 Data request, ideally an Interrupt pin

unsigned long lastTime;
int intervalTime = 50;

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// VARIABLES REQUIRED FOR THIS CODE
// MUSIC
int speakerStatus;                      // ON or OFF
int prevSpeakerStatus;
int roomSelect;                         // LOCATION: Plays either in living or in sleep
int songSelect;                         // SELECTION of song
int prevSongSelect;
bool changeSong = false;
int audioVolume;                        // VOLUME

// TELEVISION
int tvStatus;                           // ON or OFF
int prevTvStatus;
int channelSelect;                      // SELECTION of channel
int prevChannelSelect;
int tvVolume;                           // VOLUME
bool changeChannel = false;

int volMax;                             // Maximum volume over speakers (lower is louder)
int volMin = 70;                        // Minimum volume over speakers (higher is less loud)
int outputVolume;                       // Separate volMax for TV and audio

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);                // receives the array from the interface over this serial

  if (! musicPlayer.begin()) {          // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);                          // don't do anything more
  }
  Serial.println("SD OK!");

  Serial.println(F("VS1053 found"));

  //  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
  //    Serial.println(F("DREQ pin is not an interrupt pin"));

  // This option uses timer0, this means timer1 & t2 are not required
  // (so you can use 'em for Servos, etc) BUT millis() can lose time
  // since we're hitchhiking on top of the millis() tracker
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  // This option uses a pin interrupt. No timers required! But DREQ
  // must be on an interrupt pin. For Uno/Duemilanove/Diecimilla
  // that's Digital #2 or #3
  // See http://arduino.cc/en/Reference/attachInterrupt for other pins
  // *** This method is preferred
  //  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
  //    Serial.println(F("DREQ pin is not an interrupt pin"));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (fullStringReceived) {

    // Print array of bytes that was received over serial //
    for (int i = 0; i < NR_BYTES; i++) {
      //      byteArray[i] = inputByteArray[i];
      Serial.print(byteArray[i]);
      Serial.print('\t');
    }
    Serial.println();
    ////////////////////////////////////////////////////////

    assignBytes();                      // This function assigns the bytes to the corresponding variables

    audioControl();
//    televisionControl();
    volumeControl();

  }
  fullStringReceived = false;
}

void serialEvent2() {
  if (Serial2.available() > 0) {
    if (Serial2.read() == 65) {
      Serial2.readBytes(byteArray, NR_BYTES);
      // CHECK START AND END VALUES AS CONDITIONS TO SAY THAT FULL STRING HAS BEEN RECEIVED
      if (byteArray[endByte] == 66){
      fullStringReceived = true;
      }
    }
  }
}
