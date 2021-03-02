/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: Analog Sensor Functions                                  |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                          
 ----------------------------------------------------------------------------------------------*/

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
  PhotoresistorData = analogRead(PHOTO);                // May need proper formula to get useful values -- otherwise will just see varying analog values
}

void updateAnalogSensor() {
  AnalogSensorData = analogRead(ANALOGSENSOR);          // May need proper formula to get useful values -- otherwise will just see varying analog values
}
