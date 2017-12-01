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
    
    byteArray[televisionOnOffByte] = digitalRead(televisionSwitchPin); 
    byteArray[televisionChannelByte] = televisionChannelSelected; 
    byteArray[televisionVolumeByte] = map(analogRead(televisionVolumePotPin),1024,0,70,30); 
    //Serial.println(televisionChannelSelected);
  }
  else{
    byteArray[televisionOnOffByte] = 0; 
  }
}
