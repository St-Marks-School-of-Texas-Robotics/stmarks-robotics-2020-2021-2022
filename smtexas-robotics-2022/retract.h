/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef RETRACT_H // include guard
#define RETRACT_H

// STATES
//int hinge_position = 0; // hole 0 is no hole
bool retract_position = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool retract_pressed = false; // right pad right button

bool left_state = false; // right pad right button
bool right_state = false; // right pad right button


// control motor to drop light pole
void retract_claw(Controller *c, int left_claw, int right_claw) {
	// drops light poles
	// right pad right button to drop next lightpole
	// right pad bottom button to go back to previous slot
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int pole_port: light pole servo port number

	// reset button state when button is released
	if (!c->btn8.left) {	// right pad right button
		retract_pressed = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn8.left  && retract_pressed == false) {
		retract_position = !retract_position; // increment flag motor allignment to num hole, avoid exceeding 3

		retract_pressed = true; // set state to true to not call function until after another button release
		left_state = true;
		right_state = true;
		clearTimer(T2); //start timer 2
	}


	// set the servo value according to the hole number
	if (retract_position) {

		if (left_state) {

			if ( (SensorValue[CLAW_BL_SWITCH] == 1) && (time1[T2] < 3500) ) {   //left claw back

				motor[left_claw] = -50;

			} else {
				motor[left_claw] = 0;
				left_state = false;
			}
		}

		if (right_state) {

			if ( (SensorValue[CLAW_BR_SWITCH] == 1) && (time1[T2] < 3500) ) {   //left claw back

				motor[right_claw] = 50;

			} else {
				motor[right_claw] = 0;
				right_state = false;
			}
		}

		if (!left_state && !right_state) {
			retract_position = false;
		}


	}

}


#endif // close guard
