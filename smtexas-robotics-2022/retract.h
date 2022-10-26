/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef RETRACT_H // include guard
#define RETRACT_H

// STATES
//int hinge_position = 0; // hole 0 is no hole
bool retract_postion = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool retract_pressed = false; // right pad right button



// control motor to drop light pole
void retract_claw(Controller *c, int battery_port) {
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
		retract_postion = !retract_postion; // increment flag motor allignment to num hole, avoid exceeding 3

		retract_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (retract_postion) {
		case false: // open position
			motor[battery_port] = 127;
			break;

		case true: // close position
			motor[battery_port] = 95;
			break;
		}

}


#endif // close guard
