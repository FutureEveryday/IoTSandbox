void volumeControl() {
  // als alleen tv > maxVolume = 30;
  // als tv + audio of alleen audio > maxVolume = 0;

  if (byteArray[6] && byteArray[10]) {
    int volMax = 0;
    outputVolume = byteArray[9];
    }

  else if (byteArray[6] && !byteArray[10]) {
    int volMax = 0;
    outputVolume = byteArray[9];
  }

  else if (byteArray[10] && !byteArray[6]) {
    int volMax = 30;
    outputVolume = byteArray[12];
  }

  if (byteArray[7] == 0) {
    musicPlayer.setVolume(0, outputVolume);
  }
  else if (byteArray[7] == 1) {
    musicPlayer.setVolume(outputVolume, 0);
  }
}

