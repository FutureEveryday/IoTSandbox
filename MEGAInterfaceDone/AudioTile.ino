void audioTile(){
  if (presenceCheckArray[7] == 1){

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
      byteArray[audioOnOffByte] = 0;
   } else {
      byteArray[audioOnOffByte] = 1;
   }
    
    byteArray[audioLocationByte] = digitalRead(audioLocationSwitch); 
    byteArray[audioGenreByte] = audioGenreSelected; 
    byteArray[audioVolumeByte] = map(analogRead(audioVolumePotPin),0,1024,0,70); 
  }
  else{
    byteArray[audioGenreByte] = 0;
  }
}
