/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef SQUEAKY_H // include guard
#define SQUEAKY_H

int prevState = 0;
int curState = 0;

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
int left = 0;
int right = 0;


char posR = NULL;
char prevPosR = NULL;
char posL = NULL;
char prevPosL = NULL;

void squeaky_drive(Controller *c, float x, float y, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {



	//bad ir code
int lift_value;

	if (c->btn6.up) {
		lift_value = -1;
	}
	else if (c->btn6.down) {
		lift_value = 1;
	} else {
		lift_value = 0;
	}






/*


	if ( (lift_value != 0) || (abs(y) > 15) ) {     // turn + lift

  	curState = 1;

	} else if (lift_value != 0) {    // drive + lift

  	curState = 2;

	} else {

		//default?
		curState = 3;


	}

*/




	switch (curState)
  {
  case 1: //drive + lift

	curState = 1;
  if (abs(vexRT[Ch1]) > 15) {
  		curState = 3;
  }




  	if (curState != prevState) {
  		for (int i=0; i<3; i++)
      {
        sendChar(UART1, 0x66);
      }
   }




	// Right claw forward

			if (vexRT[Btn6D] == 1) { //button held
				curA = true;

				if (curA && !prevA) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FR_SWITCH] == 1) { //not at limit
						motor[right_claw_port] = -100;
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'F';
				}

			} else { //button not held
				curA = false;
			}


			if (SensorValue[CLAW_FR_SWITCH] == 0 && posR == 'G') { //falling edge RUNS ONCE

							posR = 'M';
							prevPosR = 'F';
							clearTimer(T2);

			}



			if (!curA && prevA) { //falling edge RUNS ONCE
					if (posR == 'F') {
							posR = 'M';
							prevPosR = 'F';
							clearTimer(T2);
					}
			}

			if (posR == 'M' && time1[T2] < 300 && prevPosR == 'F') {
					motor[right_claw_port] = 100;
			} else if (posR == 'M' && time1[T2] >= 300 && prevPosR == 'F') {
					motor[right_claw_port] = 0;
					posR = NULL;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (vexRT[Btn6U] == 1) { //button held
				curB = true;

				if (curB && !prevB) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BR_SWITCH] == 1) { //not at limit
						motor[right_claw_port] = 100;
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'C';
				}

			} else { //button not held
				curB = false;
			}

			if (SensorValue[CLAW_BR_SWITCH] == 0 && posR == 'G') { //falling edge RUNS ONCE

							posR = 'M';
							prevPosR = 'C';
							clearTimer(T3);

			}



			if (!curB && prevB) { //falling edge RUNS ONCE
					if (posR == 'C') {
							posR = 'M';
							prevPosR = 'C';
							clearTimer(T3);
					}
			}

			if (posR == 'M' && time1[T3] < 400 && prevPosR == 'C') {
					motor[right_claw_port] = -100;
			} else if (posR == 'M' && time1[T3] >= 400 && prevPosR == 'C') {
					motor[right_claw_port] = 0;
					posR = NULL;
			}



			prevA = curA;
			prevB = curB;




			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
						motor[left_claw_port] = -35;
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'F';
				}

			} else { //button not held
				curC = false;
			}


			if (SensorValue[CLAW_FL_SWITCH] == 0 && posL == 'G') { //falling edge RUNS ONCE

							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);

			}



			if (!curC && prevC) { //falling edge RUNS ONCE
					if (posL == 'F') {
							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);
					}
			}

			if (posL == 'M' && time1[T4] < 1300 && prevPosL == 'F') {
					motor[left_claw_port] = 35;
			} else if (posL == 'M' && time1[T4] >= 1300 && prevPosL == 'F') {
					motor[left_claw_port] = 0;
					posL = NULL;
			}






			// left claw backward ////////////////////////////////////////////////////////////
			if (down == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						motor[left_claw_port] = 35;
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'C';
				}

			} else { //button not held
				curD = false;
			}

			if (SensorValue[CLAW_BL_SWITCH] == 0 && posL == 'G') { //falling edge RUNS ONCE

							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);

			}



			if (!curD && prevD) { //falling edge RUNS ONCE
					if (posL == 'C') {
							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);
					}
			}

			if (posL == 'M' && time1[T1] < 1300 && prevPosL == 'C') {
					motor[left_claw_port] = -35;
			} else if (posL == 'M' && time1[T1] >= 1300 && prevPosL == 'C') {
					motor[left_claw_port] = 0;
					posL = NULL;
			}



			prevC = curC;
			prevD = curD;







    break;

   case 2: //turn + lift

	curState = 2;

   if (abs(vexRT[Ch3]) > 15) {
  		curState = 1;
  }



   	if (curState != prevState) {
  		for (int i=0; i<3; i++)
      {
        sendChar(UART1, 0x33);
      }
 		}


		 // Right claw forward

			if (vexRT[Btn6D] == 1) { //button held
				curA = true;

				if (curA && !prevA) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FR_SWITCH] == 1) { //not at limit
						motor[right_claw_port] = -100;
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'F';
				}

			} else { //button not held
				curA = false;
			}


			if (SensorValue[CLAW_FR_SWITCH] == 0 && posR == 'G') { //falling edge RUNS ONCE

							posR = 'M';
							prevPosR = 'F';
							clearTimer(T2);

			}



			if (!curA && prevA) { //falling edge RUNS ONCE
					if (posR == 'F') {
							posR = 'M';
							prevPosR = 'F';
							clearTimer(T2);
					}
			}

			if (posR == 'M' && time1[T2] < 300 && prevPosR == 'F') {
					motor[right_claw_port] = 100;
			} else if (posR == 'M' && time1[T2] >= 300 && prevPosR == 'F') {
					motor[right_claw_port] = 0;
					posR = NULL;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (vexRT[Btn6U] == 1) { //button held
				curB = true;

				if (curB && !prevB) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BR_SWITCH] == 1) { //not at limit
						motor[right_claw_port] = 100;
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'C';
				}

			} else { //button not held
				curB = false;
			}

			if (SensorValue[CLAW_BR_SWITCH] == 0 && posR == 'G') { //falling edge RUNS ONCE

							posR = 'M';
							prevPosR = 'C';
							clearTimer(T3);

			}



			if (!curB && prevB) { //falling edge RUNS ONCE
					if (posR == 'C') {
							posR = 'M';
							prevPosR = 'C';
							clearTimer(T3);
					}
			}

			if (posR == 'M' && time1[T3] < 400 && prevPosR == 'C') {
					motor[right_claw_port] = -100;
			} else if (posR == 'M' && time1[T3] >= 400 && prevPosR == 'C') {
					motor[right_claw_port] = 0;
					posR = NULL;
			}



			prevA = curA;
			prevB = curB;
////////////////////////////////////////////////////////////////////////////////////////////turn left claw


			if (vexRT[Ch1] > 15) {
				right = 1;
			} else {
				right = 0;
			}

			if (vexRT[Ch1] < -15) {
				left = 1;
			} else {
				left = 0;
			}

			if (right == 1) { //button held
				curC = true;

				if (curC && !prevC) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FL_SWITCH] == 1) { //not at limit
						motor[left_claw_port] = -35;
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'F';
				}

			} else { //button not held
				curC = false;
			}


			if (SensorValue[CLAW_FL_SWITCH] == 0 && posL == 'G') { //falling edge RUNS ONCE

							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);

			}



			if (!curC && prevC) { //falling edge RUNS ONCE
					if (posL == 'F') {
							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);
					}
			}

			if (posL == 'M' && time1[T4] < 1300 && prevPosL == 'F') {
					motor[left_claw_port] = 35;
			} else if (posL == 'M' && time1[T4] >= 1300 && prevPosL == 'F') {
					motor[left_claw_port] = 0;
					posL = NULL;
			}






			// left claw backward ////////////////////////////////////////////////////////////
			if (left == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						motor[left_claw_port] = 35;
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'C';
				}

			} else { //button not held
				curD = false;
			}

			if (SensorValue[CLAW_BL_SWITCH] == 0 && posL == 'G') { //falling edge RUNS ONCE

							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);

			}



			if (!curD && prevD) { //falling edge RUNS ONCE
					if (posL == 'C') {
							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);
					}
			}

			if (posL == 'M' && time1[T1] < 1300 && prevPosL == 'C') {
					motor[left_claw_port] = -35;
			} else if (posL == 'M' && time1[T1] >= 1300 && prevPosL == 'C') {
					motor[left_claw_port] = 0;
					posL = NULL;
			}



			prevC = curC;
			prevD = curD;





    break;

  default: //drive + turn

	curState = 3;

  if (vexRT[Btn6D] == 1 || vexRT[Btn6U] == 1) {
  		curState = 2;
  }

  if (curState != prevState) {
  	for (int i=0; i<3; i++)
      {
        sendChar(UART1, 0x3C);
      }
   }

     if (vexRT[Ch1] > 15) {
				right = 1;
			} else {
				right = 0;
			}

			if (vexRT[Ch3] < -15) {
				left = 1;
			} else {
				left = 0;
			}

	// Right claw forward


			if (right == 1) { //button held
				curA = true;

				if (curA && !prevA) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FR_SWITCH] == 1) { //not at limit
						motor[right_claw_port] = -100;
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'F';
				}

			} else { //button not held
				curA = false;
			}


			if (SensorValue[CLAW_FR_SWITCH] == 0 && posR == 'G') { //falling edge RUNS ONCE

							posR = 'M';
							prevPosR = 'F';
							clearTimer(T2);

			}



			if (!curA && prevA) { //falling edge RUNS ONCE
					if (posR == 'F') {
							posR = 'M';
							prevPosR = 'F';
							clearTimer(T2);
					}
			}

			if (posR == 'M' && time1[T2] < 300 && prevPosR == 'F') {
					motor[right_claw_port] = 100;
			} else if (posR == 'M' && time1[T2] >= 300 && prevPosR == 'F') {
					motor[right_claw_port] = 0;
					posR = NULL;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (left == 1) { //button held
				curB = true;

				if (curB && !prevB) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BR_SWITCH] == 1) { //not at limit
						motor[right_claw_port] = 100;
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'C';
				}

			} else { //button not held
				curB = false;
			}

			if (SensorValue[CLAW_BR_SWITCH] == 0 && posR == 'G') { //falling edge RUNS ONCE

							posR = 'M';
							prevPosR = 'C';
							clearTimer(T3);

			}



			if (!curB && prevB) { //falling edge RUNS ONCE
					if (posR == 'C') {
							posR = 'M';
							prevPosR = 'C';
							clearTimer(T3);
					}
			}

			if (posR == 'M' && time1[T3] < 400 && prevPosR == 'C') {
					motor[right_claw_port] = -100;
			} else if (posR == 'M' && time1[T3] >= 400 && prevPosR == 'C') {
					motor[right_claw_port] = 0;
					posR = NULL;
			}



			prevA = curA;
			prevB = curB;




			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
						motor[left_claw_port] = -35;
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'F';
				}

			} else { //button not held
				curC = false;
			}


			if (SensorValue[CLAW_FL_SWITCH] == 0 && posL == 'G') { //falling edge RUNS ONCE

							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);

			}



			if (!curC && prevC) { //falling edge RUNS ONCE
					if (posL == 'F') {
							posL = 'M';
							prevPosL = 'F';
							clearTimer(T4);
					}
			}

			if (posL == 'M' && time1[T4] < 1300 && prevPosL == 'F') {
					motor[left_claw_port] = 35;
			} else if (posL == 'M' && time1[T4] >= 1300 && prevPosL == 'F') {
					motor[left_claw_port] = 0;
					posL = NULL;
			}






			// left claw backward ////////////////////////////////////////////////////////////
			if (down == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						motor[left_claw_port] = 35;
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'C';
				}

			} else { //button not held
				curD = false;
			}

			if (SensorValue[CLAW_BL_SWITCH] == 0 && posL == 'G') { //falling edge RUNS ONCE

							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);

			}



			if (!curD && prevD) { //falling edge RUNS ONCE
					if (posL == 'C') {
							posL = 'M';
							prevPosL = 'C';
							clearTimer(T1);
					}
			}

			if (posL == 'M' && time1[T1] < 1300 && prevPosL == 'C') {
					motor[left_claw_port] = -35;
			} else if (posL == 'M' && time1[T1] >= 1300 && prevPosL == 'C') {
					motor[left_claw_port] = 0;
					posL = NULL;
			}



			prevC = curC;
			prevD = curD;


} //end of switch




	prevState = curState;


} //end of function

void joystick_squeaky_control(Controller *c, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {
	// controls base movement with joystick
	//
	// PARAMS
	// 		Controller *c: controller object with its values
	// 		int left_port: port num for left motor
	// 		int right_port: port num for right motor

	Joystick *l = c->Left; // joystick
	Joystick *r = c->Right; // joystick

	// general movement scaling
  int x = r->x_axis * r->x_scale; // x value of movement [-127, 127]
  int y = l->y_axis * l->y_scale; // y value of movement [-127, 127]

  // move robot with joystick values
  squeaky_drive(c, x, y, left_claw_port, right_claw_port, front_left_port, back_left_port, front_right_port, back_right_port); // claw movement
}


#endif // close guard
