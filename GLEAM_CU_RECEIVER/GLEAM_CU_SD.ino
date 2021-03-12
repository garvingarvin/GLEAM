/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Ground Unit Receiver: SD Card Functions                                      |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                          
 ----------------------------------------------------------------------------------------------*/

void setupSD() {
  
  pinMode(chipSelect, OUTPUT);
  if(!SD.begin(chipSelect)) {
    Serial.println("SD card failed, or not present");
    delay(1000); 
  }
  else {
    Serial.print("      card initialized! \nCreating File...                   ");
    for (byte i = 0; i<100; i++) {
      filename[4] = '0' + i/10;
      filename[5] = '0' + i%10;
      if(!SD.exists(filename)) {
        datalog = SD.open(filename, FILE_WRITE);
        sdActive = true;
        Serial.println("complete!");
        updateOLED("SD Card\nonline!");
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


void updateSD() {
  datalog = SD.open(filename, FILE_WRITE);
  datalog.println(dataString);
  datalog.close();
  dataLogs++;
  blinkLED(2);
}
