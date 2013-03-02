#pragma config(Hubs,	S1, HTMotor,	HTServo,	none,			none)
#pragma config(Sensor, S2,		 IRSeekerS2,		 sensorHiTechnicIRSeeker1200)
#pragma config(Motor,	 mtr_S1_C1_1,			motorD,				 tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,	 mtr_S1_C1_2,			motorE,				 tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,	 srvo_S1_C2_1,		servo1,								tServoNone)
#pragma config(Servo,	 srvo_S1_C2_2,		servo2,								tServoNone)
#pragma config(Servo,	 srvo_S1_C2_3,		servo3,								tServoNone)
#pragma config(Servo,	 srvo_S1_C2_4,		servo4,								tServoNone)
#pragma config(Servo,	 srvo_S1_C2_5,		servo5,								tServoNone)
#pragma config(Servo,	 srvo_S1_C2_6,		servo6,								tServoNone)
#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)

#include "JoystickDriver.c"

void initializeRobot()
{
	return;
}

task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	static int lightMotorPower = 50;

	while(true)                            // Infinite loop:
	{
		getJoystickSettings(joystick);

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
				motor[motorD] = 50;
				motor[motorE] = 50;
			}
			motor[motorD] = 0;
			motor[motorE] = 0;
		}

		if(joy1Btn(4))     // If button 3 is pressed, use the light sensor to auto align
		{
			PlaySound(soundBeepBeep);
			while(joy1Btn(4)){
				getJoystickSettings(joystick);
				if((SensorValue[lightSensor] < 30) && (SensorValue[lightSensor] > 15))  // If the Light Sensor does not see the white line, turn until it does
				{
					while(SensorValue[lightSensor] < 30){
						motor[motorD] = -lightMotorPower;
						motor[motorE] = lightMotorPower;
					}
					motor[motorD] = 0;
					motor[motorE] = 0;
				}
			}
		}

			if(joystick.joy1_x2 > 5)   // If the right analog stick's Y-axis readings is above the threshold do a point turn right
			{
				while(joystick.joy1_x2 > 5){
					getJoystickSettings(joystick);
					motor[motorD] = -50;
					motor[motorE] = 50;
				}
				motor[motorD] = 0;
				motor[motorE] = 0;
			}
			if(joystick.joy1_x2 < -5)
			{
				while(joystick.joy1_x2 < -5){
					getJoystickSettings(joystick);
					motor[motorD] = 50;
					motor[motorE] = -50;
				}
				motor[motorD] = 0;
				motor[motorE] = 0;
			}
		}
	}
