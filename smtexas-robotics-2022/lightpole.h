/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef LIGHTPOLE_H // include guard
#define LIGHTPOLE_H

// STATES
int pole_current_hole = 0; // hole 0 is no hole

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool drop_pressed = false; // right pad right button
bool undrop_pressed = false; // right pad down button


// control motor to drop light pole
void drop_light_pole(Controller *c, int pole_port) {
	// drops light poles
	// right pad right button to drop next lightpole
	// right pad bottom button to go back to previous slot
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int pole_port: light pole servo port number

	// reset button state when button is released
	if (!c->btn8.right) {	// right pad right button
		drop_pressed = false; // reset state to false
	}

	// reset button state when button is released
	if (!c->btn8.down) { // right pad down button
		undrop_pressed = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn8.right  && drop_pressed == false) {
		pole_current_hole = min(3, pole_current_hole + 1); // increment flag motor allignment to num hole, avoid exceeding 3

		drop_pressed = true; // set state to true to not call function until after another button release
	}

	// rotate to prev  pole when button pressed for first time after release
	// 		right pad bottom button
	else if (c->btn8.down && undrop_pressed == false) {
		pole_current_hole = max(0, pole_current_hole - 1); // decrement flag motor allignment to num hole, avoid below 0

		drop_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (pole_current_hole) {
		case 0: // home port
			motor[pole_port] = 127;
			break;

		case 1: // hole 1
			motor[pole_port] = 95;
			break;

		case 2: // hole 2
			motor[pole_port] = 0;
			break;

		case 3: // hole 3
			motor[pole_port] = -100;
			break;
	}
}


// testing the lightpole dropper servo locations
void pole_test(int pole_port) {
	writeDebugStreamLine("pole test start");

	writeDebugStreamLine("Hole Home");
	motor[pole_port] = 127;
	wait1Msec(1000);

	writeDebugStreamLine("Hole 1");
	motor[pole_port] = 80;
	wait1Msec(200);
	writeDebugStreamLine("Hole 1");
	motor[pole_port] = 100;
	wait1Msec(1000);

	writeDebugStreamLine("Hole 2");
	motor[pole_port] = 0;
	wait1Msec(1000);

	writeDebugStreamLine("Hole 2");
	motor[pole_port] = -100;
	wait1Msec(1000);

	writeDebugStreamLine("pole test done");
}

#endif // close guard
