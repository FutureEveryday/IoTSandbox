void audioControl() {
  if (songSelect == 0) {
    musicPlayer.stopPlaying();
  }
  else if (songSelect == 1) {
    switch (songSelect) {
      case 0:
        checkPlaying();
        musicPlayer.startPlayingFile("ACDC.mp3");
        break;
      case 1:
        checkPlaying();
        musicPlayer.startPlayingFile("Drake.mp3");
        break;
      case 2:
        checkPlaying();
        musicPlayer.startPlayingFile("FooFight.mp3");
        break;
      case 3:
        checkPlaying();
        musicPlayer.startPlayingFile("Germain.mp3");
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
  }
}

