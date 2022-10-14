/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef IR_CONTROL_H // include guard
#define IR_CONTROL_H

// STATES
int ir_current_state = 0; // hole 0 is no hole

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool cycle_pressed = false; // right pad right button
bool uncycle_pressed = false; // right pad down button


// control motor to drop light pole
void ir_switcher(Controller *c, int pole_port) {
	// drops light poles
	// right pad right button to drop next lightpole
	// right pad bottom button to go back to previous slot
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int pole_port: light pole servo port number

	// reset button state when button is released
	if (!c->btn7.right) {	// right pad right button
		cycle_pressed = false; // reset state to false
	}

	// reset button state when button is released
	if (!c->btn7.left) { // right pad down button
		uncycle_pressed = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn7.right  && cycle_pressed == false) {
		ir_current_state = min(3, pole_current_hole + 1); // increment flag motor allignment to num hole, avoid exceeding 3

		cycle_pressed = true; // set state to true to not call function until after another button release
	}

	// rotate to prev  pole when button pressed for first time after release
	// 		right pad bottom button
	else if (c->btn7.left && uncycle_pressed == false) {
		ir_current_state = max(0, pole_current_hole - 1); // decrement flag motor allignment to num hole, avoid below 0

		uncycle_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (ir_current_state) {
		case 0: // home port
			sendChar(UART1, 0xAA) //default level order
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
