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

//boolean connectionsTiles[] = {0,0,0,0};
//#define emergentAmbilightSwitchPin 53
//int emergentAmbilightOnOff;
//int emergentAmbilightLastState;
//#define emergentAmbilightBlindsSwitchPin 43
//int emergentAmbilightBlindsOnOff;
//int emergentAmbilightBlindsPinLastState;
//#define emergentTvAudioSwitchPin 45
//int emergentTvAudioOnOff;
//int emergentTvAudioPinLastState;
//#define emergentDiscoOrganSwitchPin 33
//int emergentDiscoOrganOnOff;
//int emergentDiscoOrganPinLastState;

void emergentFunctionalityTiles(){

  if(!digitalRead(emergentTvAudioSwitchPin) != emergentTvAudioPinLastState){
    emergentTvAudioPinLastState = !digitalRead(emergentTvAudioSwitchPin);
    if(!digitalRead(emergentTvAudioSwitchPin) != 1){
      emergentTvAudioOnOff++;
    }else{
      emergentTvAudioOnOff++;
    }
  }

  if(!digitalRead(emergentAmbilightSwitchPin) != emergentAmbilightLastState){
    emergentAmbilightLastState = !digitalRead(emergentAmbilightSwitchPin);
    if(!digitalRead(emergentAmbilightSwitchPin) != 1){
      emergentAmbilightOnOff++;
    }else{
      emergentAmbilightOnOff++;
    }
  }
  
  if(!digitalRead(emergentAmbilightBlindsSwitchPin) != emergentAmbilightBlindsLastState){
    emergentAmbilightBlindsLastState = !digitalRead(emergentAmbilightBlindsSwitchPin);
    if(!digitalRead(emergentAmbilightBlindsSwitchPin) != 1){
      emergentAmbilightBlindsOnOff++;
    }else{
      emergentAmbilightBlindsOnOff++;
    }
  }

  if(!digitalRead(emergentDiscoOrganSwitchPin) != emergentDiscoOrganLastState){
    emergentDiscoOrganLastState = !digitalRead(emergentDiscoOrganSwitchPin);
    if(!digitalRead(emergentDiscoOrganSwitchPin) != 1){
      emergentDiscoOrganOnOff++;
    }else{
      emergentDiscoOrganOnOff++;
    }
  }
  
  if (presenceCheckArray[2] == 1 && emergentAmbilightOnOff % 4 == 0 && byteArray[10] == 1 ){
     if(connectionsTiles[1] == 1){
//      byteArray[1] = !digitalRead(ambientSwitchPin); 
//      byteArray[2] = encValue; 
//      byteArray[3] = map(analogRead(ambientSliderPin),1024,0,0,255); 
//      byteArray[4] = map(analogRead(ambientPotPin),1024,0,0,255); 
      byteArray[4] = map(byteArray[4],0,255,0,80);
//      if(presenceCheckArray[1] == 1){
//        byteArray[5] = 255; 
//      }
    } 
  }
  if (presenceCheckArray[3] == 1 && emergentAmbilightBlindsOnOff % 4 == 0 ){
    if(connectionsTiles[2] == 1){
//      byteArray[1] = !digitalRead(ambientSwitchPin); 
//    byteArray[2] = encValue; 
//    byteArray[3] = map(analogRead(ambientSliderPin),1024,0,0,255); 
//    byteArray[4] = map(analogRead(ambientPotPin),1024,0,0,255); 
      byteArray[2] = 195;
      byteArray[3] = 70;
      byteArray[5] = 1;
    } 
  }
  if (presenceCheckArray[8] == 1 && emergentDiscoOrganOnOff % 4 == 0 && byteArray[6] == 1){
    if(connectionsTiles[3] == 1){
      //disco
      int randomValue = random(60);
      if(millis()-lastTimeDisco < 250){
        byteArray[3] = byteArray[3]+40;
        if(byteArray[4]-randomValue < 0){
          byteArray[4] = 0;
        }else{
          byteArray[4] = byteArray[4]-randomValue;
        }
      }else{
        if(millis()-lastTimeDisco > 500){
          lastTimeDisco = millis();
        }
      }
    } 
  }
  if (presenceCheckArray[4] == 1 && emergentTvAudioOnOff % 4 == 0){
    if(connectionsTiles[0] == 1){
      byteArray[12] = byteArray[9];
    } 
  }
}

