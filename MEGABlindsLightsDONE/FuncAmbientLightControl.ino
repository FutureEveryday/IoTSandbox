void ambientLightControl() {

  if (ambientOnState == 0) { // When OFF, turn everything off
    for (int i = 0; i < NUM_LEDSAmbient; i++) {
      ledsAmbient[i] = CRGB::Black;
    }
  }

  if (ambientOnState == 1) {

    for (int i = 0; i < middle - (range / 2); i++) {                              // LEDs OFF before LEDs array
      if (rangeCheck(i)) ledsAmbient[i] =   CRGB(0, 0, 0);
    }
    for (int i = middle - (range / 2); i < middle + (range / 2); i++) {           // LEDs ON
      if (rangeCheck(i)) ledsAmbient[i] =   CRGB( brightness, brightness * 0.58, brightness * 0.16);
    }
    for (int i = middle + (range / 2); i < NUM_LEDSAmbient; i++) {                // LEDs OFF after LEDs array
      if (rangeCheck(i)) ledsAmbient[i] =   CRGB(0, 0, 0);
    }
    //    if (((middle + range / 2)-1 ) > NUM_LEDSAmbient) {
    //      for (int i = NUM_LEDSAmbient-1; i < ((NUM_LEDSAmbient-1) + (range / 2)); i++) {
    //        ledsAmbient[i] =   CRGB(0, 0, 0);
    //      }
    //    }

    //  for (int y = 0; y < middle-(range/2); y++) {
    //    ledsAmbient.setPixelColor(y, 0, 0, 0);
    ////    ledsAmbient.show();
    //  }
    //    for (int x = middle - (range/2); x < middle + (range/2); x++){
    //  ledsAmbient.setPixelColor(x, brightness, brightness * 0.58, brightness * 0.16);
    ////  ledsAmbient.show();
    //  }
    //  for (int z = middle + (range/2); z < NUM_LEDSAmbient; z++) {
    //    ledsAmbient.setPixelColor(z, 0, 0, 0);
    ////    ledsAmbient.show();
    //  }

  }

}

bool rangeCheck( int l ) {
  bool ok = true;
  if ( l < 0 || l >= NUM_LEDSAmbient ) ok = false;
  return ok;
}

//    FastLED.show();                         // Show what ledstrips need to show based on input
//  ledsAmbient.show();

