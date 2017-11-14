void televisionControl() {

if (tvStatus == 0){
  tft.fillScreen(TFT_BLACK);
  prevTvStatus = tvStatus;
}
  
  else if (byteArray[10] == 1) {
    switch (channelSelect) {
      case 0:
        tft.setRotation(3);
        // Draw bmp image top left corner at x,y = 0,0
        // Image must fit (one day I will add clipping... but it will slow things down)
        drawBMP("CC.BMP", 0, 0, BU_BMP);
              case 1:
        tft.setRotation(3);
        // Draw bmp image top left corner at x,y = 0,0
        // Image must fit (one day I will add clipping... but it will slow things down)
        drawBMP("Disc.BMP", 0, 0, BU_BMP);
              case 2:
        tft.setRotation(3);
        // Draw bmp image top left corner at x,y = 0,0
        // Image must fit (one day I will add clipping... but it will slow things down)
        drawBMP("Journaal.BMP", 0, 0, BU_BMP);
              case 3:
        tft.setRotation(3);
        // Draw bmp image top left corner at x,y = 0,0
        // Image must fit (one day I will add clipping... but it will slow things down)
        drawBMP("Jurassic.BMP", 0, 0, BU_BMP);
              case 4:
        tft.setRotation(3);
        // Draw bmp image top left corner at x,y = 0,0
        // Image must fit (one day I will add clipping... but it will slow things down)
        drawBMP("Mtv.BMP", 0, 0, BU_BMP);
              case 5:
        tft.setRotation(3);
        // Draw bmp image top left corner at x,y = 0,0
        // Image must fit (one day I will add clipping... but it will slow things down)
        drawBMP("SW.BMP", 0, 0, BU_BMP);
        
    }
  }
}

