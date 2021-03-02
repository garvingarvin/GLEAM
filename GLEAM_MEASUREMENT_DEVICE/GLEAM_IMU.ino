/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Measurement Device: IMU Functions                                            |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                           
 ----------------------------------------------------------------------------------------------*/
 
void IMUSetup() {
  Wire.begin();
  if(!imu.begin()) {
    Serial.println("Failed to communicate with IMU.");
    delay(500);
  }

  else{
    updateOLED("IMU\nonline!");
    delay(500);
  }
}


void updateIMU() {

  if (imu.magAvailable()) imu.readMag();
  if (imu.accelAvailable()) imu.readAccel();
  if (imu.gyroAvailable()) imu.readGyro();

  magnetometer[0] = imu.calcMag(imu.mx);
  magnetometer[1] = imu.calcMag(imu.my);
  magnetometer[2] = imu.calcMag(imu.mz);
  accelerometer[0] = imu.calcAccel(imu.ax);
  accelerometer[1] = imu.calcAccel(imu.ay);
  accelerometer[2] = imu.calcAccel(imu.az);
  gyroscope[0] = imu.calcGyro(imu.gx);
  gyroscope[1] = imu.calcGyro(imu.gy);
  gyroscope[2] = imu.calcGyro(imu.gz);

  updateRoll();
  updatePitch();
  updateHeading();
}


// ADDITIONAL FUNCTIONS OF IMU 
void updateRoll() {

 roll = atan2(accelerometer[1], accelerometer[2]);
 roll *= 180.0 / PI;
  
}


void updatePitch() {

  pitch = atan2(-accelerometer[0], sqrt(accelerometer[1]*accelerometer[1] + accelerometer[2]*accelerometer[2]));
  pitch *= 180.0 / PI;
  
}


void updateHeading() {
  
  if (magnetometer[1] == 0) {
    heading = (magnetometer[0] < 0) ? PI : 0;
  }
  
  else {
    heading = atan2(magnetometer[0], magnetometer[1]);
    heading -= DECLINATION * PI / 180;
  }
  
   if(heading > PI) { heading -= (2 * PI); }
   
   else if (heading < -PI) { heading += (2 * PI);}
   
    heading *= 180.0 / PI;
}
