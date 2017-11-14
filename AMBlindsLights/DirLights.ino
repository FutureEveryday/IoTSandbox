void directionalLights() {

  if (livingRoom == 1) {
    for (int i = 0; i < NUM_LEDSDirLiving; i++) {
      ledsDirLiving[i] = CRGB( brightness, brightness * 0.58, brightness * 0.16);
      Serial.print("yep");
    }
    FastLED.show();
  }

  else if (livingRoom == 0) {
    for (int i = 0; i < NUM_LEDSDirLiving; i++) {
      ledsDirLiving[i] = CRGB( 0, 0, 0);
    }
  }

  if (bedRoom == 1) {
    for (int i = 0; i < NUM_LEDSDirSleep; i++) {
      ledsDirSleep[i] = CRGB( brightness, brightness * 0.58, brightness * 0.16);
    }
  }

  else if (bedRoom == 0) {
    for (int i = 0; i < NUM_LEDSDirLiving; i++) {
      ledsDirSleep[i] = CRGB( 0, 0, 0);
    }
  }

}


