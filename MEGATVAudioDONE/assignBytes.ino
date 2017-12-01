void assignBytes() {
  //    for (int i = 0; i < NR_BYTES; i++) {
  //      Serial.print(byteArray[i]);
  //      Serial.print('\t');
  //    }
  //    Serial.println();

  speakerStatus = byteArray[audioOnOffByte];       // ON or OFF
//      Serial.print(speakerStatus);
//      Serial.println(" ");
  roomSelect    = byteArray[audioLocationByte];       // LOCATION: Plays either in living or in sleep
  //    Serial.print(roomSelect);
  //    Serial.print(" ");
  songSelect    = byteArray[audioGenreByte];       // SELECTION of song
  //    Serial.print(songSelect);
  //    Serial.print(" ");
  audioVolume   = byteArray[audioVolumeByte];       // VOLUME
  //    Serial.print(audioVolume);
  //    Serial.print(" ");

  // TELEVISION
  tvStatus      = byteArray[televisionOnOffByte];      // ON or OFF
  //    Serial.print(tvStatus);
  //    Serial.print(" ");
  channelSelect = byteArray[televisionChannelByte];      // SELECTION of channel
  //    Serial.print(channelSelect);
  //    Serial.print(" ");
  tvVolume      = byteArray[televisionVolumeByte];      // VOLUME
  //    Serial.print(tvVolume);
  //    Serial.print(" ");
  
}

