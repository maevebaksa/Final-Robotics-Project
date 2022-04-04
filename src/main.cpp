#include <Arduino.h>
#include <Servo.h>

//some of the following is taken from the previous Arduino challenges.


//*** HARDWARE SETTINGS ****
//variables for the pins
int servopinright = 12;
int servopinleft = 13;

Servo rightservo;
Servo leftservo;

int sensorpinfront = 0; 
int sensorpinright = 1;
int sensorpinleft = 2;

int ledpinfront = 3;
int ledpinright = 2;
int ledpinleft = 4;


//***** HARDWARE DRIVE TRAIN CALIBRATION ***
//set this to 1 in order to enable the motors to just be at 1500 1500 to tune their 0 points, do this first before
//the software calibration
//how to calibrate:
//(1) set this value to 1 and upload the code.
//(2) use a fine screwdriver on the back of the servo motor (looks like a small screw) to set the 0 point of the motor
//    by slowly turning "the screw" (a potentiometer) on the back until the motor is completely still. This requires 
//    very fine control and it may take a while.
//(3) reset this value to 0 and reupload the code.
int calibrationenabled = 0;


//***** SOFTWARE DRIVE TRAIN CALIBRATION ****
//calibration data software jank 
//how to calibrate:
//(1) start with 1300 and 1700 and make sure that the robot is driving in the right direction, if not, you will have to 
//    switch the 1300 and 1700 around.
//(2) see which way the robot is veering
//(3) if the robot is veering to the left, then you will need to increase the left value proportionally to the right
//    value. This means you can bring the right value closer to 1500 slightly, decreasing the speed on the right motor
//(4) if the robot is verring to the right, then you need to do the opposite, increasing the right value proportionally
//    to the left value. This means you can bring the left value closer to 1500, decreasing the speed on the right motor.
//(5) continue adjusting in increments of 50 at first, then 10, and then down to +-1. Small changes make a large
//    difference here, especially the closer you are to 1500. You'll notice that you've gotten close by the 
//    direction the robot is veering in changing. Once that happens, you can slowly tweak the value back in the other 
//    direction to get the precise value.
//(6) enjoy!
int right = 1590;
int left = 1300;


//***** SOFTWARE SENSOR CALIBRATION ****
//how to calibrate:
//(1) start with enabling serial monitoring (set to 1)
int serialmonitoring = 0;
//(2) calibrate the front sensor by placing the robot onto the line, and moving it around, note down these values
//(2a) continue by placing the robot off of the line, and noting down these values
//(2b) find a value, that is approximately in the middle, make sure that throughout the entire length of the line
// the value does not increase above this value 
int frontthreshold = 35;
//(3) calibrate the side sensors in the opposite way, by placing the robot onto the line for one side sensor, noting down these values
//(3a) continue by placing the robot in the middle of the line so that the side sensors are reading off the line, noting down these values
//(3b) find a value, that is approximately in the middle, make sure that throughout moving the robot down the line so that
// the sensors aren't on the line, the value doesn't drop BELOW this value
//(3c) repeat for other side
int rightthreshold = 35;
int leftthreshold = 35;





void setup() {
  //enable serial mon
  Serial.begin(9600);

  //attach pins
  rightservo.attach(servopinright);
  leftservo.attach(servopinleft);

  //set io
  pinMode(ledpinfront, OUTPUT);
  pinMode(ledpinleft,OUTPUT);
  pinMode(ledpinright, OUTPUT);

  
}

void loop() {
  //sensor calibration code
  if (serialmonitoring == 1){

    //printing the values of the pins, check threshold, enable LED accordingly

    //hold the values of the analog pins for use later
    int righthold  = analogRead(sensorpinright);
    int lefthold = analogRead (sensorpinleft);
    int fronthold = analogRead(sensorpinfront);

    //start with the right pin
    Serial.println("Right:")
    Serial.println(righthold);
    
    if (righthold < rightthreshold){
      digitalWrite(ledpinright, HIGH);
    }
    else{
      digitalWrite(ledpinright, LOW);
    }



  }

  //motor calibration code
  else if (calibrationenabled == 1){

    //this is used in my other code, set the motors to simply mid values so they can be trammed
    leftservo.writeMicroseconds(1500);
    rightservo.writeMicroseconds(1500);
    delay(900000);
  }

  //actual code
  else{

    //hold the values of the analog pins for use later
    int righthold  = analogRead(sensorpinright);
    int lefthold = analogRead (sensorpinleft);
    int fronthold = analogRead(sensorpinfront);


  }

}