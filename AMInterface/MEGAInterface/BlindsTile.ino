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

//BLINDS TILE VARIABLES
//#define blindsSliderPin A4

void blindsTile(){
  if (presenceCheckArray[1] == 1){
    int blindsValue = 120;
    blindsValue = analogRead(blindsSliderPin);
    byteArray[5] = map(blindsValue,0,1023,0,255);
  }else{
    byteArray[5] = 120;
  }
}
