/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: Micro OLED Functions                                     |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                          
 ----------------------------------------------------------------------------------------------*/

void OLEDSetup() {
  Wire.begin();
  oled.begin();
  oled.clear(ALL);
  oled.display();
  oled.clear(PAGE);
  randomSeed(analogRead(A0) + analogRead(A1));
  lines();
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.setCursor(0,0);
  oled.println("GLEAM\nDevice\nUnit " + String(Unit));
  oled.display();
  delay(1500);

  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println("Version:\n" + version_num + "\n\nDate:\n" + date);
  oled.display();
  delay(3000);
}


void updateOLED(String text) {
  
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println(text);
  oled.display();
  
}


void updateDisplay() {

  if (millis() - displayTimer > 2000){                   // Allows the OLED to keep the message "Request from GUT! Data sent via xBee to GUR!" displayed for a longer period of time while still running code
    digitalWrite(LED2, LOW);
    if(digitalRead(BUTTON) == HIGH) {
       display++;
       pressTime = millis();
       if(display > numberOfDisplays) display = 0;
     }
  if(millis() > (sleepDelay + pressTime)){
    if(millis() > (sleepDelay + pressTime + 5000)){
      updateOLED("");
      return;
    }
    else{
      updateOLED("Display\nSleeping\n\nZzzzzz...");
      return;
    }
  }
  
  if(I2CSensorBeingUsed == "AS7262") {
    switch(display) {
      case 0: if (sdActive) {updateOLED("Unit: " + Unit + endline + String(filename) + "   \nLog: " + String(dataLogs) + endline +  "Sent: " + String(packetsSent) + endline + timer);} else {updateOLED("Unit: " + Unit + endline + "No/Clr SD!"+ "\nLog: " + String(dataLogs) + endline + "Sent: " + String(packetsSent) + endline + timer);} break;
      case 1: updateOLED("Temp\nFarhenheit" + String(currentTempF) + endline + "\nCelcius\n" + String(currentTempC)); break;
      case 2: updateOLED("Photo:\n" + String(PhotoresistorData) + endline + endline + "Analog:\n" + String(AnalogSensorData)); break;
      case 3: updateOLED("Mag Vals" + endline + endline + "X: " + String(magnetometer[0]) + endline + "Y: " + String(magnetometer[1]) + endline + "Z: " + String(magnetometer[2])); break;
      case 4: updateOLED("Gryo Vals" + endline + endline + "X: " + String(gyroscope[0]) + endline + "Y: " + String(gyroscope[1]) + endline + "Z: " + String(gyroscope[2])); break;
      case 5: updateOLED("Accel Vals" + endline + "X: " + String(accelerometer[0]) + endline + "Y: " + String(accelerometer[1]) + endline + "Z: " + String(accelerometer[2])); break;
      case 6: updateOLED("Violet:\n" + String(AS7262Violet) + endline + "Blue:\n" + String(AS7262Blue) + endline + "Green:\n" + String(AS7262Green)); break;
      case 7: updateOLED("Yellow:\n" + String(AS7262Yellow) + endline + "Orange:\n" + String(AS7262Orange) + endline + "Red:\n" + String(AS7262Red)); break;
     }
  }
  else if(I2CSensorBeingUsed == "VEML6070") {
    switch(display) {
case 0: if (sdActive) {updateOLED("Unit: " + Unit + endline + String(filename) + "   \nLog: " + String(dataLogs) + endline +  "Sent: " + String(packetsSent) + endline + timer);} else {updateOLED("Unit: " + Unit + endline + "No/Clr SD!"+ "\nLog: " + String(dataLogs) + endline + "Sent: " + String(packetsSent) + endline + timer);} break;
      case 1: updateOLED("Temp\nFarhenheit" + String(currentTempF) + endline + "\nCelcius\n" + String(currentTempC)); break;
      case 2: updateOLED("Photo:\n" + String(PhotoresistorData) + endline + endline + "Analog:\n" + String(AnalogSensorData)); break;
      case 3: updateOLED("Mag Vals" + endline + endline + "X: " + String(magnetometer[0]) + endline + "Y: " + String(magnetometer[1]) + endline + "Z: " + String(magnetometer[2])); break;
      case 4: updateOLED("Gryo Vals" + endline + endline + "X: " + String(gyroscope[0]) + endline + "Y: " + String(gyroscope[1]) + endline + "Z: " + String(gyroscope[2])); break;
      case 5: updateOLED("Accel Vals" + endline + "X: " + String(accelerometer[0]) + endline + "Y: " + String(accelerometer[1]) + endline + "Z: " + String(accelerometer[2])); break;
      case 6: updateOLED(String(I2CSensorBeingUsed) + ":\n\n" + String(VEML6070Data)); break;
    }
  }
    else if(I2CSensorBeingUsed == "VEML7700") {
      switch(display) {
case 0: if (sdActive) {updateOLED("Unit: " + Unit + endline + String(filename) + "   \nLog: " + String(dataLogs) + endline +  "Sent: " + String(packetsSent) + endline + timer);} else {updateOLED("Unit: " + Unit + endline + "No/Clr SD!"+ "\nLog: " + String(dataLogs) + endline + "Sent: " + String(packetsSent) + endline + timer);} break;
      case 1: updateOLED("Temp\nFarhenheit" + String(currentTempF) + endline + "\nCelcius\n" + String(currentTempC)); break;
      case 2: updateOLED("Photo:\n" + String(PhotoresistorData) + endline + endline + "Analog:\n" + String(AnalogSensorData)); break;
      case 3: updateOLED("Mag Vals" + endline + endline + "X: " + String(magnetometer[0]) + endline + "Y: " + String(magnetometer[1]) + endline + "Z: " + String(magnetometer[2])); break;
      case 4: updateOLED("Gryo Vals" + endline + endline + "X: " + String(gyroscope[0]) + endline + "Y: " + String(gyroscope[1]) + endline + "Z: " + String(gyroscope[2])); break;
      case 5: updateOLED("Accel Vals" + endline + "X: " + String(accelerometer[0]) + endline + "Y: " + String(accelerometer[1]) + endline + "Z: " + String(accelerometer[2])); break;
      case 6: updateOLED("Lux:\n" + String(VEML7700Lux) + endline + "White:\n" + String(VEML7700White) + endline + "RawALS:\n" + String(VEML7700RawALS)); break;
      
    }
  }
    else if(I2CSensorBeingUsed == "SI1145") {
      switch(display) {
case 0: if (sdActive) {updateOLED("Unit: " + Unit + endline + String(filename) + "   \nLog: " + String(dataLogs) + endline +  "Sent: " + String(packetsSent) + endline + timer);} else {updateOLED("Unit: " + Unit + endline + "No/Clr SD!"+ "\nLog: " + String(dataLogs) + endline + "Sent: " + String(packetsSent) + endline + timer);} break;
      case 1: updateOLED("Temp\nFarhenheit" + String(currentTempF) + endline + "\nCelcius\n" + String(currentTempC)); break;
      case 2: updateOLED("Photo:\n" + String(PhotoresistorData) + endline + endline + "Analog:\n" + String(AnalogSensorData)); break;
      case 3: updateOLED("Mag Vals" + endline + endline + "X: " + String(magnetometer[0]) + endline + "Y: " + String(magnetometer[1]) + endline + "Z: " + String(magnetometer[2])); break;
      case 4: updateOLED("Gryo Vals" + endline + endline + "X: " + String(gyroscope[0]) + endline + "Y: " + String(gyroscope[1]) + endline + "Z: " + String(gyroscope[2])); break;
      case 5: updateOLED("Accel Vals" + endline + "X: " + String(accelerometer[0]) + endline + "Y: " + String(accelerometer[1]) + endline + "Z: " + String(accelerometer[2])); break;
      case 6: updateOLED("Visible:\n" + String(SI1145Visible) + endline + "Infrared:\n" + String(SI1145IR) + endline + "Ult Viol:\n" + String(SI1145UV)); break;
    }
  }
    else {
      Serial.println("Error - (in updateDisplay()): Please change the User Input Variable 'I2CSensorBeingUsed' to one of the four I2C sensor options and reset system!");
      Serial.println("Exiting program!");
      updateOLED("Error!\n\nExiting\nprogram!");
      while(1) {}   
    }
  }

  else {digitalWrite(LED2, HIGH);}
}


void lines()
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
  int xEnd, yEnd;
  int lineWidth = min(middleX, middleY);


  for (int i=0; i<1; i++)
  {
    for (int deg=-90; deg<270; deg+=15)
    {
      xEnd = lineWidth * cos(deg * PI / 180.0);
      yEnd = lineWidth * sin(deg * PI / 180.0);

      oled.line(middleX, middleY, middleX + xEnd, middleY + yEnd);
      oled.display();
      delay(10);
    }
    for (int deg=-75; deg<285; deg+=15)
    {
      xEnd = lineWidth * cos(deg * PI / 180.0);
      yEnd = lineWidth * sin(deg * PI / 180.0);

      oled.line(middleX, middleY, middleX + xEnd, middleY + yEnd, BLACK, NORM);
      oled.display();
      delay(10);
    }
  }
}
