/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef ARM_H // include guard
#define ARM_H

// STATES
//int hinge_position = 0; // hole 0 is no hole
bool arm_postion = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool arm_drop_pressed = false; // right pad right button



// control motor to drop light pole
void drop_arm(Controller *c, int arm_port) {
	// drops light poles
	// right pad right button to drop next lightpole
	// right pad bottom button to go back to previous slot
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int pole_port: light pole servo port number

	// reset button state when button is released
	if (!c->btn7.right) {	// right pad right button
		arm_drop_pressed = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn7.right  && arm_drop_pressed == false) {
		arm_postion = !arm_postion; // increment flag motor allignment to num hole, avoid exceeding 3

		arm_drop_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (arm_postion) {
		case false: // close position
			motor[arm_port] = 0;
			break;

		case true: // open position
			motor[arm_port] = 70;
			break;
		}

}


#endif // close guard
