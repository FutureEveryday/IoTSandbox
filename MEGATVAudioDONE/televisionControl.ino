//void televisionControl() {
//
//  if (channelSelect != prevChannelSelect) {
//    changeChannel = true;
//  }
//  else{
//    changeChannel = false;
//  }
//
//  if (tvStatus == 0) {
//    tft.fillScreen(TFT_BLACK);
//  }
//
//  else if (tvStatus == 1 && changeChannel == true || tvStatus != prevTvStatus) {
//    switch (channelSelect) {
//      case 0:
//        tft.setRotation(3);
//        musicPlayer.startPlayingFile("ComCen.mp3");
//        drawBMP("CC.BMP", 0, 0, BU_BMP);
//      case 1:
//        tft.setRotation(3);
//        musicPlayer.startPlayingFile("Discov.mp3");
//        drawBMP("Disc.BMP", 0, 0, BU_BMP);
//      case 2:
//        tft.setRotation(3);
//        musicPlayer.startPlayingFile("Journa.mp3");
//        drawBMP("Journaal.BMP", 0, 0, BU_BMP);
//      case 3:
//        tft.setRotation(3);
//        musicPlayer.startPlayingFile("Jurass.mp3");
//        drawBMP("Jurassic.BMP", 0, 0, BU_BMP);
//      case 4:
//        tft.setRotation(3);
//        musicPlayer.startPlayingFile("Mtv.mp3");
//        drawBMP("Mtv.BMP", 0, 0, BU_BMP);
//      case 5:
//        tft.setRotation(3);
//        musicPlayer.startPlayingFile("Starwa.mp3");
//        drawBMP("SW.BMP", 0, 0, BU_BMP);
//    }
//    prevChannelSelect = channelSelect;
//    prevTvStatus = tvStatus;
//  }
//  
//}

