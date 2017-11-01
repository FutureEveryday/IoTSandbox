void ambientLightControl() {

  if (ambientOnState == 0) {
    for (int i = 0; i < NUM_LEDSAmbient; i++){
      ledsAmbient[i] = CRGB::Black;
      }
//      Serial.println("ambient = 0");
    middle = 0;
    range = 0;
    differencePixel = 0;
    brightness = 10;
    encValue = NUM_LEDSAmbient / 2;
  }

  else {
    FastLED.clear();
    Serial.print(" YESS IM HERE");
    brightness = map(valuePotAmbient, 0, 1023, 0, 100);
    Serial.print("Brightness = ");
    Serial.print(brightness);
//    middle = encValue;
    Serial.print("Middle = ");
    Serial.println(encValue);
    for (int y = 0; y < encValue - (valueSliderAmbient / 2); y++) {
      if (rangeCheck(y)) ledsAmbient[y] =   CRGB(0, 0, 0);
    }
    for (int z = encValue + (valueSliderAmbient / 2); z < NUM_LEDSAmbient; z++) {
      if (rangeCheck(z)) ledsAmbient[z] =   CRGB(0, 0, 0);
    }
    for (int x = encValue - (valueSliderAmbient / 2); x < encValue + (valueSliderAmbient / 2); x++) {
      if (rangeCheck(x)) ledsAmbient[x] =   CRGB( brightness, brightness * 0.58, brightness * 0.16);
    }
    FastLED.show();
  }
}

//BELOW CODE READ THE ENCODER VALUE
void updateEncoder() {

  encValue = myEnc.read();
  if (encValue != oldPosition) {
    oldPosition = encValue;
  }

  if (encValue > NUM_LEDSAmbient) {
    myEnc.write(NUM_LEDSAmbient);
  }

  if (encValue < 0) {
    myEnc.write(0);
  }

  encValue = constrain((encValue), 0, NUM_LEDSAmbient);
//  Serial.print("Encoder = ");
//  Serial.print(encValue);
//  byteArray[0] = 'A';
//  byteArray[1] = map(analogValueSlider, 0, 1023, 0, 255);
//  for (int i = 2 ; i < byteArraySize - 1; i++) {
//    byteArray[i] = encValue;
//  }

  if (millis() - lastTime > 20) {
    Serial3.write(byteArray, byteArraySize);
    lastTime = millis();
  }
}

bool rangeCheck( int l ) {
  bool ok = true;
 if( l < 0 || l >= NUM_LEDSAmbient ) ok = false;
 return ok;
}
