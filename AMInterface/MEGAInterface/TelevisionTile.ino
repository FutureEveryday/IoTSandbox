//#define televisionChannelUpPin 51
//#define televisionChannelDownPin 49

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

void televisionTile(){
  if (presenceCheckArray[0] == 1){

     if(digitalRead(televisionChannelUpPin) != lastStateTelevisionChannelUp){
      lastStateTelevisionChannelUp = digitalRead(televisionChannelUpPin);
      if(digitalRead(televisionChannelUpPin) != 1){
        televisionChannelSelected--;
      }
    }

    if(digitalRead(televisionChannelDownPin) != lastStateTelevisionChannelDown){
      lastStateTelevisionChannelDown = digitalRead(televisionChannelDownPin);
      if(digitalRead(televisionChannelDownPin) != 1){
        televisionChannelSelected++;
      }
    }

    //Serial.println(digitalRead(televisionChannelUpPin));
    
    if(televisionChannelSelected < 0){
      televisionChannelSelected = 5;
    }
    if(televisionChannelSelected > 5){
      televisionChannelSelected = 0;
    }
    
    byteArray[10] = digitalRead(televisionSwitchPin); 
    byteArray[11] = televisionChannelSelected; 
    byteArray[12] = map(analogRead(televisionVolumePotPin),1024,0,70,30); 
    //Serial.println(televisionChannelSelected);
  }else{
    byteArray[10] = 0; 
    
  }
}
