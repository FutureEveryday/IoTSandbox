void assignBytes(){
      // ASSIGNING OF BYTES TO INTEGERS
    // AMBIENT LIGHTING
    
    ambientOnState      = byteArray[ambientOnOffByte];     // ON or OFF                                   (0 or 1)
    //    Serial.print(ambientOnState);
    //    Serial.print(" ");
    middle              = byteArray[ambientLocationByte];     // LOCATION               (0 - 255)
//    middle = middle % NUM_LEDSAmbient;
    //    middle = 0 & middle;
    //    Serial.print(middle);
    //    Serial.print(" ");
    range               = map(byteArray[ambientWidthByte], 0, 255, 10, NUM_LEDSAmbient/2);     // WIDTH of LIGHTS         (0 - 255)
    //    Serial.print(range);
    //    Serial.print(" ");
    brightness          = map(byteArray[ambientBrightnessByte], 0, 255, 0, 150);     // BRIGHTNESS             (0 - 255)
    //    Serial.print(brightness);
    //    Serial.println(" ");

    // BLINDS
    valueBlinds         = byteArray[blindsLeftRightByte];     // DIRECTION and SPEED     (0 - 255)

    // DIRECTIONAL LIGHTS
    livingRoom          = byteArray[directionalLightByte1];
    bedRoom             = byteArray[directionalLightByte2];
}

