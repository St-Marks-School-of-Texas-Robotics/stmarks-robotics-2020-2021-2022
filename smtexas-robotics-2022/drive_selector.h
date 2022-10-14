/* tank_drive.h
Module to enbale movement controls with tank controls
Generic Code
*/
#include "main.c" // ir uart


#ifndef DRIVE_SELECTOR_H // include guard
#define DRIVE_SELECTOR_H

// CONSTANTS
bool is_squeaky = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool drive_switch = false; // right pad right button

// drive control with x and y values
void drive_mode() {


	if (!c->btn7.up) {	// right pad right button
		drive_switch = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn7.up  && drive_switch == false) {
		is_squeaky = !is_squeaky; // increment flag motor allignment to num hole, avoid exceeding 3

		drive_switch = true; // set state to true to not call function until after another button release
	}

		// set the servo value according to the hole number
	switch (is_squeaky) {
		case false: // open position
			joystick_drive_control(c, left_port, right_port);
			break;

		case true: // close position
			joystick_squeaky_control(c, LEFT_CLAW_MOTOR, RIGHT_CLAW_MOTOR, CLAW_FL_SWITCH, CLAW_BL_SWITCH, CLAW_FR_SWITCH, CLAW_BR_SWITCH);;
			break;
		}


}




#endif // close guard
