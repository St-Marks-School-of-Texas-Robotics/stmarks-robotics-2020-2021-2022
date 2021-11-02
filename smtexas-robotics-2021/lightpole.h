<<<<<<< HEAD
#ifndef LIGHTPOLE_H // include guard
#define LIGHTPOLE_H

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
		pole_current_hole = pole_current_hole == 3 ? 3 : pole_current_hole + 1; // increment flag motor alignment to num hole, avoid exceeding 4
		drop_pressed = true; // set state to true to not call function until after another button release
	}

	// rotate to prev  pole when button pressed for first time after release
	// 		right pad bottom button
	else if (c->btn8.down && undrop_pressed == false) {
		pole_current_hole = pole_current_hole == 0 ? 0 : pole_current_hole - 1; // decrement flag motor alignment to num hole, avoid exceeding 0
		undrop_pressed = true; // set state to true to not call function until after another button release
	}



	// set the servo value according to the hole number
	// motor[pole_port] = c->btn8.up ? 127 : -127;


	switch (pole_current_hole) {
		case 0: // home port
			motor[pole_port] = 127;
			break;

		case 1: // hole 1
			motor[pole_port] = 55;
			break;

		case 2: // hole 2
			motor[pole_port] = -60;
			break;

		case 3: // hole 3
			motor[pole_port] = -127;
			break;
	}

}

void pole_test(int pole_port) {
	writeDebugStreamLine("pole test start");

	//writeDebugStreamLine("Hole -Home");
	//motor[pole_port] = 127;
	//wait1Msec(5000);

	writeDebugStreamLine("Hole Home");
	motor[pole_port] = 127;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 1");
	motor[pole_port] = 60;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 2");
	motor[pole_port] = -60;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 31");
	motor[pole_port] = -107;
	wait1Msec(2000);


	writeDebugStreamLine("Hole 32");
	motor[pole_port] = -117;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 33");
	motor[pole_port] = -127;
	wait1Msec(2000);


	writeDebugStreamLine("Hole 34");
	motor[pole_port] = -137;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 35");
	motor[pole_port] = -142;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 35");
	motor[pole_port] = -147;
	wait1Msec(2000);

	writeDebugStreamLine("pole test done");
}

#endif
=======
#ifndef LIGHTPOLE_H // include guard
#define LIGHTPOLE_H

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
		pole_current_hole = pole_current_hole == 3 ? 3 : pole_current_hole++; // increment flag motor allignment to num hole, avoid exceeding 4
		drop_pressed = true; // set state to true to not call function until after another button release
	}

	// rotate to prev  pole when button pressed for first time after release
	// 		right pad bottom button
	else if (c->btn8.down && undrop_pressed == false) {
		pole_current_hole = pole_current_hole == 0 ? 0 : pole_current_hole--; // decrement flag motor allignment to num hole, avoid exceeding 0
		drop_pressed = true; // set state to true to not call function until after another button release
	}


	// set the servo value according to the hole number
	switch (pole_current_hole) {
		case 0: // home port
			motor[pole_port] = 127;
			break;

		case 1: // hole 1
			motor[pole_port] = 70;
			break;

		case 2: // hole 2
			motor[pole_port] = -50;
			break;

		case 3: // hole 3
			motor[pole_port] = -127;
			break;
	}
}

void pole_test(int pole_port) {
	writeDebugStreamLine("pole test start");

	writeDebugStreamLine("Hole -Home");
	motor[pole_port] = 307;
	wait1Msec(5000);

	writeDebugStreamLine("Hole Home");
	motor[pole_port] = 127;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 1");
	motor[pole_port] = 60;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 2");
	motor[pole_port] = -50;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 31");
	motor[pole_port] = -107;
	wait1Msec(2000);


	writeDebugStreamLine("Hole 32");
	motor[pole_port] = -117;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 33");
	motor[pole_port] = -127;
	wait1Msec(2000);


	writeDebugStreamLine("Hole 34");
	motor[pole_port] = -137;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 35");
	motor[pole_port] = -142;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 35");
	motor[pole_port] = -147;
	wait1Msec(2000);

	writeDebugStreamLine("pole test done");
}

#endif
>>>>>>> 43eb5bfa031c9f4f3664b848caca763bc38bcb4e
