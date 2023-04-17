/*
Coders: Shaan Banday (20993610) and James Yu(21013316)
Group: 39
Class: ME 101
*/

void configureAllSensors(); //configures all sensors to standard configuration
void drive(int motor_power); //powers both drive motors with the same power
void driveBoth (int motor_power_A, int motor_power_D); //powers both motors
void waitButton(TEV3Buttons button_name);  //push and release of button

/*
1. Reset motor encoders to 0
2. Removed resetGyro() function by using a variable to track the current angle
3. Decreased speed of the motors to cause less error when abbruptly stopping
4. Added a wait after the turn to fully allow all processes to occur
*/

void rotateRobot(int angle) //Rotates robot in place to given angle then stops.
{ //Positive angles are CW
	nMotorEncoder[motorA] = 0;//reset the value of encoder A to zero
	nMotorEncoder[motorD] = 0;//reset the value of encoder D to zero

	float current_angle = getGyroDegrees(S4); //Get current angle from gyrosensor

	//Decisions
	if (angle > 0) //If a positive angle
	{
		driveBoth(-10, 10); //Move clockwise
	}

	else //Otherwise, if a negative angle
	{
		driveBoth(10, -10); //Move counter-clockwise
	}

	//Loops
	while (abs(getGyroDegrees(S4)- current_angle) < abs(angle))
	{}  //Keep going until angle is reached

	drive(0); //Stop motors

	wait1Msec(2500); //Pause thread for 2.5 seconds
}

/*
1. Removed resetMotorEncoder()
2. Decreased the speed of the motors to reduce shaking
3. Added acceleration and deceleration to make transition more smooth
4. Added a wait after the drive to fully allow all processes to occur
*/

//Drives robot straight for given distance based on motor encoders and
//nominal wheel diameter. Positive distance is forward
void driveDistance (int distance)
{
	//Record current encoder value
	float current_encoder_value = nMotorEncoder[motorA];
	const float CM_TO_DEG = 180/(2.75*PI); //conversion

	//Decisions
	if (distance > 0) //If the distance is positive
	{
		drive(10); //Drive forward at slow speed
		//Drive for 1/4 of the way
		while (abs(nMotorEncoder[motorA] - current_encoder_value) < (abs(distance*CM_TO_DEG))/4)
		{}

		drive(20); //Drive forward at faster speed
		//Drive for the next 1/2 of the way (3/4 of the whole length)
		while (abs(nMotorEncoder[motorA] - current_encoder_value) < 3*(abs(distance*CM_TO_DEG))/4)
		{}

		drive(10); //Drive forward at slow speed
		//Drive for the last 1/4 of the way
		while (abs(nMotorEncoder[motorA] - current_encoder_value) < (abs(distance*CM_TO_DEG)))
		{}
	}

	else //Otherwise, if the distance is negative
	{
		drive(-10);//Drive backwards at slow speed
		//Drive for 1/4 of the way
		while (abs(nMotorEncoder[motorA] - current_encoder_value) < (abs(distance*CM_TO_DEG))/4)
		{}

		drive(-20); //Drive backwards at faster speed
		//Drive for the next 1/2 of the way (3/4 of the whole length)
		while (abs(nMotorEncoder[motorA] - current_encoder_value) < 3*(abs(distance*CM_TO_DEG))/4)
		{}

		drive(-10);//Drive backwards at slow speed
		//Drive for the last 1/4 of the way
		while (abs(nMotorEncoder[motorA] - current_encoder_value) < (abs(distance*CM_TO_DEG)))
		{}
	}

	drive(0); //Stop both motors

	wait1Msec(2500); //Pause thread for 2.5 seconds
}

/* ------------------------------------------------------------ */
/* --- Do Not Modify the code below.                        --- */
/* ------------------------------------------------------------ */
task main()
{
	const int NUM_SIDES = 4;
	const int ANGLE_CORNER = 90;
	const int SIDE_LENGTH = 50;

	configureAllSensors();
	waitButton(buttonEnter);

	for(int sides = 0; sides < NUM_SIDES; sides++)
	{
		driveDistance(SIDE_LENGTH);
		rotateRobot(ANGLE_CORNER);
	}
	wait1Msec(1000);
	for(int sides = 0; sides < NUM_SIDES; sides++)
	{
		rotateRobot(-ANGLE_CORNER);
		driveDistance(-SIDE_LENGTH);
	}
}
/* DNM: Do Not Modify the code below. */
void configureAllSensors()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}
/* DNM: Do Not Modify the code below. */
//powers both drive motors with the same power
void drive(int motor_power)
{
	motor[motorA] = motor[motorD] = motor_power;
}
/* DNM: Do Not Modify the code below. */
//powers both motors independently
void driveBoth(int motor_power_A, int motor_power_D)
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
}
/* DNM: Do Not Modify the code below. */
void waitButton(TEV3Buttons button_name)
{
	while(!getButtonPress(button_name))
	{}
	while(getButtonPress(button_name))
	{}
}
/* ------------------------------------------------------------ */
