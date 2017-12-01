// Check which tiles are present and put the results in an array
void checkProgrammingAndPresence() {
  static unsigned long prevT = millis();
  unsigned long dif = 100;
  if ((unsigned long) millis() - prevT > dif) {
    for (int i = 0; i < arrayLengthPresence; i++) {
      presenceCheckArray[i] = !digitalRead(pinsPresence[i]);
      //      Serial.print(presenceCheckArray[i]);

      programmingCheckArray[i] = !digitalRead(pinsProgramming[i]);
      //        Serial.print(pinsPresence[i]);
      //    Serial.print("  ");

    }
    //    Serial.println();
    prevT = millis();
    showLeds();
  }
}

void showLeds() {

  //If programming mode is active, pulsate the leds to reflect this in the interface
  if (brightness < 200 && fadeIn == true && programmingModeActive == true) {
    brightness += 20;
  } else {
    fadeIn = false;
  }
  if (brightness > 40 && fadeIn == false && programmingModeActive == true) {
    brightness -= 20;
  } else {
    fadeIn = true;
  }
  lastTimeProgrammingLeds = millis();

  FastLED.setBrightness(brightness);

  //This for loop loops through all the leds and decides whether they are programmed, being programmed, connected or disconnected
  for (int i = 0; i < numLedsInterface; i++) {
    // check if the tiles are present
    if (presenceCheckArray[i] == 1) {
      // check if the programming mode is activated
      if (programmingModeActive == true) {
        // Check if a programming connection is made, which turns the leds green
        if (programmingStatePins[i] == 1 && checkButtonPressed() == true) {
          ledsInterface[lookupTableLeds[i]] = CRGB::Green;
        } else if (pushStatePins[i] % 4 == 0) {
          ledsInterface[lookupTableLeds[i]] = CRGB::Red;
        } else {
          ledsInterface[lookupTableLeds[i]] = CRGB( brightness, brightness, brightness);
        }
      } else {
        if (i == 2) {
          if (emergentAmbilightOnOff % 4 == 0 && connectionsTiles[1] == 1) {
            ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
          } else {
            ledsInterface[lookupTableLeds[i]] = CRGB::White;
          }
        } else if (i == 3) {
          if (emergentAmbilightBlindsOnOff % 4 == 0 && connectionsTiles[2] == 1) {
            ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
          } else {
            ledsInterface[lookupTableLeds[i]] = CRGB::White;
          }
        } else if (i == 4) {
          if (emergentTvAudioOnOff % 4 == 0 && connectionsTiles[0] == 1) {
            ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
          } else {
            ledsInterface[lookupTableLeds[i]] = CRGB::White;
          }
        } else if (i == 8) {
          if (emergentDiscoOrganOnOff % 4 == 0 && connectionsTiles[3] == 1) {
            ledsInterface[lookupTableLeds[i]] = CRGB::Yellow;
          } else {
            ledsInterface[lookupTableLeds[i]] = CRGB::White;
          }
        } else {
          ledsInterface[lookupTableLeds[i]] = CRGB::White;
        }
      }
    } else {
      ledsInterface[lookupTableLeds[i]] = CRGB::Black;
    }
  }
  FastLED.show();
}

// check if the interface is in programming mode
boolean checkProgrammingMode() {
  if (!digitalRead(programmingPin) == 1) {
    programmingModeActive = true;
  } else {
    programmingModeActive = false;
    for (int i = 0; i < 10; i++) {
      pushStatePins[i] = 2;
    }
  }
}

//check for all the programming pins whether they are pressed or not
int checkButtonPressed() {
  for (int i = 0; i < arrayLengthProgramming; i++) {
    if (pushStatePins[i] != 2) {
      return false;
      break;
    }
  }
  return true;
}

