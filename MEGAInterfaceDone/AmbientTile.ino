void ambientTile() {
  if (presenceCheckArray[5] == 1) {                                                          // If tile is in place, run code below
    updateEncoder();                                                                         // Run function that reads the encoder
    byteArray[ambientOnOffByte]       = !digitalRead(ambientSwitchPin);                      // Check if ambient lighting is turned on and assign to first byte in the array
    byteArray[ambientLocationByte]    = encValue;                                            // Assign the encoder value to the second byte in the array
    byteArray[ambientWidthByte]       = map(analogRead(ambientSliderPin), 1024, 0, 0, 255);  // Read analog value for width of ambient lighting, map it 0-255 and that assign to third byte in the array
    byteArray[ambientBrightnessByte]  = map(analogRead(ambientPotPin), 1024, 0, 0, 255);     // Read analog value for brightness of ambient lighting, map it 0-255 and that assign to fourth byte in the array
  } else {
    byteArray[ambientOnOffByte]       = 0;                                                   // If tile is not in place, send a 0 to the first byte in the array
  }
}
