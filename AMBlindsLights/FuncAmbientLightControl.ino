void ambientLightControl() {

  if (ambientOnState == 0) { // When OFF, turn everything off
    for (int i = 0; i < NUM_LEDSAmbient; i++) {
      ledsAmbient[i] = CRGB::Black;
    }
  }

  if (ambientOnState == 1) {

    for (int i = 0; i < middle - (range / 2); i++) { // LEDs off before LEDs array
      ledsAmbient[i] =   CRGB(0, 0, 0);
    }
    for (int i = middle - (range / 2); i < middle + (range / 2); i++) { // LEDs off before LEDs array
      ledsAmbient[i] =   CRGB( brightness, brightness * 0.58, brightness * 0.16);
    }
    for (int i = middle + (range / 2); i < NUM_LEDSAmbient; i++) {
      ledsAmbient[i] =   CRGB(0, 0, 0);
    }
  }

  //  bool rangeCheck( int l ) {
  //    bool ok = true;
  //    if ( l < 0 || l >= NUM_LEDSAmbient ) ok = false;
  //    return ok;
  //  }
  
  FastLED.show();                         // Show what ledstrips need to show based on input
}
