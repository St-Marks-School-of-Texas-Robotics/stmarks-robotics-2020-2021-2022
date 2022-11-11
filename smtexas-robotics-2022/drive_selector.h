/* tank_drive.h
Module to enbale movement controls with tank controls
Generic Code
*/

#ifndef DRIVE_SELECTOR_H // include guard
#define DRIVE_SELECTOR_H

// CONSTANTS
bool is_squeaky = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool drive_switch = false; // right pad right button

// drive control with x and y values
void drive_mode(Controller *c, int left_port,  int right_port, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {


	if (!c->btn7.up) {	// right pad right button
		drive_switch = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn7.up  && drive_switch == false) {
		is_squeaky = !is_squeaky; // increment flag motor allignment to num hole, avoid exceeding 3

		drive_switch = true; // set state to true to not call function until after another button release

		sendChar(UART1, 0x3C);
	}

		// set the servo value according to the hole number
	switch (is_squeaky) {
		case false: // open position
			joystick_drive_control(c, left_port, right_port);
			break;

		case true: // close position
			joystick_squeaky_control(c, left_claw_port, right_claw_port, front_left_port, back_left_port, front_right_port, back_right_port);
			break;
		}


}




#endif // close guard
