/*
Coders: Shaan Banday (20993610) and Ryan Yau (21025670)
Group: 52
Class: ME 101
*/

task main() //Main task
{
	//Display Group Number and Initials
	displayString(5,"Group 52, SB, RY"); //Display on line 5

	//Declare gyro sensors
	SensorType[S2] = sensorEV3_Ultrasonic; //Set ultrasonic to port 2
	wait1Msec(65); //Pause thread for 65 ms to let calibration occur


	SensorType[S4] = sensorEV3_Gyro; //Set gyro to port 4
	SensorMode[S4] = modeEV3Gyro_Calibration; //Callibrate gyro sensor
	wait1Msec(100); //Pause thread for 100 ms to let calibration occur
	SensorMode[S4] = modeEV3Gyro_RateAndAngle; //Callibrate again

	//Initialse motors
  nMotorEncoder[motorA] = 0; //Reset the encoder to 0

	//Drive forward
	motor[motorA]= 50; //Drive motor A at 50% power
	motor[motorD] = 50; //Drive motor B at 50% power
	wait1Msec(2000); //Pause thread for 2 seconds, which will continue this operation

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)


	//Drive Backwards to original location using motors encoders
	motor[motorA]= -50; //Drive motor A at -50% power (i.e., 50% backwards)
	motor[motorD] = -50; //Drive motor D at -50% power (i.e., 50% backwards)

	//Keep running so long as the encoder is greater than 0
	while(nMotorEncoder[motorA] > 0)
	{}

	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)


	//Turn 90 degree clockwise
	resetGyro(S4); //Reset the gyroscope
	motor[motorA] = -25; // Drive motor A at -25% power (i.e., -25% backwards)
	motor[motorD] = 25; //Drive motor B at 25% power (i.e., 25% forwards)
	//When this happens, robot will start to rotate in place as motors are operating in opposite directions

	//Keep running so long as the angle of the gyroscope is less than 90 degrees
	while(getGyroDegrees(S4) < 90)
	{}


	//Stop
	motor[motorA] = 0; //Drive motor A at 0% power (i.e., stop)
	motor[motorD] = 0; //Drive motor D at 0% power (i.e., stop)


	//Wait
	wait1Msec(3000); //Pause thread for 3 seconds, then terminate program
}
