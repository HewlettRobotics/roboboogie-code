#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSeekerS2,     sensorI2CCustom)
#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorA,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorB,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//MotorB = Ringholder motor
//MotorD = Left Motor
//motorA = lift motor
//motorE = Right Motor
#include "JoystickDriver.c"

void initializeRobot()
{
	return;
}

task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	if(joy1Btn(2))     // If Button 8 is pressed on joy1: lift goes down
	{
		while(joy1Btn(2)){
			getJoystickSettings(joystick);
			motor[motorA] = -70;
		}
		motor[motorA] = 0;
	}
	if(joy1Btn(3))     // If Button 8 is pressed on joy1: lift goes up
	{
		while(joy1Btn(3)){
			getJoystickSettings(joystick);
			motor[motorA] = 70;
		}
		motor[motorA] = 0;
	}

	if(joy1Btn(5))     // If Button 8 is pressed on joy1: go backwards
		{
			while(joy1Btn(5)){
				getJoystickSettings(joystick);
				motor[motorD] = -50;
				motor[motorE] = -50;
			}
			motor[motorD] = 0;
			motor[motorE] = 0;
		}
		if(joy1Btn(6))     // If Button 8 is pressed on joy1: go forwards
		{
			while(joy1Btn(6)){
				getJoystickSettings(joystick);
				motor[motorB] = 50;
			}
			motor[motorB] = 0;
		}

		if(joy1_x1 > 50){ //Point turn
			while(joy1_x1 > 50){
				getJoystickSettings(joystick);
				motor[motorD] = 50;
				motor[motorE] = -50;
			}
		}

		if(joy1_x2 > 50){ // Point turn
			while(joy1_x2 > 50){
				getJoystickSettings(joystick);
				motor[motorD] = -50;
				motor[motorE] = 50;
			}
		}

		if(joy2Btn(5)){
			while(joy2Btn(6)){
			getJoystickSettings(joystick);
			motor[motorB] = -50;
		}
	}

/*	if(joy1Btn(5)){
			while(joy2Btn(5)){
			getJoystickSettings(joystick);
			motor[motorB] = 50;
		}
	}*/
}
