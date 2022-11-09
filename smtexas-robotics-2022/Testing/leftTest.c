#pragma config(Sensor, dgtl1,  CLAW_FL_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl2,  CLAW_BL_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl3,  CLAW_FR_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl4,  CLAW_BR_SWITCH, sensorDigitalIn)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define LEFT_CLAW_MOTOR port4


bool curA = false;
bool prevA = false;
bool curB = false;
bool prevB = false;

bool curC = false;
bool prevC = false;
bool curD = false;
bool prevD = false;

int up = 0;
int down = 0;

char posR = NULL;
char prevPosR = NULL;
char posL = NULL;
char prevPosL = NULL;



task main()
{
	clearDebugStream();
	while (true) {

// left claw forward ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (vexRT[Ch3] > 15) {
				up = 1;
			} else {
				up = 0;
			}

			if (vexRT[Ch3] < -15) {
				down = 1;
			} else {
				down = 0;
			}

			if (up == 1) { //button held
				curC = true;

				if (curC && !prevC) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FL_SWITCH] == 1) { //not at limit
						motor[LEFT_CLAW_MOTOR] = -35;
				} else {
						motor[LEFT_CLAW_MOTOR] = 0;
						posL = 'F';
				}

			} else { //button not held
				curC = false;
			}



			if (!curC && prevC) { //falling edge RUNS ONCE
					if (posL == 'F') {
							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);
					}
			}

			if (posL == 'M' && time1[T4] < 1300) {
					motor[LEFT_CLAW_MOTOR] = 35;
			} else if (posL == 'M' && time1[T4] >= 1300 && prevPosL == 'F') {
					motor[LEFT_CLAW_MOTOR] = 0;
					posL = NULL;
			}


/*

			// left claw backward ////////////////////////////////////////////////////////////
			if (down == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						motor[LEFT_CLAW_MOTOR] = 35;
				} else {
						motor[LEFT_CLAW_MOTOR] = 0;
						posL = 'C';
				}

			} else { //button not held
				curD = false;
			}



			if (!curD && prevD) { //falling edge RUNS ONCE
					if (posL == 'C') {
							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);
					}
			}

			if (posL == 'M' && time1[T1] < 1300) {
					motor[LEFT_CLAW_MOTOR] = -35;
			} else if (posL == 'M' && time1[T1] >= 1300 && prevPosL == 'C') {
					motor[LEFT_CLAW_MOTOR] = 0;
					posL = NULL;
			}



			prevC = curC;
			prevD = curD;

*/

	}



}
