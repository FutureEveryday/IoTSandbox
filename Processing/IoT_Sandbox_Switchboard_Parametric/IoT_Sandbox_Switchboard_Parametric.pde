import processing.serial.*;
PImage bg;

Serial Interface1;
Serial Interface2;
Serial Interface3;
Serial House;

int byteLength = 16;
byte[] inBuffer = new byte[byteLength];
byte[] inBuffer2 = new byte[byteLength];
int conversionInt = 0;

long lastTime;
long lastTime2;
long lastTime3;
int intervalMillis = 50;

int windowWidth = 480;
int windowHeight = 320;

int buttonSizeWidth;
int buttonSizeHeight = windowHeight/3;
int cornerRadius = 5;

// Button-related integers
int buttonOriginY = windowHeight/3;

int activeInterface = 100;
int interfaceOver = 100;
boolean mouseClick = false;

int interfaceAmount;
boolean interfaceArrayPrint = false;      // If true, it prints the array coming from the interface that is currently activated in the drag and drop
boolean houseArrayPrint = true;           // If true, it prints the array that the house is receiving


void setup() {
  size(480, 320);                                        // This is the size of the 3.5" touchscreen
  bg = loadImage("GreyBackground.jpg");                  // Assign image to the variable "bg"
  printArray(Serial.list());                             // Print all the serial connections that are active 
  //interfaceAmount = Serial.list().length-3;             // This integer is based on the amount of serial connections -3 (-3 because 2 are used by the Pi at all times, and 1 is the house)
  interfaceAmount = Serial.list().length-1;             // This integer is based on the amount of serial connections -3 (-3 because 2 are used by the Pi at all times, and 1 is the house)
  println("list length = " + interfaceAmount);          // Print the amount of active serial connections that are interfaces
  buttonSizeWidth = windowWidth/(3*interfaceAmount);    // This is the width of a button, based on the amount of interfaces
  buttonSizeHeight = buttonSizeWidth;                    // Make the height correspond to the width of a button to keep them square

  // RASPBERRY PI
  /*
// Based on the amount of serially connected interfaces, make new serial ports
   if (interfaceAmount == 1) {
   House = new Serial(this, "/dev/ttyACM0", 115200);
   Interface1 = new Serial(this, "/dev/ttyACM1", 115200);
   }
   if (interfaceAmount == 2) {
   House = new Serial(this, "/dev/ttyACM0", 115200);
   Interface1 = new Serial(this, "/dev/ttyACM1", 115200);
   Interface2 = new Serial(this, "/dev/ttyACM2", 115200);
   }
   if (interfaceAmount == 3) {
   House = new Serial(this, "/dev/ttyACM0", 115200);
   Interface1 = new Serial(this, "/dev/ttyACM1", 115200);
   Interface2 = new Serial(this, "/dev/ttyACM2", 115200);
   Interface3 = new Serial(this, "/dev/ttyACM3", 115200);
   }
   */

  // WINDOWS COMPUTER
  // Based on the amount of serially connected interfaces, make new serial ports
  if (interfaceAmount == 1) {
    House = new Serial(this, "COM6", 115200);
    Interface1 = new Serial(this, "COM4", 115200);
  }
  if (interfaceAmount == 2) {
    House = new Serial(this, "COM6", 115200);
    Interface1 = new Serial(this, "COM4", 115200);
    Interface2 = new Serial(this, "COM6", 115200);
  }
  if (interfaceAmount == 3) {
    House = new Serial(this, "/dev/ttyACM0", 115200);
    Interface1 = new Serial(this, "/dev/ttyACM1", 115200);
    Interface2 = new Serial(this, "/dev/ttyACM2", 115200);
    Interface3 = new Serial(this, "/dev/ttyACM3", 115200);
  }

  // IF TIME LEFT, MAKE HERE A LISTENING PART, WHERE INTERFACES SEND THEIR NAMES TO BE PRINTED OVER EACH BUTTON
}

void draw() {
  //background(0, 0, 0);
  background(bg);                  // Load image into the background

  // Based on amount of serial connections, draw rectangles representing the interfaces
  for (int i = 0; i < interfaceAmount; i++) {

    if (interfaceOver == i) {      // Fill rectangle differently according to hover over, or not
      fill(100);
    } else {
      fill(200);
    }

    if (activeInterface == i && mouseClick) {    // If interface has be set to active, give the button a green stroke
      strokeWeight(5);
      stroke(0, 255, 0);
    } else {
      noStroke();
    }

    // Draw an x amount of rectangles, based on the amount of serially connected interfaces
    rectMode(CENTER);
    rect(windowWidth/(interfaceAmount+1)*(i+1), buttonOriginY, buttonSizeWidth, buttonSizeHeight, cornerRadius);
  }

  // DRAW A RESET BUTTON
  noStroke();
  fill(255, 0, 0);
  ellipseMode(CENTER);
  ellipse(windowWidth/2, (windowHeight/15)*12, buttonSizeWidth/2, buttonSizeHeight/2);
  noStroke();
  fill(255, 0, 0);
  textSize(15);
  textAlign(CENTER);
  text("RESET", windowWidth/2, (windowHeight/15)*10);


  // HERE WE DEFINE WHICH INTERFACE IS ACTIVE (I.E. SENDING DATA TO THE HOUSE)
  // THIS IS BASED ON WHICH CONNECTION IS MADE USING THE DRAG AND DROP FUNCTION ON THE TOUCHSCREEN

  if (activeInterface == 0 && mouseClick) {                            // If the first interface is connected, do what is below 
    Interface1.readBytes(inBuffer);                     // Read the bytes that are sent from interface 1 and put them in a buffer
    if (millis() - lastTime > intervalMillis) {         // Every 50 milliseconds, do what is below
      sendBytes();                                      // Go to the sendBytes() function at the bottom of this page
      lastTime = millis();                              // Set lastTime to current time
    }
  }

  if (activeInterface == 1  && mouseClick) {                            // If the first interface is connected, do what is below 
    Interface2.readBytes(inBuffer);                     // Read the bytes that are sent from interface 1 and put them in a buffer
    if (millis() - lastTime > intervalMillis) {         // Every 50 milliseconds, do what is below
      sendBytes();                                      // Go to the sendBytes() function at the bottom of this page
      lastTime = millis();                              // Set lastTime to current time
    }
  }

  if (activeInterface == 2  && mouseClick) {                            // If the first interface is connected, do what is below 
    Interface3.readBytes(inBuffer);                     // Read the bytes that are sent from interface 1 and put them in a buffer
    if (millis() - lastTime > intervalMillis) {         // Every 50 milliseconds, do what is below
      sendBytes();                                      // Go to the sendBytes() function at the bottom of this page
      lastTime = millis();                              // Set lastTime to current time
    }
  }


  // CONVERT INCOMING BYTE (FROM CURRENTLY ACTIVE INTERFACE) TO VALUES THAT WE CAN READ //
  if (interfaceArrayPrint == true && mouseClick) {
    if (millis() - lastTime3 > intervalMillis) {         // Every 50 milliseconds, do what is below
      for (int i = 0; i < inBuffer.length; i++) {           // For the length of the buffer, do the following with each value
        conversionInt = 0;
        conversionInt = ((byte)inBuffer[i] | (byte) conversionInt) & 0xFF; // Convert the byte from an ASCII value to an integer
        print(conversionInt + "\t");                        // Print the converted byte as an integer in the console, followed by a tab
      }
      println();                                            // Go to next line after the for loop has finished to print the next line of bytes
      lastTime3 = millis();                                 // Set lastTime to current time
    }
  }
  //////////////////////////////////////////////////////////////////////////////

  // CONVERT INCOMING BYTE (FROM HOUSE) TO VALUES THAT WE CAN READ //
  if (houseArrayPrint == true && mouseClick) {
    House.readBytes(inBuffer2);                             // This function reads the bytes that come in at the house as a check to see if the byte array is received
    //Interface2.readBytes(inBuffer2);
    if (millis() - lastTime2 > intervalMillis) {            // Every 50 milliseconds, do what is below
      for (int i = 0; i < inBuffer2.length; i++) {
        conversionInt = 0;
        conversionInt = ((byte)inBuffer2[i] | (byte) conversionInt) & 0xFF;
        print(conversionInt + "\t");
      }
      println();
      lastTime2 = millis();
      //}
    }
  }
  //////////////////////////////////////////////////////////////////////////////
}

void mouseMoved() {
  for (int i = 0; i < interfaceAmount; i++) {
    if (mouseX > (windowWidth/(interfaceAmount+1)*(i+1))-buttonSizeWidth/2 && mouseX < (windowWidth/(interfaceAmount+1)*(i+1)+buttonSizeWidth/2) && mouseY > buttonOriginY-buttonSizeHeight/2 && mouseY < buttonOriginY+buttonSizeHeight/2) {
      interfaceOver = i;
      //println("hooverInterface" + interfaceOver);
    } else {
      interfaceOver = 10;
    }
  }
}

void mousePressed() {
  for (int i = 0; i < interfaceAmount; i++) {
    if (mouseX > (windowWidth/(interfaceAmount+1)*(i+1))-buttonSizeWidth/2 && mouseX < (windowWidth/(interfaceAmount+1)*(i+1)+buttonSizeWidth/2) && mouseY > buttonOriginY-buttonSizeHeight/2 && mouseY < buttonOriginY+buttonSizeHeight/2) {
      activeInterface = i;
      mouseClick = !mouseClick;
      println("activeInterface" + activeInterface);
      //mouseIn = true;
    }
  }

  if (mouseX > (windowWidth/2)-(buttonSizeWidth/2/2) && mouseX < (windowWidth/2)+(buttonSizeWidth/2/2) && mouseY > ((windowHeight/15)*12)-(buttonSizeHeight/2/2) && mouseY < ((windowHeight/15)*12)+(buttonSizeHeight/2/2)) {
    reset();
    println("reset is true");
  }
}

void reset() {
  activeInterface = 100;
  interfaceOver = 100;
  mouseClick = false;
}

// SEND INCOMING BYTE ARRAY TO HOUSE WHEN A CONNECTION HAS BEEN MADE
void sendBytes() {
  if (inBuffer[0] == 65 && inBuffer[15] == 66) { 
    House.write(inBuffer);
  }
}