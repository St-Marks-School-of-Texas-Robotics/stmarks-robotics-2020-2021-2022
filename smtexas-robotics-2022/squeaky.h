/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef SQUEAKY_H // include guard
#define SQUEAKY_H

int curState = 0;
int prevState = 0;

bool curSlow = false;
bool prevSlow = true;

bool curFast = false;
bool prevFast = false;

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
bool slowR = false;

char posL = NULL;
char prevPosL = NULL;
bool slowL = false;

int irNum = 7;

void squeaky_drive(Controller *c, float x, float y, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {


	if (c->btn5.up) {
		curSlow = true;

		if (curSlow && !prevSlow) { //rising edge
			for (int i = 0; i < irNum; i++) {
				sendChar(UART1, 0x99); //drive to LOW
				sendChar(UART1, 0x69); //rotation to LOW

				//sendChar(UART1, 0xC3); //drive to High
			}

		}

	} else { //button not held
				curSlow = false;
		}

	if (!curSlow && prevSlow) { //falling edge RUNS ONCE
		for (int i = 0; i < irNum; i++) {
			//sendChar(UART1, 0xA5); //drive to medium
			sendChar(UART1, 0xC3); //drive to high
			sendChar(UART1, 0x0F); //rotation to High
		}
	}

	prevSlow = curSlow;
/*
	if (c->btn5.down) {
		curFast = true;

		if (curFast && !prevFast) { //rising edge
			for (int i = 0; i < irNum; i++) {
				sendChar(UART1, 0x0F); //rotationg to High
				

				//sendChar(UART1, 0xC3); //drive to High
			}

		}

	} else { //button not held
				curFast = false;
		}

	if (!curFast && prevFast) { //falling edge RUNS ONCE
		for (int i = 0; i < irNum; i++) {
			sendChar(UART1, 0xA5); //drive to medium
			sendChar(UART1, 0x96); //rotation to medium
		}
	}

	prevFast = curFast;

*/






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


   if (abs(vexRT[Ch1]) > 45) { //switch state to default (drive + turn)
		if(!((vexRT[Btn6U] == 1) && (vexRT[Btn6D] == 1) && abs(vexRT[Ch3]) > 45)) { //if button not pressed and drive not on
			
			if ((vexRT[Btn6U] == 1) || (vexRT[Btn6D] == 1)) //if lift bypass to drive + lift
			{
				curState = 2;

				for (int i=0; i<irNum; i++){
        			sendChar(UART1, 0x33); // rotate + lift
      			}

				break;
			} else {
				curState = 3;

				for (int i=0; i<irNum; i++){
					sendChar(UART1, 0x3C); //drive + turn
				}
				break;
			}
			
			
     	 }

  	}




	// Right claw forward

			if (vexRT[Btn6D] == 1) { //button down held MOVE Forward
			//if (vexRT[Btn6U] == 1) { //Field Specific FIX BEFORE COMP

				curA = true;

				if (curA && !prevA) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FR_SWITCH] == 1) { //not at limit
						if (slowR == true) {
							motor[right_claw_port] = -45;
						} else {
							motor[right_claw_port] = -100;
						}
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'F';
						slowR = true; // slow true
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
					slowR = false;
			}

			if (posR == 'M' && time1[T2] < 300 && prevPosR == 'F') { //move back from FAR TO MIDDLE
					motor[right_claw_port] = 100;
			} else if (posR == 'M' && time1[T2] >= 300 && prevPosR == 'F') {
					motor[right_claw_port] = 0;
					posR = NULL;
					slowR = false;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (vexRT[Btn6U] == 1) { //button held
			//if (vexRT[Btn6D] == 1) { //Field Specific FIX BEFORE COMP
				curB = true;

				if (curB && !prevB) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BR_SWITCH] == 1) { //not at limit
						if (slowR == true) {
							motor[right_claw_port] = 45;
						} else {
							motor[right_claw_port] = 100;
						}
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'C';
						slowR = true; // slow true
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
					slowR = false;
			}

			if (posR == 'M' && time1[T3] < 400 && prevPosR == 'C') { //move forward from CLOSE to MIDDLE
					motor[right_claw_port] = -100;
			} else if (posR == 'M' && time1[T3] >= 400 && prevPosR == 'C') {
					motor[right_claw_port] = 0;
					posR = NULL;
					slowR = false;
			}



			prevA = curA;
			prevB = curB;



			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (vexRT[Ch3] > 45) {
				up = 1;
			} else {
				up = 0;
			}

			if (vexRT[Ch3] < -45) {
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

						if (slowL == true) {
							motor[left_claw_port] = 45;
						} else {
							motor[left_claw_port] = 100;
						}


						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'F';
						slowL = true; // slow true
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
					slowL = false;
			}

			if (posL == 'M' && time1[T4] < 300 && prevPosL == 'F') {
					motor[left_claw_port] = -100;
			} else if (posL == 'M' && time1[T4] >= 300 && prevPosL == 'F') {
					motor[left_claw_port] = 0;
					posL = NULL;
					slowL = false;
			}






			// left claw backward ////////////////////////////////////////////////////////////
			if (down == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						if (slowL == true) {
							motor[left_claw_port] = -45;
						} else {
							motor[left_claw_port] = -100;
						}
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'C';
						slowL = true;
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
					slowL = false;
			}

			if (posL == 'M' && time1[T1] < 300 && prevPosL == 'C') {
					motor[left_claw_port] = 100;
			} else if (posL == 'M' && time1[T1] >= 300 && prevPosL == 'C') {
					motor[left_claw_port] = 0;
					posL = NULL;
					slowL = false;
			}



			prevC = curC;
			prevD = curD;






    break;

   case 2: //turn + lift

		curState = 2;






		if (abs(vexRT[Ch3]) > 45) { //left joystick moves - switch to drive + lift
			if(!((vexRT[Btn6U] == 1) && (vexRT[Btn6D] == 1) && abs(vexRT[Ch1]) > 45)) { //if button not pressed and drive not on
				


				if (abs(vexRT[Ch1]) > 45) //if rotate bypass to drive + Rotate
				{
					curState = 3;

					for (int i=0; i<irNum; i++){
						sendChar(UART1, 0x3C); // drive + rotate
					}

					break;
				} else {
					curState = 1;
					for (int i=0; i<irNum; i++){
						sendChar(UART1, 0x66); // drive + lift
					}
					break;
				}

				
			}
		}


		 // Right claw forward

			if (vexRT[Btn6D] == 1) { //button down held MOVE Forward
			//if (vexRT[Btn6U] == 1) { //Field Specific FIX BEFORE COMP
				curA = true;

				if (curA && !prevA) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FR_SWITCH] == 1) { //not at limit
						if (slowR == true) {
							motor[right_claw_port] = -45;
						} else {
							motor[right_claw_port] = -100;
						}
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'F';
						slowR = true; // slow true
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
					slowR = false;
			}

			if (posR == 'M' && time1[T2] < 300 && prevPosR == 'F') { //move back from FAR TO MIDDLE
					motor[right_claw_port] = 100;
			} else if (posR == 'M' && time1[T2] >= 300 && prevPosR == 'F') {
					motor[right_claw_port] = 0;
					posR = NULL;
					slowR = false;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (vexRT[Btn6U] == 1) { //button held
			//if (vexRT[Btn6D] == 1) { //Field Specific FIX BEFORE COMP
				curB = true;

				if (curB && !prevB) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BR_SWITCH] == 1) { //not at limit
						if (slowR == true) {
							motor[right_claw_port] = 45;
						} else {
							motor[right_claw_port] = 100;
						}
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'C';
						slowR = true; // slow true
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
					slowR = false;
			}

			if (posR == 'M' && time1[T3] < 400 && prevPosR == 'C') { //move forward from CLOSE to MIDDLE
					motor[right_claw_port] = -100;
			} else if (posR == 'M' && time1[T3] >= 400 && prevPosR == 'C') {
					motor[right_claw_port] = 0;
					posR = NULL;
					slowR = false;
			}



			prevA = curA;
			prevB = curB;
////////////////////////////////////////////////////////////////////////////////////////////turn left claw


			if (vexRT[Ch1] > 45) {
				right = 1;
			} else {
				right = 0;
			}

			if (vexRT[Ch1] < -45) {
				left = 1;
			} else {
				left = 0;
			}

	// Right claw forward


			if (right == 1) { //button held
				curC = true;

				if (curC && !prevC) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_FL_SWITCH] == 1) { //not at limit
						if (slowL == true) {
							motor[left_claw_port] = 45;
						} else {
							motor[left_claw_port] = 100;
						}
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'F';
						slowL = true; // slow true
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
					slowL = false;
			}

			if (posL == 'M' && time1[T4] < 300 && prevPosL == 'F') { //move back from FAR TO MIDDLE
					motor[left_claw_port] = -100;
			} else if (posL == 'M' && time1[T4] >= 300 && prevPosL == 'F') {
					motor[left_claw_port] = 0;
					posL = NULL;
					slowL = false;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (left == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						if (slowL == true) {
							motor[left_claw_port] = -45;
						} else {
							motor[left_claw_port] = -100;
						}
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'C';
						slowL = true; // slow true
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
					slowL = false;
			}

			if (posL == 'M' && time1[T1] < 400 && prevPosL == 'C') { //move forward from CLOSE TO MIDDLE
					motor[left_claw_port] = 100;
			} else if (posL == 'M' && time1[T1] >= 400 && prevPosL == 'C') {
					motor[left_claw_port] = 0;
					posL = NULL;
					slowL = false;
			}



			prevC = curC;
			prevD = curD;





    break;

  default: //drive + turn

	curState = 3;



   if (vexRT[Btn6D] == 1 || vexRT[Btn6U] == 1) {
     if(!(abs(vexRT[Ch1]) > 45 && abs(vexRT[Ch3]) > 45)) { //if button not pressed and drive not on
  		



		if (abs(vexRT[Ch3]) > 45) //if drive bypass to drive + lift
		{
			curState = 1;

			for (int i=0; i<irNum; i++){
				sendChar(UART1, 0x66); // drive + lift
			}

			break;
			} else {
				curState = 2;

				for (int i=0; i<irNum; i++)
				{
					sendChar(UART1, 0x33); //switch to turn + lift
				}
				break;
			}


      }
  }

     if (vexRT[Ch1] > 45) {
				right = 1;
			} else {
				right = 0;
			}

			if (vexRT[Ch1] < -45) {
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
						if (slowR == true) {
							motor[right_claw_port] = -45;
						} else {
							motor[right_claw_port] = -100;
						}
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'F';
						slowR = true; // slow true
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
					slowR = false;
			}

			if (posR == 'M' && time1[T2] < 300 && prevPosR == 'F') { //move back from FAR TO MIDDLE
					motor[right_claw_port] = 100;
			} else if (posR == 'M' && time1[T2] >= 300 && prevPosR == 'F') {
					motor[right_claw_port] = 0;
					posR = NULL;
					slowR = false;
			}




			// Right claw backward ////////////////////////////////////////////////////////////
			if (left == 1) { //button held
				curB = true;

				if (curB && !prevB) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BR_SWITCH] == 1) { //not at limit
						if (slowR == true) {
							motor[right_claw_port] = 45;
						} else {
							motor[right_claw_port] = 100;
						}
						posR = 'G';
				} else {
						motor[right_claw_port] = 0;
						posR = 'C';
						slowR = true; // slow true
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
					slowR = false;
			}

			if (posR == 'M' && time1[T3] < 400 && prevPosR == 'C') { //move forward from CLOSE TO MIDDLE
					motor[right_claw_port] = -100;
			} else if (posR == 'M' && time1[T3] >= 400 && prevPosR == 'C') {
					motor[right_claw_port] = 0;
					posR = NULL;
					slowR = false;
			}



			prevA = curA;
			prevB = curB;




			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (vexRT[Ch3] > 45) {
				up = 1;
			} else {
				up = 0;
			}

			if (vexRT[Ch3] < -45) {
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

						if (slowL == true) {
							motor[left_claw_port] = 45;
						} else {
							motor[left_claw_port] = 100;
						}


						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'F';
						slowL = true; // slow true
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
					slowL = false;
			}

			if (posL == 'M' && time1[T4] < 300 && prevPosL == 'F') {
					motor[left_claw_port] = -100;
			} else if (posL == 'M' && time1[T4] >= 300 && prevPosL == 'F') {
					motor[left_claw_port] = 0;
					posL = NULL;
					slowL = false;
			}






			// left claw backward ////////////////////////////////////////////////////////////
			if (down == 1) { //button held
				curD = true;

				if (curD && !prevD) { //rising edge
					//clearTimer(T1);
				}

				if (SensorValue[CLAW_BL_SWITCH] == 1) { //not at limit
						if (slowL == true) {
							motor[left_claw_port] = -45;
						} else {
							motor[left_claw_port] = -100;
						}
						posL = 'G';
				} else {
						motor[left_claw_port] = 0;
						posL = 'C';
						slowL = true;
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
					slowL = false;
			}

			if (posL == 'M' && time1[T1] < 300 && prevPosL == 'C') {
					motor[left_claw_port] = 100;
			} else if (posL == 'M' && time1[T1] >= 300 && prevPosL == 'C') {
					motor[left_claw_port] = 0;
					posL = NULL;
					slowL = false;
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
