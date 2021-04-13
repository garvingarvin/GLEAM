/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: SD Card Functions                                        |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                     
 ----------------------------------------------------------------------------------------------*/

void SDSetup(){
  pinMode(chipSelect, OUTPUT);
  if(!SD.begin(chipSelect)) {
    Serial.println("SD card failed, or not present");
    updateOLED("SD Card\nfailed\nor\nnot\npresent");
    delay(1000); 
  }
  else {
    Serial.print("        card initialized! \nCreating File...             ");
    for (byte i = 0; i<100; i++) {
      filename[3] = '0' + i/10;
      filename[4] = '0' + i%10;
      if(!SD.exists(filename)) {
        datalog = SD.open(filename, FILE_WRITE);
        sdActive = true;
        Serial.println("complete!");
        Serial.println("Logging to: " + String(filename));
        updateOLED("SD\nonline!");
        delay(500);
        updateOLED("Logging:\n\n" + String(filename));
        delay(500);
        break;}
      }

      if(!sdActive) {
        Serial.println("No available file names; clear SD card to enable logging");
        for(int i = 0; i<4; i++) {
        updateOLED("Warning:\n\nSD Card\nfull!\n\nClear ASAP");
        blinkLEDs(1);
        delay(500);
        updateOLED("");
        delay(500);
        }
        updateOLED("Warning:\n\nSD Card\nfull!\n\nClear ASAP");
        delay(2000);
    }
  }
}


void updateSD(String text) {                                
  datalog = SD.open(filename, FILE_WRITE);
  datalog.println(text);
  datalog.close();
  blinkLED(1);
  dataLogs++;
  Serial.println(text);
}
