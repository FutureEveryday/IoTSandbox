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
      byteArray[ambientBrightnessByte] = map(byteArray[ambientBrightnessByte],0,255,0,80);
    } 
  }
  if (presenceCheckArray[3] == 1 && emergentAmbilightBlindsOnOff % 4 == 0 ){
    if(connectionsTiles[2] == 1){
      byteArray[ambientLocationByte] = 195;
      byteArray[ambientWidthByte] = 70;
      byteArray[ambientBrightnessByte] = 1;
    } 
  }
  if (presenceCheckArray[8] == 1 && emergentDiscoOrganOnOff % 4 == 0 && byteArray[audioOnOffByte] == 1){
    if(connectionsTiles[3] == 1){
      //disco
      int randomValue = random(60);
      if(millis()-lastTimeDisco < 250){
        byteArray[ambientWidthByte] = byteArray[ambientBrightnessByte]+40;
        if(byteArray[ambientBrightnessByte]-randomValue < 0){
          byteArray[ambientBrightnessByte] = 0;
        }else{
          byteArray[ambientBrightnessByte] = byteArray[ambientBrightnessByte]-randomValue;
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
      byteArray[televisionVolumeByte] = byteArray[audioVolumeByte];
    } 
  }
}

