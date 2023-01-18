/*
This is NOT a remote control testing code.
All remote control content was deleted from
this file, however, file name was not changed
for the sake of simplicity. There is no more
remote control anywhere in this file!!
*/

#include "CytronMotorDriver.h" 	// Brushed motor 
#include <Wire.h> 		// I2C for IMU
#include <LSM6.h> 		// Orientation sensing IMU
#include <SPI.h>
#include <SD.h>
#include <Encoder.h>


//storage variables
volatile int32_t SPEED = 0;
volatile double old_pos = 0; 
volatile double prev_error = 0;
volatile double integral = 0;
volatile const double  k = 0.1;
volatile double derivitive = 0;
// Configure the motor driver.
CytronMD motor(PWM_DIR, 9, 8);  // PWM = Pin 9, DIR = Pin 8.


const bool PRINT = true; // debug bool
const double pulley_dia = 12.0;
double set_dist = -20000; //set point for distance for string to travel

void setup() {
  pid_setup();
  if(PRINT)
    Serial.begin(115200);
    //setup_error();
    //setup_pwm_read();
    //setup_encoder();

 /* if(!setup_IMU()){
    Serial.println("No IMU");
    //print("IMU not here");
    //print_error("IMU Disconnected");
  }
  */
}

 Encoder enc = setup_encoder ();

void loop() {  
  //Serial.print(millis());
  //Serial.print(",");
  Serial.print(SPEED);
  Serial.print(",");
  //Serial.print(" Current position: ");
  Serial.print(old_pos);
  //Serial.print(" Previous error: ");
  //Serial.print(prev_error);
  //Serial.print(" Integral: ");
  //Serial.print(integral);
  //Serial.print(" Derivitive: ");
  //Serial.print(derivitive);
  Serial.println();
  

}
