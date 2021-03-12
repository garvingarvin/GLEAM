/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Ground Unit Receiver: OLED Functions                                         |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                          
 ----------------------------------------------------------------------------------------------*/

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


void updateOLED(String text) {
  
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.println(text);
  oled.display();
}


void updateDisplay() {
  if(digitalRead(BUTTON) == HIGH) {
       display++;
       if(display > 1) display = 0;
     }

   switch(display) {
    case 0: updateOLED(recentUnit); recentUnit = ""; break;
    case 1: updateTimer(); updateOLED(String(filename) + endline + endline + "Logs: " + String(dataLogs) + endline + endline + timer);; break;
   }
}


void updateTimer() {
  int time = millis()/1000;                                     // Time we are converting
  int hr = time/3600;                                                         // Number of hours
  int mins = (time-hr*3600)/60;                                               // Remove the number of hours and calculate the minutes.
  int sec = time-hr*3600-mins*60;                                            // Remove the number of hours and minutes, leaving only seconds.
  timer = (String(hr) + ":" + String(mins) + ":" + String(sec));             // Converts to HH:MM:SS string
}
