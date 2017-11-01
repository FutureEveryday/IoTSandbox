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
//byteArray - 10: televisionSwitchPin, between 0 and 1, determaining if the television is switched on or not
//byteArray - 11: televisionChannelSelected, a value between 0 and 5, determaining the channel which is slected
//byteArray - 12: televisionVolumePotPin, a value between 30 and 70, determaining the volume of the tv audio
//byteArray - 13: directionalLightLivingOnOff, between 0 and 1, is the lighting in the living room switched on or not
//byteArray - 14: directionalLightSleepingOnOff, between 0 and 1, is the lighting in the sleeping area switched on or not

//#define arrayLengthProgramming 10
//int pinsProgramming[] = {52,6,50,5,29,23,26,24,22,28};
//int programmingCheckArray[10];

//This function is being called when, and only when, the interface is in programming mode.
void programmingTiles(){  

  for(int i=0;i<arrayLengthProgramming;i++){
    if(programmingCheckArray[i] != lastStatePins[i]){
      lastStatePins[i] = programmingCheckArray[i];
      pushStatePins[i]++;
    }
  }

  // Checking if Tv/Audio tile is being programmed
  if(pushStatePins[0] % 4 == 0 && pushStatePins[7] % 4 == 0 && pushStatePins[4] % 4 == 0){
    connectionsTiles[0] = 1;
    for(int i=0;i<3;i++){
      ledsInterface[lookupTableLeds[0]] = CRGB::Green;
      ledsInterface[lookupTableLeds[7]] = CRGB::Green;
      ledsInterface[lookupTableLeds[4]] = CRGB::Green;
      FastLED.show();
      delay(200);
      ledsInterface[lookupTableLeds[0]] = CRGB::Black;
      ledsInterface[lookupTableLeds[7]] = CRGB::Black;
      ledsInterface[lookupTableLeds[4]] = CRGB::Black;
      FastLED.show();
      delay(200);
    }
    if(connectionsTiles[0] == 1){
      programmingStatePins[0] = 1;
      programmingStatePins[4] = 1;
      programmingStatePins[7] = 1;
    }else{
      programmingStatePins[0] = 0;
      programmingStatePins[4] = 0;
      programmingStatePins[7] = 0;  
    }
    for(int i=0;i<arrayLengthProgramming;i++){
      pushStatePins[i] = 2;
    }
  }
  if(pushStatePins[5] % 4 == 0 && pushStatePins[2] % 4 == 0 && pushStatePins[0] % 4 == 0){
    connectionsTiles[1] = 1;
    for(int i=0;i<3;i++){
      ledsInterface[lookupTableLeds[5]] = CRGB::Green;
      ledsInterface[lookupTableLeds[2]] = CRGB::Green;
      ledsInterface[lookupTableLeds[0]] = CRGB::Green;
      FastLED.show();
      delay(200);
      ledsInterface[lookupTableLeds[5]] = CRGB::Black;
      ledsInterface[lookupTableLeds[2]] = CRGB::Black;
      ledsInterface[lookupTableLeds[0]] = CRGB::Black;
      FastLED.show();
      delay(200);
    }
     if(connectionsTiles[1] == 1){
      programmingStatePins[5] = 1;
      programmingStatePins[2] = 1;
      programmingStatePins[0] = 1;
    }else{
      programmingStatePins[5] = 0;
      programmingStatePins[2] = 0;
      programmingStatePins[0] = 0;  
    }
    for(int i=0;i<arrayLengthProgramming;i++){
      pushStatePins[i] = 2;
    }
  }
   if(pushStatePins[5] % 4 == 0 && pushStatePins[3] % 4 == 0 && pushStatePins[1] % 4 == 0){
    connectionsTiles[2] = 1;
    for(int i=0;i<3;i++){
      ledsInterface[lookupTableLeds[5]] = CRGB::Green;
      ledsInterface[lookupTableLeds[3]] = CRGB::Green;
      ledsInterface[lookupTableLeds[1]] = CRGB::Green;
      FastLED.show();
      delay(200);
      ledsInterface[lookupTableLeds[5]] = CRGB::Black;
      ledsInterface[lookupTableLeds[3]] = CRGB::Black;
      ledsInterface[lookupTableLeds[1]] = CRGB::Black;
      FastLED.show();
      delay(200);
    }
    if(connectionsTiles[2] == 1){
      programmingStatePins[5] = 1;
      programmingStatePins[3] = 1;
      programmingStatePins[1] = 1;
    }else{
      programmingStatePins[5] = 0;
      programmingStatePins[3] = 0;
      programmingStatePins[1] = 0;  
    }
    for(int i=0;i<arrayLengthProgramming;i++){
      pushStatePins[i] = 2;
    }
  }
   if(pushStatePins[5] % 4 == 0 && pushStatePins[7] % 4 == 0 && pushStatePins[8] % 4 == 0){
    connectionsTiles[3] = 1;
    for(int i=0;i<3;i++){
      ledsInterface[lookupTableLeds[5]] = CRGB::Green;
      ledsInterface[lookupTableLeds[7]] = CRGB::Green;
      ledsInterface[lookupTableLeds[8]] = CRGB::Green;
      FastLED.show();
      delay(200);
      ledsInterface[lookupTableLeds[5]] = CRGB::Black;
      ledsInterface[lookupTableLeds[7]] = CRGB::Black;
      ledsInterface[lookupTableLeds[8]] = CRGB::Black;
      FastLED.show();
      delay(200);
    }
    if(connectionsTiles[3] == 1){
      programmingStatePins[5] = 1;
      programmingStatePins[7] = 1;
      programmingStatePins[8] = 1;
    }else{
      programmingStatePins[5] = 0;
      programmingStatePins[7] = 0;
      programmingStatePins[8] = 0;  
    }
    for(int i=0;i<arrayLengthProgramming;i++){
      pushStatePins[i] = 2;
    }
  }
}

