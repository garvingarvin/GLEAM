/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device                                                           |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Edited By Team B                                                                             |
 *                                                                                              | 
 * XBee Series 3 Mesh Network: Measurement Device for GLEAM Project                             |
 * This software is to be placed on the measurement units that are to collect data, log         |
 * the data to an SD card, and send data to the Ground Unit Reciever (CUR) once a request is    |
 * detected from the Ground Unit Transmitter (CUT). Designed for a Teensy 3.5 and Teensyduino.  |
 ----------------------------------------------------------------------------------------------*/
 
// Version Number and Date
String version_num = "0.0.22b";
String date = "3/29/2021";

 
// SENSORs, SD, and I2C LIBRARIES
#include <Wire.h>                                       // I2C  library                    - Should already be on your computer as a part of the IDE download
#include <SPI.h>                                        // SPI  library                    - Should already be on your computer as a part of the IDE download
#include <SD.h>                                         // SD   library                    - Should already be on your computer as a part of the IDE download
#include <XBee.h>                                       // XBee library                    - https://github.com/MNSGC-Ballooning/XBee
#include <SparkFunLSM9DS1.h>                            // IMU  library                    - https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library
#include <SFE_MicroOLED.h>                              // OLED library                    - https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide/arduino-library-download-install-and-test

// SENSOR LIBRARIES FOR YOUR RESPECTIVE I2C SENSOR
#include <Adafruit_VEML6070.h>                          // VEML6070 I2C Sensor             - Go to Sketch > Include Library > Manage Libraries... > (search "VEML6070" and install library...click 'Install all' if needed)
#include <Adafruit_VEML7700.h>                          // VEML7700 I2C Sensor             - Go to Sketch > Include Library > Manage Libraries... > (search "VEML7700" and install library...click 'Install all' if needed)
#include <Adafruit_AS726x.h>                            // AS7252   I2C Sensor             - Go to Sketch > Include Library > Manage Libraries... > (search "AS726x"   and install library...click 'Install all' if needed)
#include <Adafruit_SI1145.h>                            // SI1145   I2C Sensor             - Go to Sketch > Include Library > Manage Libraries... > (search "SI1145"   and install library...click 'Install all' if needed)

                                                        // Note: Don't worry if your library name doesn't turn orange. As long as you have this library downloaded and  
                                                        //       located in the proper folder, Arduino (in this case Teensyduino) will be able to properly use the library.


// SD CARD VARIABLES
#define chipSelect BUILTIN_SDCARD                       // Using built in chipselect on Teensy 3.5
File datalog;                                           // File object to be opened, written to, and closed
char filename[] = "GLM00.csv";                          // File name as will be seen on SD card -- can have maximum of 99 files on SD card ('GLM00' -> 'GLM99')
bool sdActive = false;                                  // Boolean to check if there are any available filenames left to be used 

// XBEE SERIAL DECLARATION
#define XBeeSerial Serial5                              // xBee serial TX5 and RX5 on pins 33 and 34, respectively 

// MICRO_OLED SETTINGS
#define PIN_RESET 9                                     // The SFE_MicroOLED.h library assumes a reset pin is necessary.The Qwiic OLED has RST hard-wired, so pick an arbitrary IO pin that is not being used.
#define DC_JUMPER 1                                     // The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is open (default)

// TEENSY 3.5 PIN CONNECTIONS
#define THERM A17                                       // Analog pin 17 for thermistor
#define PHOTO A16                                       // Analog pin 16 for photoresistor
#define ANALOGSENSOR A18                                // Analog pin 18 for respective analog sensor
#define LED1 24                                         // Digital pin for LED1
#define LED2 25                                         // Digital pin for LED2
#define BUTTON 38                                    // Digital pin for button

// BAUD RATES
#define SERIAL_BAUD_RATE 9600                           // Baud rate of serial monitor
#define XBEE_BAUD_RATE 115200                           // Baud rate of xBee serial

// OBJECT DELCARATIONS
MicroOLED oled(PIN_RESET, DC_JUMPER);                   // OLED Object
LSM9DS1 imu;                                            // IMU  Object
XBee xBee = XBee(&XBeeSerial);                          // xBee Object

// OBJECT DECLARATION FOR YOUR RESPECTIVE I2C SENSOR
Adafruit_VEML6070 veml6070 = Adafruit_VEML6070();       // VEML6070 Object
Adafruit_VEML7700 veml7700 = Adafruit_VEML7700();       // VEML7700 Object
Adafruit_AS726x AS;                                     // AS7262   Object
Adafruit_SI1145 SI = Adafruit_SI1145();                 // SI1145   Object

// GENERAL VARIABLES
String Data;                                            // String containing all data from sensors
String spacer = ", ";                                   // Used to make creating Data and SDData strings quicker and more organized 
String endline = "\n";                                  // Used to make creating Data and SDData strings quicker and more organized 
String delimiter = "Q";                                 // Used to make creating Data and SDData strings quicker and more organized - delimiter must be an uppercase 'E' in order for the GUR to properly read your data
String timer;                                           // Hours/Minutes/Seconds
double timeS;                                               // Time in s
String header;                                          // Used as first row of .csv file to distinguish logged data
int dataLogs = 0;                                       // Number of times data has been logged to SD card
float setupTime;                                        // Used to start logging at t = 0 seconds
int xbeeLines = 0;                                      // Number of lines in xbeeData string

//DELAY UPDATE VARIABLES
int delayFast = 50;                                     // Fast data logging (ms)
int delaySlow = 500;                                   // Slow data logging (ms)
int delayLength = delayFast;                            // Delay length (in milliseconds) between each main loop iteration
int fastDataTime = 10;                                    // Seconds from start when swtich to slow data logging occurs
float accelPrev[3];                                       //Stores the previous accelerometer values for comparison
int startTime;                                            // Time of inital accelerometer disturbance
double accelTolerance = .05;                             // Amount accel data needs to change (in Gs) to increase data recording rate

// IMU VARIABLES
float magnetometer[3];                                  // Three element array for holding magnetometer values in x, y, z directions, respectively
float accelerometer[3];                                 // Three element array for holding acceleration values in x, y, z directions, respectively
float gyroscope[3];                                     // Three element array for holding gyroscope    values in x, y, z directions, respectively
float roll;                                             // Roll of IMU
float pitch;                                            // Pitch of IMU
float heading;                                          // Heading of IMU
float DECLINATION = -7.22;                              // Declination of Minneapolis, MN

// THERMISTOR CONSTANTS and VARIABLES
int analogResolutionBits = 14;                          // Sets the size (in bits) of the value returned by analogRead(). It defaults to 10 bits (returns values between 0-1023), but we can request greater accuracy by using more bits
int analogResolutionVals = pow(2,analogResolutionBits); // Maximum possible analog resolution with base-2 math
int adcMax = pow(2, analogResolutionBits) - 1.0;        // Maximum possible analog reading from thermistor (1024 values between 0-1023) (adc stands for analog-to-digital converter converts the analog signal from the sensor into a digital signal within the Teensy 3.5) 
float A = 0.001125308852122;                            // Steinhart - Hart equation constant
float B = 0.000234711863267;                            // Steinhart - Hart equation constant
float C = 0.000000085663516;                            // Steinhart - Hart equation constant
float R1 = 10000;                                       // Resistor value (in ohms) being used in series with the thermistor
float ThermistorData;                                   // Analog value reading from thermistor
float logR;                                             // Necessary log value used in Steinhart - Hart equation
float Tinv;                                             // Temperature in degrees kelvin inverted
float T;                                                // Temperature in degress kelvin
float currentTempC;                                     // Temperature in degrees celcius
float currentTempF;                                     // Temperature in degrees fahrenheit

// PHOTOERSISTOR CONSTANTS and VARIABLES
float PhotoresistorData;                                // Analog value reading from photoresistor

// ANALOG SENSOR VARIABLES
float AnalogSensorData;                                 // Analog sensor data

// VEML6070 SENSOR VARIABLES
float VEML6070Data;                                     

// VEML7700 SENSOR VARIABLES
float VEML7700Lux;                                      
float VEML7700White;
float VEML7700RawALS;

// AS7262 SENSOR VARIABLES
uint8_t  AS7262STemperature;
uint16_t AS7262SensorValues[AS726x_NUM_CHANNELS];
uint16_t AS7262Violet;
uint16_t AS7262Blue;
uint16_t AS7262Green; 
uint16_t AS7262Yellow; 
uint16_t AS7262Orange; 
uint16_t AS7262Red; 

// SI1145 SENSOR VARIABLES
float SI1145Visible;
float SI1145IR;
float SI1145UV;

// XBEE VARIABLES
String xBeeString;                                      // String to throw away incoming data request ("!") from transmitter 
String xBeeHeader;                                      // Header string to be sent via the xBee to the GUR
String xBeeData;                                        // Data string to be sent via the xBee to the GUR
bool xBeeHeaderSent = false;                            // Bool to allow the header to only be sent 1 time

// OLED VARIABLES
int display = 0;                                         // Variable that allows user to push button to change what is displayed on the OLED
float displayTimer = 0;                                 // Variable used in allowing the OLED to display a message for a given amount of time without stopping the rest of the program
int numberOfDisplays;
int pressTime;
int sleepDelay = 30000;                                 // Delay before display sleeps in ms

// *********** USER INPUT VARIABLES ***********
String Unit = "B3";                                     // *** MUST CHANGE THIS TO YOUR ASSIGNED UNIT (A1, A2, ..., A5; B1, B2, ..., B5; C1, C2, ..., C5; D1, D2, ..., D5)
String I2CSensorBeingUsed = "VEML7700";                   // *** MUST CHANGE THIS TO YOUR ASSIGNED I2C SENSOR ("VEML6070", "VEML7700", "AS7262", "SI1145")
String AnalogSensorBeingUsed = "GUVA-S12SD";            // *** MUST CHANGE THIS TO YOUR ASSIGNED ANALOG SENSOR ("GUVA-S12SD", "ALS-PT19")
int ledsONorOFF = 1;                                    // *** Set = 1 to enable LEDs; Set = 0 to disable LEDs


// SETUP FUNCTION
void startupProcedure();                                // Startup function which carries out the setup of the Serials, OLED, LEDs, and SENSORs
                                       
// EXTRA USER FUNCTIONS
void getHeader(String I2CSensor, String AnalogSensor);  // Functioon that sets up head based on the Analog and I2C sensors being used
void updateDataStrings(String I2CSensor);               // Funcation that updates the strings that will be printed to the serial monitor, SD card, and XBee radio
void updateTimer();                                     // Sets the 'timer' variable


void setup() {      
                                  
  startupProcedure();
  
}


void loop() {
  updateTimer();
  updateIMU();
  updateThermistor();
  updatePhotoresistor();
  updateAnalogSensor();
  updateI2CSensor(I2CSensorBeingUsed);
  updateDataStrings(I2CSensorBeingUsed);
  updateSD(Data);
  updateXBee(xBeeData);
  updateDisplay();
  delay(delayLength);
  updateDelay();
  
}


void startupProcedure() {
  int delayTime = 250;
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  for(int i = 0; i < 4; i++) {
    blinkLED(1);
    blinkLED(2);
  }
  delay(delayTime);
  
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Serial monitor connected!");
  blinkLEDs(2);
  delay(delayTime);

  Serial.print("Starting OLED setup...       ");
  OLEDSetup();
  Serial.println("complete!");
  blinkLEDs(2);
  delay(delayTime);
  

  Serial.print("Display button setup...      ");
  pinMode(BUTTON, INPUT);
  updateOLED("Button\nonline!");
  Serial.println("complete!");
  blinkLEDs(2);
  delay(delayTime);
  
 
  Serial.print("Connecting xBee serial...    ");
  XBeeSerial.begin(XBEE_BAUD_RATE);
  Serial.println("complete!");
  updateOLED("xBee\nonline!");
  blinkLEDs(2);
  delay(delayTime);

  
  Serial.print("Starting IMU setup...        ");
  IMUSetup();
  updateIMU();
  Serial.println("complete!");
  blinkLEDs(2);
  delay(delayTime);
  

  Serial.print("Starting I2C sensor setup... ");
  I2CSensorSetup(I2CSensorBeingUsed);
  Serial.println("complete!");
  updateOLED("I2C sensoronline!");
  blinkLEDs(2);
  delay(delayTime);

  Serial.print("Starting SD setup... ");
  SDSetup();
  getHeader(I2CSensorBeingUsed, AnalogSensorBeingUsed);
  blinkLEDs(2);
  delay(delayTime);

  Serial.println("Beginning logging sequence:");
  updateOLED("Data log\nbeginning");
  updateSD(header);
  blinkLEDs(3);
  delay(delayTime);

  setupTime = millis();
}



void getHeader(String I2CSensor, String AnalogSensor) {
  
  header = "Unit, Time, MagX, MagY, MagZ, AccelX, AccelY, AccelZ, GyroX, GyroY, GyroZ, TempF, TempC, Photo, " + AnalogSensor + spacer;
  xBeeHeader = String(Unit) + spacer +  "Time, TempF, TempC, Photo, " + AnalogSensor + spacer;
  
  if(I2CSensor == "VEML6070") {
    header = header + String("VEML6070");
    xBeeHeader = xBeeHeader + String("VEML6070") + delimiter;
  }

  else if(I2CSensor == "VEML7700") {
    header = header + String("Lux") + spacer + String("White") + spacer + String ("RawALS");
    xBeeHeader = xBeeHeader + String("Lux") + spacer + String("White") + spacer + String ("RawALS") + delimiter;
  }

  else if(I2CSensor == "AS7262") {
    header = header + String("Temperature") + spacer + String("Violet") + spacer + String("Blue") + spacer + String("Green") + spacer + String("Yellow") + spacer + String("Orange") + spacer + String("Red");
    xBeeHeader = xBeeHeader + String("Temperature") + spacer + String("Violet") + spacer + String("Blue") + spacer + String("Green") + spacer + String("Yellow") + spacer + String("Orange") + spacer + String("Red") + delimiter;
  }

  else if(I2CSensor == "SI1145") {
    header = header + String("Visible") + spacer + String("IR") + spacer + String("UV");
    xBeeHeader = xBeeHeader + String("Visible") + spacer + String("IR") + spacer + String("UV") + delimiter;
  }

  else {
    Serial.println("Error - (in getHeader()): Please change the User Input Variable 'I2CSensorBeingUsed' to one of the four I2C sensor options!");
    Serial.println("Exiting program!");
    while(1) {}
  }
}



void updateDataStrings(String I2CSensor) {
  
  Data = Unit + spacer + String((millis() - setupTime)/1000) + spacer + String(magnetometer[0]) + spacer + String(magnetometer[1]) + spacer + String(magnetometer[2]) + spacer;
  Data = Data + String(accelerometer[0]) + spacer + String(accelerometer[1]) + spacer + String(accelerometer[2]) + spacer;
  Data = Data + String(gyroscope[0]) + spacer + String(gyroscope[1]) + spacer + String(gyroscope[2]) + spacer;
  Data = Data + String(currentTempF) + spacer + String(currentTempC) + spacer;
  Data = Data + String(PhotoresistorData) + spacer + String(AnalogSensorData) + spacer;

  xbeeLines++;
  if(xbeeLines > 1){
    xBeeData = xbeeData + Data;
  }
  else if(xbeeLines = 1){
    xBeeData = Data;
  }
  else{
    xBeeData = Data;
    xbeeLines = 0;
    serial.println("!!!!! Error with xbeeLines !!!!!");
  }

  if(I2CSensor == "VEML6070") {
    Data = Data + String(VEML6070Data);
    xBeeData = xBeeData + String(VEML6070Data) + delimiter;
  }
  else if(I2CSensor == "VEML7700") { 
    Data = Data + String(VEML7700Lux) + spacer + String(VEML7700White) + spacer + String (VEML7700RawALS);
    xBeeData = xBeeData + String(VEML7700Lux) + spacer + String(VEML7700White) + spacer + String (VEML7700RawALS) + delimiter;
  }
  else if(I2CSensor == "AS7262") {
    Data = Data + String(AS7262STemperature) + spacer + String(AS7262Violet) + spacer + String(AS7262Blue) + spacer + String(AS7262Green) + spacer + String(AS7262Yellow) + spacer + String(AS7262Orange) + spacer + String(AS7262Red);
    xBeeData = xBeeData + String(AS7262STemperature) + spacer + String(AS7262Violet) + spacer + String(AS7262Blue) + spacer + String(AS7262Green) + spacer + String(AS7262Yellow) + spacer + String(AS7262Orange) + spacer + String(AS7262Red) + delimiter;
  }
  else if(I2CSensor == "SI1145") {
    Data = Data + String(SI1145Visible) + spacer + String(SI1145IR) + spacer + String(SI1145UV);
    xBeeData = xBeeData + String(SI1145Visible) + spacer + String(SI1145IR) + spacer + String(SI1145UV) + delimiter;
  }
  else {
    Serial.println("Error - (in updateDataStrings()): Please change the variable 'I2CSensorBeingUsed' to one of the four I2C sensor options!");
    Serial.println("Exiting program!");
    updateOLED("Error!\n\nExiting\nprogram!");
    while(1) {}
  }                  
}


void updateTimer() {
  timeS = (millis() - setupTime)/1000;                                     // Time we are converting
  int hr = timeS/3600;                                                         // Number of hours
  int mins = (timeS-hr*3600)/60;                                               // Remove the number of hours and calculate the minutes.
  int sec = timeS-hr*3600-mins*60;                                            // Remove the number of hours and minutes, leaving only seconds.
  timer = (String(hr) + ":" + String(mins) + ":" + String(sec));             // Converts to HH:MM:SS string
  if(sec < 10)
  {
    timer = (String(hr) + ":" + String(mins) + ":0" + String(sec));
  }
}

void updateDelay() {
  if(abs(accelPrev[0]-accelerometer[0]) > accelTolerance || abs(accelPrev[1]-accelerometer[1]) > accelTolerance || abs(accelPrev[2]-accelerometer[2]) > accelTolerance)
  {
    startTime = timeS;
    delayLength = delayFast;
  }
  if((timeS - startTime) > ((fastDataTime)))
  {
    delayLength = delaySlow;
  }
}



    
