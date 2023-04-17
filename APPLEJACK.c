/*
Coders: Shaan Banday (20993610) and Saleem Mohammed Ali (21033947)
Group: 57
Class: ME 101
*/

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

task main()
{
	//Declare all variables
 	float ultrasonic_start = 0, ultrasonic_end = 0; //Varibles for measuring the paper using ultrasonic sensors
 	float motor_start = 0, motor_end = 0; //Varibles for measuring the paper using motor encoders
 	float motor_length = 0, ultrasonic_length = 0; //Varibles for recording the distance

	configureAllSensors(); //Call external function to callibrate all the sensors
	//Function is void so no return type (command)

	//Display Group Number and Initials
	displayString(3, "Group 57, SB, SMA"); //Display the following string on line 3 of the EV3 brick

	while(!getButtonPress(buttonAny or buttonEnter)) //press
	{}
	while(getButtonPress(buttonAny or buttonEnter)) //release
	{}

	//Initialse motors
	nMotorEncoder[motorA] = 0; //Reset the encoder to 0

	//Drive forward
	motor[motorA] = 40; //Drive motor A at 40% power
	motor[motorD] = 40; //Drive motor D at 40% power

	//While moving forward
	while(SensorValue[S3] != 5) //Keep running while loop until red is seen
  {} //As soon as color sensor sees red (5) exit while loop

  //Store how far the ultrasonic sensor is from the wall when the color sensor sees red
  ultrasonic_start = SensorValue[S2]; //record this distance from the wall as the starting point

  //While STILL moving forward
 	while(SensorValue[S3] == 5) //Keep running while loop so long as red is seen
 	{} //As soon as color sensor sees anything but red (5) exit while loop

 	//Store how far the ultrasonic sensor is from the wall when the color sensor no longer sees red
  ultrasonic_end = SensorValue[S2]; //record this distance from the wall as the end point

	//While STILL moving forward
 	while(SensorValue[S1] == 0) //Keep running while loop so long as touch sensor is not pressed
 	{} //As soon as touch sensor is pressed (!= 0) exit while loop.

 	//Stop and Wait
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
	wait1Msec(500); //Pause thread for 500 ms (0.5 s)

	//Drive Backwards to original location using motors encoders
	motor[motorA]= -40; //Drive motor A at -40% power (i.e., 40% backwards)
	motor[motorD] = -40; //Drive motor D at -40% power (i.e., 40% backwards)

	//While moving backwards
	while(SensorValue[S3] != 5) //Keep running while loop until red is seen
  {} //As soon as color sensor sees red (5) exit while loop

  //Store the value of the motor encoders (converted to distance when the color sensor sees red
  motor_start = nMotorEncoder[motorA] * PI * 2.75 / 180; //record this distance as the starting point

  //While STILL moving backwards
 	while(SensorValue[S3] == 5) //Keep running while loop so long as red is seen
 	{} //As soon as color sensor sees anything but red (5) exit while loop

 	//Store the value of the motor encoders (converted to distance when the color sensor no longer sees red
  motor_end = nMotorEncoder[motorA] * PI * 2.75 / 180; //record this distance as the end point

	//While STILL moving forward
 	while(nMotorEncoder[motorA] > 0) //Keep running, so long as the motor encoders are not at 0
 	{} //As soon as they hit 0, exit the while loop

 	//Calculate paper lengths
 	ultrasonic_length = abs(ultrasonic_start - ultrasonic_end); //Take absolute value of difference
 	motor_length = abs(motor_start - motor_end); //Take absolute value of difference

 	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)

 	//Display paper's length from motor encoder and ultrasonic sensor
	displayString(5, "Ultrasonic length: %f", ultrasonic_length); //Display on line 5 the ultrasonics length
 	displayString(7, "Motor Encoder length: %f", motor_length); //Display on line 5 the motor encoders length

 	//While stopped
	while(!getButtonPress(buttonAny)) //Wait for the enter button to be pressed
	{}
	while(getButtonPress(buttonAny)) //Wait for the enter button to be released
	{}

	//Rotate 360 degrees clockwise
	motor[motorA] = -30; // Drive motor A at -30% power (i.e., 30% backwards)
	motor[motorD] = 30; //Drive motor B at 30% power (i.e., 30% forwards)

	//Reset gyro sensor
  resetGyro(S4);

	//While robot is rotating
  while(getGyroDegrees(S4) < 360) //Keep running while loop so long as gyro sensor is less thna 360
	{} //As soon as gyro detects 360 (full rotation), exit loop

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)
} //Terminate program
