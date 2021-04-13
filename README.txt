Fork created by GLEAM Team B in order to implement code improvements without affecting the main version

!!! CHANGE LINES 164-167 IN GLEAM_MEASUREMENT_DEVICE !!!

Changed:
-Added version # and date on startup
-Added function to alter delayLength based on various factors
-Increase data collection rate for a specified time after accelerometer threshhold reached
-Display "sleeps" after the button hasn't been pressed in a while
-Option to only flash LED periodically instead of every loop
-Default screen to data collection page instead of temperature page
-"Data sent" stat on data collection page instead of the message appearing every time

Not Implemented:
-Send all the data since the last transfer instead of just the current line
