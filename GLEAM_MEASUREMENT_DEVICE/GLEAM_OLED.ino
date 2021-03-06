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
}


void updateOLED(String text) {
  
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println(text);
  oled.display();
  
}


void getDisplay() {

  if (millis() - displayTimer > 2000){                   // Allows the OLED to keep the message "Request from GUT! Data sent via xBee to GUR!" displayed for a longer period of time while still running code
    digitalWrite(LED2, LOW);
    if(digitalRead(buttonPin) == HIGH) {
       button++;
       if(button > 5) button = 0;
     }
  
   switch(button) {
      case 0: updateOLED(String(currentTempF)+ " F" + endline + String(currentTempC) + " C" + endline + String(PhotoresistorData) + endline + String(AnalogSensorData)); break;
      case 1: updateOLED("Mag Vals" + endline + endline + "X: " + String(magnetometer[0]) + endline + "Y: " + String(magnetometer[1]) + endline + "Z: " + String(magnetometer[2])); break;
      case 2: updateOLED("Gryo Vals" + endline + endline + "X: " + String(gyroscope[0]) + endline + "Y: " + String(gyroscope[1]) + endline + "Z: " + String(gyroscope[2])); break;
      case 3: updateOLED("Accel Vals" + endline + "X: " + String(accelerometer[0]) + endline + "Y: " + String(accelerometer[1]) + endline + "Z: " + String(accelerometer[2])); break;
      case 4: updateOLED("R: " + String(roll) + endline + endline + "P: " + String(pitch) + endline + endline + "H: " + String(heading)); break;
      case 5: if (sdActive) {updateOLED("Unit: " + Unit + endline + String(filename) + "\n\nLog: " + String(dataLogs) + "   " + endline + timer);} else {updateOLED("Unit: " + Unit + endline + "Clear SD!"+ "\n\nLog: " + String(dataLogs) + "   " + endline + timer);} break;
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
