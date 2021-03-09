/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: I2C Components Functions                                 |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                     
 ----------------------------------------------------------------------------------------------*/

void I2CSensorSetup(String I2CSensor) {
  
  if (I2CSensor == "VEML6070") {
    veml6070.begin(VEML6070_1_T);
    numberOfDisplays = 6;
  }

  else if (I2CSensor == "VEML7700") {
    veml7700.begin();
    veml7700.setGain(VEML7700_GAIN_1);
    veml7700.setIntegrationTime(VEML7700_IT_800MS);
    veml7700.setLowThreshold(10000);
    veml7700.setHighThreshold(20000);
    veml7700.interruptEnable(true);
    numberOfDisplays = 6;
  }

  else if (I2CSensor == "AS7262") {
    AS.begin();
    numberOfDisplays = 7;
  }

  else if (I2CSensor == "SI1145") {
    SI.begin();
    numberOfDisplays = 6;
  }

  else {
    Serial.println("Error - (in I2CSensorSetup()): Please change the User Input Variable 'I2CSensorBeingUsed' to one of the four I2C sensor options and reset system!");
    Serial.println("Exiting program!");
    updateOLED("Error!\n\nExiting\nprogram!");
    while(1) {}   
  }
}


void updateI2CSensor(String I2CSensor) {

  if (I2CSensor == "VEML6070") {
    VEML6070Data = veml6070.readUV();
  }

  else if (I2CSensor == "VEML7700") {
    VEML7700Lux = veml7700.readLux();
    VEML7700White = veml7700.readWhite();
    VEML7700RawALS = veml7700.readALS(); 
  }

  else if (I2CSensor == "AS7262") {
    AS7262STemperature = AS.readTemperature();
    AS.startMeasurement();
    bool ready = false;
    while(!ready){
      delay(5);
      ready = AS.dataReady();
    }

    AS.readRawValues(AS7262SensorValues);
    
    AS7262Violet = AS7262SensorValues[AS726x_VIOLET];
    AS7262Blue = AS7262SensorValues[AS726x_BLUE];
    AS7262Green = AS7262SensorValues[AS726x_GREEN];
    AS7262Yellow = AS7262SensorValues[AS726x_YELLOW];
    AS7262Orange = AS7262SensorValues[AS726x_ORANGE];
    AS7262Red = AS7262SensorValues[AS726x_RED];
  }

  else if (I2CSensor == "SI1145") {
    SI1145Visible = SI.readVisible();
    SI1145IR = SI.readIR();
    SI1145UV = SI.readUV() / 100.0;
  }

  else {
    Serial.println("Error - (in updateI2CSensor()): Please change the User Input Variable 'I2CSensorBeingUsed' to one of the four I2C sensor options!");
    Serial.println("Exiting program!");
    updateOLED("Error!\n\nExiting\nprogram!");
    while(1) {}
  }
}
