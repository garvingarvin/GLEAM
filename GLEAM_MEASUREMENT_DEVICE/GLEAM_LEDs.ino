/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: LED Functions                                            |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                         
 ----------------------------------------------------------------------------------------------*/

void blinkLED(int x) {
  if (ledsONorOFF == 1) {
    if (x == 1) {
      digitalWrite(LED1, HIGH);
      delay(50);
      digitalWrite(LED1, LOW);
    }
  
    if (x == 2) {
      digitalWrite(LED2, HIGH);
      delay(50);
      digitalWrite(LED2, LOW);
    }
  
    if(x != 1 && x != 2) {
      {Serial.println("Error: 'x' value inputted into function 'blinkLED(x)' not valid! - - - Please use x = 1 or x = 2"); updateOLED("Error:\nblinkLED\nUse valid\nx input!");}
      while(1){}
    }
  }
}


void blinkLEDs(int x) {

  if (ledsONorOFF == 1) {
    for (int i = 0; i<x; i++) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      delay(50);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      delay(50);
    }
  }
}
