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
  delay(250);
  updateOLED("OLED\nonline!");
}


void updateOLED(String text) {
  if (OLEDPresentOnBoard == true) {
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println(text);
  oled.display();
  }
}


void getDisplay() {
if (OLEDPresentOnBoard == true) {
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
      case 5: updateOLED("Unit: " + Unit + endline + String(filename) + "\n\nLog: " + String(dataLogs) + "   " + endline + timer); break;
     }
  }

  else {digitalWrite(LED2, HIGH);}
}
}
