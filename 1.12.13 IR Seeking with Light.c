#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSeekerS2,     sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	static int waitTime = 25;
	static int forwardDist = 2800;
	static int firstPostDist = 3300;
	static int secondPostDist = 2450;
	static int thirdPostDist = 2450;
	static int turnDist = 1850;
	static int firstPostTurnCompensation = 150;
	static int lightMotorPower = 20; //motor power level used during light sensor alignment
	static float firstInterval = .65; //this determines the fraction of the forward distance the robot moves until it aligns itself
	static float secondInterval = .35;

	//reset encoders
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;


	//move forward
	nMotorEncoderTarget[motorD] = firstPostDist;
	nMotorEncoderTarget[motorE] = firstPostDist;

	// set speed to 75%
	motor[motorD] = 75;
	motor[motorE] = 75;

	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle) //while the encoder wheel turns one revolution

	{
		// This condition waits for motors D + E to come to an idle position. Both motors stop
		// and then jumps out of the loop
	}
	//pause
	wait1Msec(waitTime);

	//get IR sensor value
	if(SensorValue[IRSeekerS2] == 5)
	{
		{
			//turn left towards 1st post
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = -(turnDist + firstPostTurnCompensation) ;
			nMotorEncoderTarget[motorE] = (turnDist + firstPostTurnCompensation);

			motor[motorD] = -40;
			motor[motorE] = 40;


			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			// go 7/10 distance to peg to get on the white strip

			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = firstInterval*(forwardDist);
			nMotorEncoderTarget[motorE] = firstInterval*(forwardDist);

			motor[motorD] = 75;
			motor[motorE] = 75;
			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			wait10Msec(10);
			//Use light sensor to unser we are aligned with the post
			if((SensorValue[lightSensor] < 30) && (SensorValue[lightSensor] > 15))  // If the Light Sensor does not see the white line, turn until it does
			{
				while(SensorValue[lightSensor] < 30){
					motor[motorD] = -lightMotorPower;   //turn until the robot is aligned with the white line
					motor[motorE] = lightMotorPower;
				}
			}

			// go 3/10 DISTANCE to peg

			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = secondInterval*(forwardDist);
			nMotorEncoderTarget[motorE] = secondInterval*(forwardDist);

			motor[motorD] = 75;
			motor[motorE] = 75;
			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			//pause
			wait1Msec(waitTime);


			//back out First Post
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = -forwardDist;
			nMotorEncoderTarget[motorE] = -forwardDist;
			motor[motorD] = -50;
			motor[motorE] = -50;

			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			//turn in preparation for going in reverse
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = turnDist;
			nMotorEncoderTarget[motorE] = -turnDist;
			motor[motorD] = 50;
			motor[motorE] = -50;
			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			//reverse into starting position from First Post
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = -firstPostDist;
			nMotorEncoderTarget[motorE] = -firstPostDist;
			motor[motorD] = -70;
			motor[motorE] = -70;
			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}


		}


		{
			StopAllTasks();
		}
	}
	if(SensorValue[IRSeekerS2] != 5)
	{

		//keep going
		nMotorEncoder[motorD] = 0;
		nMotorEncoder[motorE] = 0;
		nMotorEncoderTarget[motorD] = secondPostDist;
		nMotorEncoderTarget[motorE] = secondPostDist;

		motor[motorD] = 50;
		motor[motorE] = 50;
	}

	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle) //while the encoder wheel turns one revolution


	//turn both motors off
	wait1Msec(waitTime);

	//Check IR again etc... etc...
	if(SensorValue[IRSeekerS2] == 5)
	{
		{
			//turn left
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = -turnDist;
			nMotorEncoderTarget[motorE] = turnDist;

			motor[motorD] = -40;
			motor[motorE] = 40;

			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}


			// go fraction of distance to peg

			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = firstInterval*(forwardDist + 200);
			nMotorEncoderTarget[motorE] = firstInterval*(forwardDist + 200);

			motor[motorD] = 50;
			motor[motorE] = 50;


			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			wait10Msec(10);
			//Use light sensor to ensure we are aligned with the post
			if((SensorValue[lightSensor] < 30) && (SensorValue[lightSensor] > 15))  // If the Light Sensor does not see the white line, turn until it does
			{
				while(SensorValue[lightSensor] < 30){
					motor[motorD] = -lightMotorPower;
					motor[motorE] = lightMotorPower;
				}
			}

			// go fraction of distance to peg

			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = secondInterval*(forwardDist + 200);
			nMotorEncoderTarget[motorE] = secondInterval*(forwardDist + 200);

			motor[motorD] = 50;
			motor[motorE] = 50;


			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}


			//pause
			wait1Msec(waitTime);


			//back out Second Post
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = -forwardDist;
			nMotorEncoderTarget[motorE] = -forwardDist;
			motor[motorD] = -50;
			motor[motorE] = -50;
			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			//turn in preparation for going in reverse
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = turnDist;
			nMotorEncoderTarget[motorE] = -turnDist;
			motor[motorD] = 50;
			motor[motorE] = -50;
			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

			//reverse into starting position from Second Post
			nMotorEncoder[motorD] = 0;
			nMotorEncoder[motorE] = 0;
			nMotorEncoderTarget[motorD] = -(firstPostDist + secondPostDist);
			nMotorEncoderTarget[motorE] = -(firstPostDist + secondPostDist);
			motor[motorD] = -70;
			motor[motorE] = -70;


			while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){} //while the encoder wheel turns one revolution
		}
		{
			StopAllTasks();
		}
	}
	if(SensorValue[IRSeekerS2] != 5)
	{
		//keep going
		nMotorEncoder[motorD] = 0;
		nMotorEncoder[motorE] = 0;
		nMotorEncoderTarget[motorD] = thirdPostDist;
		nMotorEncoderTarget[motorE] = thirdPostDist;

		motor[motorD] = 50;
		motor[motorE] = 50;
	}

	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle) //while the encoder wheel turns one revolution




	//turn left because you dont need to check for the third pole for the ir beacon
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
	nMotorEncoderTarget[motorD] = -(turnDist-150);
	nMotorEncoderTarget[motorE] = (turnDist-150);

	motor[motorD] = -40;
	motor[motorE] = 40;


	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){} //while the encoder wheel turns one revolution

	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
	nMotorEncoderTarget[motorD] = firstInterval*(forwardDist);
	nMotorEncoderTarget[motorE] = firstInterval*(forwardDist);

	motor[motorD] = 75;
	motor[motorE] = 75;
	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

	wait10Msec(10);
	//Use light sensor to unser we are aligned with the post
	if((SensorValue[lightSensor] < 30) && (SensorValue[lightSensor] > 15))  // If the Light Sensor does not see the white line, turn until it does
	{
		while(SensorValue[lightSensor] < 30){
			motor[motorD] = -lightMotorPower;                  // Motor D is run at a 60 power level.
			motor[motorE] = lightMotorPower;                  // Motor E is run at a 20 power level.
		}
	}

	// go 3/10 DISTANCE to peg

	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
	nMotorEncoderTarget[motorD] = secondInterval*(forwardDist);
	nMotorEncoderTarget[motorE] = secondInterval*(forwardDist);

	motor[motorD] = 75;
	motor[motorE] = 75;
	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

	//pause
	wait1Msec(waitTime);


	//back out Third Post
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
	nMotorEncoderTarget[motorD] = -forwardDist;
	nMotorEncoderTarget[motorE] = -forwardDist;
	motor[motorD] = -50;
	motor[motorE] = -50;

	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

	//turn in preparation for going in reverse
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
	nMotorEncoderTarget[motorD] = turnDist;
	nMotorEncoderTarget[motorE] = -turnDist;
	motor[motorD] = 50;
	motor[motorE] = -50;
	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){}

	//reverse into starting position from Third Post
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
	nMotorEncoderTarget[motorD] = -(firstPostDist + secondPostDist + thirdPostDist);
	nMotorEncoderTarget[motorE] = -(firstPostDist + secondPostDist + thirdPostDist);
	motor[motorD] = -70;
	motor[motorE] = -70;


	while (nMotorRunState[motorD] != runStateIdle || nMotorRunState[motorE] != runStateIdle){} //while the encoder wheel turns one revolution

	{
		StopAllTasks();
	}
}
