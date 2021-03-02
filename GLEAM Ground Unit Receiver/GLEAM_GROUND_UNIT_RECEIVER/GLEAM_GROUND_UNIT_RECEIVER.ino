/* 
   XBee Series 3 Mesh Network: Ground Unit Reciever
   This unit will receive data from each end device one at a time according to the
   order placed in Ground Unit Transmitter.  

   Author: Joe Poeppel, poepp027@umn.edu
   Last Edited: 1/23/2021
*/


#include <XBee.h>                                       // This must be the "XBee-master" library
#include <SPI.h>                                        // SPI  library              
#include <SD.h>                                         // SD   library
#include <Wire.h>                                       // I2C  library
#include <SFE_MicroOLED.h>                              // OLED library


// SD CARD VARIABLES
#define chipSelect BUILTIN_SDCARD                       // Using built in chipselect on Teensy 3.5
File datalog;                                           // File object to be opened, written to, and closed
char filename[] = "GLM00.csv";                          // File name as will be seen on SD card -- can have maximum of 99 files on SD card ('GLM00' -> 'GLM99')
bool sdActive = false;                                  // Boolean to check if there are any available filenames left to be used 

// MICRO_OLED SETTINGS and OBJECT
#define PIN_RESET 9                                     // The SFE_MicroOLED.h library assumes a reset pin is necessary.The Qwiic OLED has RST hard-wired, so pick an arbitrary IO pin that is not being used.
#define DC_JUMPER 1                                     // The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is open (default)
MicroOLED oled(PIN_RESET, DC_JUMPER);                   // OLED Object

// TEENSY 3.5 LED PIN CONNECTIONS
#define LED1 24
#define LED2 25

// XBEE OBJECTS
#define XBeeSerial Serial5
XBee xBee = XBee(&XBeeSerial);

// BAUD RATES
#define SERIAL_BAUD_RATE 9600                           // Baud rate of serial monitor
#define XBEE_BAUD_RATE 115200                           // Baud rate of xBee serial

String xbeeData;
String dataString;
String list = "";

String spacer = ", ";

String UnitA1String = "UnitA1 Not Detected, ";
String UnitA2String = "UnitA2 Not Detected, ";
String UnitA3String = "UnitA3 Not Detected, ";
String UnitA4String = "UnitA4 Not Detected, ";
String UnitA5String = "UnitA5 Not Detected,,,,,,,,, "; // Professor Flaten

String UnitB1String = "UnitB1 Not Detected, ";
String UnitB2String = "UnitB2 Not Detected, ";
String UnitB3String = "UnitB3 Not Detected, ";
String UnitB4String = "UnitB4 Not Detected, ";
String UnitB5String = "UnitB5 Not Detected,,,,,,,,,,,,, "; // Joe Poeppel

String UnitC1String = "UnitC1 Not Detected, ";
String UnitC2String = "UnitC2 Not Detected, ";
String UnitC3String = "UnitC3 Not Detected, ";
String UnitC4String = "UnitC4 Not Detected, ";
String UnitC5String = "UnitC5 Not Detected, ";

String UnitD1String = "UnitD1 Not Detected, ";
String UnitD2String = "UnitD2 Not Detected, ";
String UnitD3String = "UnitD3 Not Detected, ";
String UnitD4String = "UnitD4 Not Detected, ";
String UnitD5String = "UnitD5 Not Detected, ";

bool UnitA1Bool = false;
bool UnitA2Bool = false;
bool UnitA3Bool = false;
bool UnitA4Bool = false;
bool UnitA5Bool = false;

bool UnitB1Bool = false;
bool UnitB2Bool = false;
bool UnitB3Bool = false;
bool UnitB4Bool = false;
bool UnitB5Bool = false;

bool UnitC1Bool = false;
bool UnitC2Bool = false;
bool UnitC3Bool = false;
bool UnitC4Bool = false;
bool UnitC5Bool = false;

bool UnitD1Bool = false;
bool UnitD2Bool = false;
bool UnitD3Bool = false;
bool UnitD4Bool = false;
bool UnitD5Bool = false;

bool ReceiverBool = false;

void setupProcedure();
void setupSD();
void setupOLED();

void receiveXBeeData();
void parseData();
void printData();
void updateSD();
void updateOLED();
void resetUnitStrings();
void resetUnitBools();
void blinkLED(int x);


void setup() {

  setupProcedure();

}

void loop() {

  receiveXBeeData();
  parseData();
  printData();
  
}

/////////////////// SETUP FUNCTION DEFINITIONS ///////////////////

void setupProcedure() {
  
  Serial.begin(SERIAL_BAUD_RATE);
  XBeeSerial.begin(XBEE_BAUD_RATE);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  delay(150);
  
  Serial.print("Connecting OLED...               ");
  setupOLED();   
  Serial.println("complete!"); 
  
  Serial.print("Establishing XBee Mesh Network...  ");
  delay(5000);
  Serial.println("done.");
  
  Serial.print("Setting up SD card...        ");
  setupSD();
  
  Serial.println("Beginning data collection...");
  
}



void setupSD() {
  
  pinMode(chipSelect, OUTPUT);
  if(!SD.begin(chipSelect)) {
    Serial.println("SD card failed, or not present");
    delay(1000); 
  }
  else {
    Serial.print("      card initialized! \nCreating File...                   ");
    for (byte i = 0; i<100; i++) {
      filename[3] = '0' + i/10;
      filename[4] = '0' + i%10;
      if(!SD.exists(filename)) {
        datalog = SD.open(filename, FILE_WRITE);
        sdActive = true;
        Serial.println("complete!");
        Serial.println("Logging to: " + String(filename));
        delay(500);
        break;}
      }

      if(!sdActive) {
        Serial.println("No available file names; clear SD card to enable logging");
        delay(500);
    }
  }
}



void setupOLED() {
  
  Wire.begin();
  oled.begin();
  oled.clear(ALL);
  oled.display();
  oled.clear(PAGE);
  randomSeed(analogRead(A0) + analogRead(A1));
  delay(250);
  updateOLED("OLED\nonline!");
  delay(100);

}


/////////////////// MAIN FUNCTION DEFINITIONS ///////////////////

void receiveXBeeData() {
  
  while(!xBee.available()) {}
  
  if (xBee.available()) {
    xbeeData = xBee.readStringUntil('Q');
  }
    blinkLED(1);
    parseData();
}



void parseData() {
  
  if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '1' && UnitA1Bool == false) {
    UnitA1String = xbeeData + spacer;
    UnitA1Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit A1");
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '2' && UnitA2Bool == false) {
    UnitA2String = xbeeData + spacer;
    UnitA2Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit A2");
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '3' && UnitA3Bool == false) {
    UnitA3String = xbeeData + spacer;
    UnitA3Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit A3");
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '4' && UnitA4Bool == false) {
    UnitA4String = xbeeData + spacer;
    UnitA4Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit A4");
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '5' && UnitA5Bool == false) {
    UnitA5String = xbeeData + spacer;
    UnitA5Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit A5");
  }




  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '1' && UnitB1Bool == false) {
    UnitB1String = xbeeData + spacer;
    UnitB1Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit B1");
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '2' && UnitB2Bool == false) {
    UnitB2String = xbeeData + spacer;
    UnitB2Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit B2");
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '3' && UnitB3Bool == false) {
    UnitB3String = xbeeData + spacer;
    UnitB3Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit B3");
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '4' && UnitB4Bool == false) {
    UnitB4String = xbeeData + spacer;
    UnitB4Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit B4");
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '5' && UnitB5Bool == false) {
    UnitB5String = xbeeData + spacer;
    UnitB5Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit B5");
  }




else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '1' && UnitC1Bool == false) {
    UnitC1String = xbeeData + spacer;
    UnitC1Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit C1");
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '2' && UnitC2Bool == false) {
    UnitC2String = xbeeData + spacer;
    UnitC2Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit C2");
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '3' && UnitC3Bool == false) {
    UnitC3String = xbeeData + spacer;
    UnitC3Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit C3");
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '4' && UnitC4Bool == false) {
    UnitC4String = xbeeData + spacer;
    UnitC4Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit C4");
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '5' && UnitC5Bool == false) {
    UnitC5String = xbeeData + spacer;
    UnitC5Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit C5");
  }




   else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '1' && UnitD1Bool == false) {
    UnitD1String = xbeeData + spacer;
    UnitD1Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit D1");
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '2' && UnitD2Bool == false) {
    UnitD2String = xbeeData + spacer;
    UnitD2Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit D2");
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '3' && UnitD3Bool == false) {
    UnitD3String = xbeeData + spacer;
    UnitD3Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit D3");
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '4' && UnitD4Bool == false) {
    UnitD4String = xbeeData + spacer;
    UnitD4Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit D4");
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '5' && UnitD5Bool == false) {
    UnitD5String = xbeeData + spacer;
    UnitD5Bool = true;
    updateOLED("Data\nreceived\nfrom:\n\nUnit D5");
  }



 
  else if (xbeeData.charAt(0) == 'R' && ReceiverBool == false) { 
    ReceiverBool = true;
    updateOLED("Data\nreceived\nfrom:\n\nGUT");
    delay(150);
    }

  else{}
}


void printData() {

  if (ReceiverBool == true) {

  // GROUP A
  // dataString = String(millis()/1000) + ", " + UnitA1String + UnitA2String + UnitA3String + UnitA4String + UnitA5String;

  // GROUP B
  // dataString = String(millis()/1000) + ", " + UnitB1String + UnitB2String + UnitB3String + UnitB4String + UnitB5String;

  // GROUP C
  // dataString = String(millis()/1000) + ", " + UnitC1String + UnitC2String + UnitC3String + UnitC4String + UnitC5String;

  // GROUP D
  // dataString = String(millis()/1000) + ", " + UnitD1String + UnitD2String + UnitD3String + UnitD4String + UnitD5String;

  // ALL GROUPS
  
  dataString = String(millis()/1000) + ", " + UnitA1String + UnitA2String + UnitA3String + UnitA4String + UnitA5String;
  dataString = dataString + UnitB1String + UnitB2String + UnitB3String + UnitB4String + UnitB5String;
  dataString = dataString + UnitC1String  + UnitC2String + UnitC3String + UnitC4String + UnitC5String;
  dataString = dataString + UnitD1String + UnitD2String + UnitD3String + UnitD4String + UnitD5String;

  Serial.println(dataString);
  updateSD();
  resetUnitStrings();
  resetUnitBools();
  }
}

void updateSD() {
  datalog = SD.open(filename, FILE_WRITE);
  datalog.println(dataString);
  datalog.close();
  blinkLED(2);
}


void updateOLED(String text) {
  
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println(text);
  oled.display();
}



void blinkLED(int x) {
  if (x == 1) {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  }

  else if (x == 2) {
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  }
}








void resetUnitStrings() {

  UnitA1String = "UnitA1 Not Detected, ";
  UnitA2String = "UnitA2 Not Detected, ";
  UnitA3String = "UnitA3 Not Detected, ";
  UnitA4String = "UnitA4 Not Detected, ";
  UnitA5String = "UnitA5 Not Detected,,,,,,,,, ";
  
  UnitB1String = "UnitB1 Not Detected, ";
  UnitB2String = "UnitB2 Not Detected, ";
  UnitB3String = "UnitB3 Not Detected, ";
  UnitB4String = "UnitB4 Not Detected, ";
  UnitB5String = "UnitB5 Not Detected,,,,,,,,,,,,, ";
  
  UnitC1String = "UnitC1 Not Detected, ";
  UnitC2String = "UnitC2 Not Detected, ";
  UnitC3String = "UnitC3 Not Detected, ";
  UnitC4String = "UnitC4 Not Detected, ";
  UnitC5String = "UnitC5 Not Detected, ";
  
  UnitD1String = "UnitD1 Not Detected, ";
  UnitD2String = "UnitD2 Not Detected, ";
  UnitD3String = "UnitD3 Not Detected, ";
  UnitD4String = "UnitD4 Not Detected, ";
  UnitD5String = "UnitD5 Not Detected, ";
    
}

void resetUnitBools() {
  
  UnitA1Bool = false;
  UnitA2Bool = false;
  UnitA3Bool = false;
  UnitA4Bool = false;
  UnitA5Bool = false;
  
  UnitB1Bool = false;
  UnitB2Bool = false;
  UnitB3Bool = false;
  UnitB4Bool = false;
  UnitB5Bool = false;
  
  UnitC1Bool = false;
  UnitC2Bool = false;
  UnitC3Bool = false;
  UnitC4Bool = false;
  UnitC5Bool = false;
  
  UnitD1Bool = false;
  UnitD2Bool = false;
  UnitD3Bool = false;
  UnitD4Bool = false;
  UnitD5Bool = false;

  ReceiverBool = false;
}
