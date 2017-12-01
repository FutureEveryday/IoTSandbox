void volumeControl() {
  // als alleen tv > maxVolume = 30;
  // als tv + audio of alleen audio > maxVolume = 0;

  if (speakerStatus && tvStatus) {
    outputVolume = audioVolume;
    musicPlayer.setVolume(70, outputVolume);
  }

  else if (speakerStatus && !tvStatus) {
    outputVolume = audioVolume;
    if (roomSelect == 0){
      musicPlayer.setVolume(70, outputVolume);
    }
    else if (roomSelect == 1){
      musicPlayer.setVolume(outputVolume, 70);
    }
  }

  else if (tvStatus && !speakerStatus) {
    outputVolume = tvVolume;
    musicPlayer.setVolume(70, outputVolume);
  }
}

