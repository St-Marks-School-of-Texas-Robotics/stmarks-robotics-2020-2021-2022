/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef HINGE_H // include guard
#define HINGE_H

// STATES
//int hinge_position = 0; // hole 0 is no hole
bool hinge_postion = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool hinge_drop_pressed = false; // right pad right button

// control motor to drop light pole
void close_hinge(Controller *c, int hinge_port) {

	if (!c->btn8.right) {	// right pad right button
		hinge_drop_pressed = false; // reset state to false
	}

	// 		right pad right button
	if (c->btn8.right  && hinge_drop_pressed == false) {
		hinge_postion = !hinge_postion; // increment flag motor allignment to num hole, avoid exceeding 3

		hinge_drop_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (hinge_postion) {
		case false: // up position
			motor[hinge_port] = 90;
			if (c->btn8.down) {
				hinge_postion = true;
			}


			break;

		case true: // down position
			motor[hinge_port] = -150;
			break;
		}

}

void hinge_test(int pole_port) {
	writeDebugStreamLine("hinge test start");

	writeDebugStreamLine("hinge up");
	motor[pole_port] = -127;
	wait1Msec(2000);

	writeDebugStreamLine("hinge down");
	motor[pole_port] = 80;
	wait1Msec(1000);

	writeDebugStreamLine("hinge test done");
}


#endif // close guard
