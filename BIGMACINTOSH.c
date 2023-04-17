/*
Coders: Shaan Banday (20993610) and Sabrina Mogus (21009761)
Group: 34
Class: ME 101
*/

//Functions from Lecture 12

void configureAllSensors() //Void function which configures all sensors
{
	//Set sensors for robot in default configuration
	SensorType[S1] = sensorEV3_Touch; //Set port 1 to touch sensor
	SensorType[S2] = sensorEV3_Ultrasonic; //Set port 2 to ultrasonic
	SensorType[S3] = sensorEV3_Color; //Set port 3 to color sensor
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur

	SensorMode[S3] = modeEV3Color_Color; //Set color sensor to color mode
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur

	SensorType[S4] = sensorEV3_Gyro; //Set port 4 to gyro sensor
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur

	SensorMode[S4] = modeEV3Gyro_Calibration; //reset the gyro sensor
	wait1Msec(100); //Pause thread for 100 ms to let calibration occur

	SensorMode[S4] = modeEV3Gyro_RateAndAngle; //Set gyro sensor
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur
} //end of function, return to main task

//function prints group number on a certain line
void printInfo(int group_number, int line_number)
{
	//display on EV3 Brick
	displayString (line_number, "Group %f, SB SM", group_number);
}

 //Void function sets motors to the same power
void samePower(int time_in_ms, int motor_power)
{
  //Drive forward
	motor[motorA] = motor_power; //Drive motor A at set power %
	motor[motorD] = motor_power; //Drive motor D at same power % as A

	//Duration
	wait1Msec(time_in_ms); //Pause thread to keep moving forward

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
}

//Void function sets motors to different power
void diffPower(int time_in_ms, int powerA, int powerD)
{
	//Rotate
	motor[motorA] = powerA; //Drive motor A at power A%
  motor[motorD] = powerD; //Drive motor D at power D%

  //Duration
	wait1Msec(time_in_ms); //Pause thread to keep moving forward

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
}

//Rotate the robot to a target angle (from PDF provided)
void rotateRobot (int target_angle, int motor_power)
{
  resetGyro(S4); //Reset gyro sensor in sensor spot 4

  //Decisions
  if (target_angle > 0) //If target angle is greater than 0
  {
		//Turn clockwise
		motor[motorD] = motor_power;
		motor[motorA] = -motor_power;

		while (SensorValue[S4] < target_angle) //Keep turning
		{
		}

		//Stop
		motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
		motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
	}

	else if (target_angle < 0)  //If target angle is less than 0
	{
		//Turn counter-clockwise
		motor[motorD] = -motor_power;
		motor[motorA] = motor_power;

		while (SensorValue[S4] > target_angle) //Keep turning
		{
		}

		//Stop
		motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
		motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
	}

	else {} //Otherwise, if target angle is zero, do nothing
}

void drive_from_colour(int time_pressed, int colour_detected)
{

  //Declaring variables
  int angle = 0, motor_power = 30, motor_powerA = -45,
  int motor_powerD = -35;

  configureAllSensors(); //call function to configure all sensors

  //Decisions
  if (colour_detected == (int)colorRed) //If sensed red
  {
  	angle = 45; //Set angle to postive 45 (clockwise)
    rotateRobot(angle, motor_power); //call rotate robot function
    samePower(time_pressed, motor_power); //move robot forward
  }
  else if (colour_detected == (int)colorBlue) //if sensed blue
  {
    angle = -90; //Set angle to negative 90 (ounter-clockwise)
    diffPower(time_pressed, motor_powerA, motor_powerD); //Drive back
    rotateRobot(angle, motor_power); //call rotate robot function
  }

  else {} //Otherwise, if any other colour is detected, do nothing
}

task main() //main function
{
  //Declare all variables
	int group = 34, line = 5;
	printInfo(group, line); //Call function to print info

	//Loops
	for (int i = 0; i < 5; i++) //run this 5 times
	{
		//Declare all variables within the scope of the loop
		int time_elapsed = 0, colour = 0; //int for time elapsed and colour

		while(!getButtonPress(buttonAny)) {} //press
		while(getButtonPress(buttonAny)) {} //release
		//or
		while(!getButtonPress(buttonEnter)) {} //press
		while(getButtonPress(buttonEnter)) {} //release

		time1 [T1] = 0;//Start
		time_elapsed = time1[T1];
		//Stop and record in var

		colour = (int) SensorValue[S3]; //Record colour sensed

		while(getButtonPress(buttonAny)) //Wait for enter button release
		{}

		time_elapsed = time1[T1]; // stop timer and record time elapsed
		drive_from_colour (time_elapsed, colour); //call written function
	}
	//Terminate program
}

/*
Assumption: Assuming the user places the paper underneath the colour
sensor BEFORE they press any button to track the amount of time
(doing it after results in error so we are assuming they know not
to do that).

Issues:

1) If non-red or blue papers are used the functionality of the robot
will be hampered.

2) If there were any walls or objects, then the robot could continue
to move and try to draw, but the opposing force would prevent that.
This would mess up the drawing.
*/
