/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Central Unit Reciever                                                        |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 3/10/2021                                                                              |
 *                                                                                              | 
 * XBee Series 3 Mesh Network: Central Unit Receiver for GLEAM Project                          |
 * This software is to be placed on the ground unit receiver that is to receiver data from the  |
 * measurement devices, recieve a parse request from the Cut Unit Transmitter (CUT), parse      |
 * the data, and log the data to an SD card. Designed for a Teensy 3.5 and Teensyduino.         |
 ----------------------------------------------------------------------------------------------*/

#include <XBee.h>                                       // This must be the "XBee-master" library
#include <SPI.h>                                        // SPI  library              
#include <SD.h>                                         // SD   library
#include <Wire.h>                                       // I2C  library
#include <SFE_MicroOLED.h>                              // OLED library


// SD CARD VARIABLES
#define chipSelect BUILTIN_SDCARD                       // Using built in chipselect on Teensy 3.5
File datalog;                                           // File object to be opened, written to, and closed
char filename[] = "GLMR00.csv";                         // File name as will be seen on SD card -- can have maximum of 99 files on SD card ('GLM00' -> 'GLM99')
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

// XBEE VARIABLES
String xbeeData;
String dataString;

// OLED VARIABLES
#define BUTTON 38                                      // Digital pin for button
int display = 0;

// GENERAL VARIABLES
String spacer = ", ";
String endline = "\n";
String recentUnit = "";
String timer;
int dataLogs = 0;

// # ',' per unit string = # spacers sent + 1
// UNIT VARIABLES
String UnitA1String = "UnitA1 Not Detected, "; // Karalus, Calvin
String UnitA2String = "UnitA2 Not Detected, "; // Meyer, Shawn
String UnitA3String = "UnitA3 Not Detected, "; // Nihart, Joe
String UnitA4String = "UnitA4 Not Detected, "; // Toriseva, Ben
String UnitA5String = "UnitA5 Not Detected,,,,,,,,, "; // Professor Flaten

String UnitB1String = "UnitB1 Not Detected, "; // Bauers, Macy
String UnitB2String = "UnitB2 Not Detected, "; // Elliot, Greta
String UnitB3String = "UnitB3 Not Detected, "; // Saner, Garvin
String UnitB4String = "UnitB4 Not Detected, "; // Stevens, Ben
String UnitB5String = "UnitB5 Not Detected,,,,,,,,,,,,, "; // Joe Poeppel

String UnitC1String = "UnitC1 Not Detected, "; // Grau-Firkus, Cooper
String UnitC2String = "UnitC2 Not Detected, "; // Hartford, Peter
String UnitC3String = "UnitC3 Not Detected, "; // Lanauze-Baez, Alfonso
String UnitC4String = "UnitC4 Not Detected, "; // Mattson, Tyler
String UnitC5String = "UnitC5 Not Detected, "; // Sorge, Ben
 
String UnitD1String = "UnitD1 Not Detected, "; // Anderson, Logan
String UnitD2String = "UnitD2 Not Detected, "; // Das, Roudh
String UnitD3String = "UnitD3 Not Detected, "; // Habegger Mc Cabe, Erne
String UnitD4String = "UnitD4 Not Detected, "; // Ray, Ben
String UnitD5String = "UnitD5 Not Detected, "; // Vanhatten, Isabelle

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

// SETUP FUNCTIONS
void setupProcedure();
void ledStartup();
void setupSD();
void setupOLED();

// UPDATE FUNCTIONS
void receiveXBeeData();
void parseData();
void printData();
void updateSD();
void updateOLED();
void updateDisplay();
void resetUnitStrings();
void resetUnitBools();
void blinkLED(int x);


void setup() {

  setupProcedure();

}

void loop() {

  receiveXBeeData();
  parseData();
  updateDisplay();
  printData();
  
}



void setupProcedure() {
  
  Serial.begin(SERIAL_BAUD_RATE);
  XBeeSerial.begin(XBEE_BAUD_RATE);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON, INPUT);
  ledStartup();
 
  Serial.print("Connecting OLED...               ");
  setupOLED();   
  Serial.println("complete!"); 
  delay(1000);
  
  Serial.print("Establishing XBee Mesh Network...  ");
  updateOLED("Est. XBee\nmesh\nnetwork...");
  delay(2500);
  Serial.println("done.");
  updateOLED("XBee\nnetwork\nonline!");
  delay(1000);
  
  Serial.print("Setting up SD card...        "); 
  updateOLED("Setting up\nSD Card..");         
  setupSD();
  Serial.println("Beginning data collection...");
  delay(500);
  updateOLED("Starting\ndata\ncollection");
  delay(1000);
  
}



void receiveXBeeData() {
  
  while(!xBee.available()) {}
  
  if (xBee.available()) {
    xbeeData = xBee.readStringUntil('Q');
  }
    Serial.println(xbeeData);
    blinkLED(1);
    parseData();
}


void printData() {

  if (ReceiverBool == true) {

  // GROUP A
  // dataString = String(millis()/1000.0) + ", " + UnitA1String + UnitA2String + UnitA3String + UnitA4String + UnitA5String;

  // GROUP B
   dataString = String(millis()/1000.0) + ", " + UnitB1String + UnitB2String + UnitB3String + UnitB4String + UnitB5String;

  // GROUP C
  // dataString = String(millis()/1000.0) + ", " + UnitC1String + UnitC2String + UnitC3String + UnitC4String + UnitC5String;

  // GROUP D
  //dataString = String(millis()/1000.0) + ", " + UnitD1String + UnitD2String + UnitD3String + UnitD4String + UnitD5String;

  // ALL GROUPS
  
//  dataString = String(millis()/1000.0) + ", " + UnitA1String + UnitA2String + UnitA3String + UnitA4String + UnitA5String;
//  dataString = dataString + UnitB1String + UnitB2String + UnitB3String + UnitB4String + UnitB5String;
//  dataString = dataString + UnitC1String  + UnitC2String + UnitC3String + UnitC4String + UnitC5String;
//  dataString = dataString + UnitD1String + UnitD2String + UnitD3String + UnitD4String + UnitD5String;

  Serial.println(dataString);
  updateSD();
  resetUnitStrings();
  resetUnitBools();
  }
}
