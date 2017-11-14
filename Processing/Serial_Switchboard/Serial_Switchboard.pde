import processing.serial.*;

// The serial port
Serial MEGAInterface;
// The serial port
Serial MEGABlindsLights;
// The serial port
Serial MEGATelevisionAudio;

void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  MEGAInterface = new Serial(this, Serial.list()[1], 115200);
  //MEGABlindsLights = new Serial(this, Serial.list()[1], 115200);
  //MEGATelevisionAudio = new Serial(this, Serial.list()[2], 115200);
  
}

void draw() {
  // Expand array size to the number of bytes you expect
  byte[] inBuffer = new byte[21];
  while (MEGAInterface.available() > 0) {
    inBuffer = MEGAInterface.readBytes();
    MEGAInterface.readBytes(inBuffer);
    if (inBuffer != null) {
      String myString = new String(inBuffer);
      println(myString);
    }
  }
  
  
  
}