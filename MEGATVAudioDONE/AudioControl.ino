void audioControl() {

  if (songSelect != prevSongSelect) {
    changeSong = true;
  }
//  else {
//    changeSong = false;
//  }

  if (speakerStatus == 0) {
    musicPlayer.stopPlaying();
  }

  if (speakerStatus == 1 && changeSong == true || speakerStatus != prevSpeakerStatus) {
    switch (songSelect) {
      case 0:
        checkPlaying();
        musicPlayer.startPlayingFile("ACDC.mp3");
        Serial.println("ACDC");
        break;
      case 1:
        checkPlaying();
        musicPlayer.startPlayingFile("Drake.mp3");
        break;
      case 2:
        checkPlaying();
        musicPlayer.startPlayingFile("FooFig.mp3");
        break;
      case 3:
        checkPlaying();
        musicPlayer.startPlayingFile("TakeFiv.mp3");
        break;
      case 4:
        checkPlaying();
        musicPlayer.startPlayingFile("Shmurda.mp3");
        break;
      case 5:
        checkPlaying();
        musicPlayer.startPlayingFile("Sinatra.mp3");
        break;

    }
    prevSongSelect = songSelect;
    prevSpeakerStatus = speakerStatus;
  }
}

void checkPlaying() {
  if (musicPlayer.playingMusic) {
    musicPlayer.stopPlaying();
  }
  changeSong = false;
}

