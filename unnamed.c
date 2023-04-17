/*
Coders: Shaan Banday (20993610) and Sabrina Mogus (GET HER STUDENT NUMBER HERE)
Group: 34
Class: ME 101
*/

//Functions from Lecture 12

void configureAllSensors() //Void function which configures all sensors but does not return anything
{
	//Set sensors for robot in default configuration
	SensorType[S1] = sensorEV3_Touch; //Set port 1 to touch sensor
	SensorType[S2] = sensorEV3_Ultrasonic; //Set port 2 to ultrasonic sensor
	SensorType[S3] = sensorEV3_Color; //Set port 3 to color sensor
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur

	SensorMode[S3] = modeEV3Color_Color; //Set color sensor to color mode (as opposed to ambient light mode
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur

	SensorType[S4] = sensorEV3_Gyro; //Set port 4 to gyro sensor
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur

	SensorMode[S4] = modeEV3Gyro_Calibration; //Callibrate the gyro sensor and reset it
	wait1Msec(100); //Pause thread for 100 ms to let calibration occur

	SensorMode[S4] = modeEV3Gyro_RateAndAngle; //Set gyro sensor to measure angle mode
	wait1Msec(50); //Pause thread for 50 ms to let calibration occur
} //end of function, return to main task


void printInfo(int group_number, int line_number) //Void function prints group number on a certain line
{
	displayString (line_number, "Group %f, SB SM", group_number); //display on EV3 Brick
}

void samePower(int time_in_ms, int motor_power) //Void function sets motors to the same power
{
  //Drive forward
	motor[motorA] = motor_power; //Drive motor A at set power %
	motor[motorD] = motor_power; //Drive motor D at same power % as A

	//Duration
	wait1Msec(time_in_ms); //Pause thread for set time in ms to keep moving forward

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
}


void diffPower(int time_in_ms, int powerA, int powerD) //Void function sets motors to different power
{
	//Rotate
	motor[motorA] = powerA; //Drive motor A at power A%
  motor[motorD] = powerD; //Drive motor D at power D%

  //Duration
	wait1Msec(time_in_ms); //Pause thread for set time in ms to keep moving forward

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
}

void rotateRobot (int target_angle, int motor_power) //Rotate the robot to a target angle (from PDF provided)
{
  resetGyro(S4); //Reset gyro sensor in sensor spot 4

  //Decisions
  if (target_angle > 0) //If the target angle is greater than 0
  {
		//Turn clockwise
		motor[motorD] = motor_power;
		motor[motorA] = -motor_power;

		while (SensorValue[S4] < target_angle) //Keep turning until target angle is reached
		{
		}

		//Stop
		motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
		motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
	}

	else if (target_angle < 0)  //If the target angle is less than 0
	{
		//Turn counter-clockwise
		motor[motorD] = -motor_power;
		motor[motorA] = motor_power;

		while (SensorValue[S4] > target_angle) //Keep turning until target angle is reached
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
  int angle = 0, motor_power = 30, motor_powerA = -45, motor_powerD = -35;

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
    diffPower(time_pressed, motor_powerA, motor_powerD); //Drive backwards in curve
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

		while(!getButtonPress(buttonAny)) //Wait for the enter button to be pressed
		{}

		time1 [T1] = 0; //Start timer
		colour = (int) SensorValue[S3]; //Record colour sensed by colour sensor

		while(getButtonPress(buttonAny)) //Wait for the enter button to be released
		{}

		time_elapsed = time1[T1]; // stop timer and record time elapsed
		drive_from_colour (time_elapsed, colour); //call written function to rotate robot
	}
	//Terminate program
}
