/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: XBee Radio Functions                                     |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                  
 ----------------------------------------------------------------------------------------------*/

void updateXBee(String text) {
 if(xBee.available()) {
  Serial.println("\nData request received from GUT!\n");
  xBeeString = xBee.read();
   if (xBeeHeaderSent == false) {
    xBee.print(xBeeHeader);
    Serial.println(xBeeHeader);
    Serial.println("\nHeader sent to GUR!\n");
    xBeeHeaderSent = true;
   }
  else {
    xBee.print(text);
    Serial.println(text);
    Serial.println("\nData sent to GUR via xBee!\n");
    updateOLED("Request\nfrom GUT!\nData sent\nvia xBee\nto GUR!");
    displayTimer = millis();
    blinkLED(2);
    }
  }
}
