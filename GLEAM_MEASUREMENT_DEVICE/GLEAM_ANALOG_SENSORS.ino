/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: Analog Sensor Functions                                  |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                          
 ----------------------------------------------------------------------------------------------*/
#define VIN 3.3 // voltage @@@8
#define R 10000 // omhs @@@

void updateThermistor() {
  analogReadResolution(analogResolutionBits);
  ThermistorData = analogRead(THERM);
  logR = log(((adcMax/ThermistorData)-1)*R1);
  Tinv = A + B * logR + C * logR * logR * logR;         // Steinhart - Hart equation
  T = 1/Tinv;
  currentTempC = T - 273.15;
  currentTempF = currentTempC * 9 / 5 + 32;
}



void updatePhotoresistor() {
  PhotoresistorData =500/(((R*(VIN-(analogRead(PHOTO)*(3.3/16384.0))))/(analogRead(PHOTO)*(3.3/16384.0)))/1000);                // Formula for analog to voltage to resistance to lumen@@@@@@@@@@@@@@
}

void updateAnalogSensor() {
  AnalogSensorData = (analogRead(ANALOGSENSOR)*(3.3/16384.0))/0.1;          // in analog to voltage to UV index@@@@@@@@@@@@@@@@@@@@@@
}
