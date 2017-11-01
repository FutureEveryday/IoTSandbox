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

//AUDIO TILE VARIABLES
//#define audioOnOffPin 39 
//#define audioLocationSwitch 41
//#define audioGenreUpPin 35
//#define audioGenreDownPin 37
//#define audioVolumePotPin A7
//int audioGenreSelected = 0;
//int lastStateAudioGenreDown = 0;
//int lastStateAudioGenreUp = 0;
//int audioSwitchPinLastState;
//int audioOnOff;

void audioTile(){
  if (presenceCheckArray[7] == 1){
//    Serial.print(digitalRead(audioOnOffPin)); 
//    Serial.print("  ");
//    Serial.print(digitalRead(audioLocationSwitch));
//    Serial.print("  ");
//    Serial.print(digitalRead(audioGenreUpPin));
//    Serial.print("  ");
//    Serial.print(digitalRead(audioGenreDownPin));
//    Serial.print("  ");
//    Serial.print(analogRead(audioVolumePotPin));
//    Serial.println();

    if(digitalRead(audioGenreUpPin) != lastStateAudioGenreUp){
      lastStateAudioGenreUp = digitalRead(audioGenreUpPin);
      if(digitalRead(audioGenreUpPin) != 1){
        audioGenreSelected--;
      }
    }

    if(digitalRead(audioGenreDownPin) != lastStateAudioGenreDown){
      lastStateAudioGenreDown = digitalRead(audioGenreDownPin);
      if(digitalRead(audioGenreDownPin) != 1){
        audioGenreSelected++;
      }
    }
    
    if(audioGenreSelected < 0){
      audioGenreSelected = 5;
    }
    if(audioGenreSelected > 5){
      audioGenreSelected = 0;
    }
    if(!digitalRead(audioOnOffPin) != audioSwitchPinLastState){
      audioSwitchPinLastState = !digitalRead(audioOnOffPin);
      if(!digitalRead(audioOnOffPin) != 1){
         audioOnOff++;
      }else{
        audioOnOff++;
      }
    }
   if (audioOnOff % 4 == 0) {
      byteArray[6] = 0;
   } else {
      byteArray[6] = 1;
   }
    
    byteArray[7] = digitalRead(audioLocationSwitch); 
    byteArray[8] = audioGenreSelected; 
    byteArray[9] = map(analogRead(audioVolumePotPin),0,1024,0,70); 
  }else{
    byteArray[6] = 0;
  }
}
