

#ifndef BATTERY_H // include guard
#define BATTERY_H

// STATES
//int hinge_position = 0; // hole 0 is no hole
bool battery_postion = false;

// state tracker to only call button function once when pressed
//false when not pressed, true when pressed
bool battery_drop_pressed = false; // right pad right button



// control motor to drop light pole
void drop_battery(Controller *c, int left_wheel, int right_wheel) {
	// drops light poles
	// right pad right button to drop next lightpole
	// right pad bottom button to go back to previous slot
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int pole_port: light pole servo port number

	// reset button state when button is released
	if (!c->btn8.down) {	// right pad right button
		battery_drop_pressed = false; // reset state to false
	}

	// rotate to next hole when button pressed for first time after release
	// 		right pad right button
	if (c->btn8.down  && battery_drop_pressed == false) {
		battery_postion = !battery_postion; // increment flag motor allignment to num hole, avoid exceeding 3

		battery_drop_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (battery_postion) {
		case false: // close position
			motor[left_wheel] = -200;
			motor[right_wheel] = -100;
			break;

		case true: // open position
			motor[left_wheel] = 80;
			motor[right_wheel] = 100;
			break;
		}

}


#endif // close guard
