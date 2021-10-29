#ifndef LIFT_H // include guard
#define LIFT_H

// control motor to lift the claw
void operate_lift(Controller *c, int lift_port) {
	// [button] to go up, [button] to go down
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int lift_port: port number of motor to lift claw

	// lift claw when button pressed
	// 		right pad right button
	if (c->btn8.right) {
		pole_current_hole == 3 ? 3 : pole_current_hole++; // increment flag motor allignment to num hole, avoid exceeding 4
		drop_pressed = true; // set state to true to not call function until after another button release
	}

	// drop claw when button pressed
	// 		right pad bottom button
	else if (c->btn8.down) {
		pole_current_hole == 0 ? 0 : pole_current_hole--; // decrement flag motor allignment to num hole, avoid exceeding 0
		drop_pressed = true; // set state to true to not call function until after another button release
	}
}

// control motor to open/close the claw
void operate_claw(Controller *c, int claw_port) {
	// [button] to go up, [button] to go down
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int claw_port: port number of motor to open/close claw

	// lift claw when button pressed
	// 		right pad right button
	if (c->btn8.right) {
		}

	// drop claw when button pressed
	// 		right pad bottom button
	else if (c->btn8.down && undrop_pressed == false) {
		}
}

// test claw functionallity
void lift_TEST(int lift_port) {
	// open close claw
	// PARAMS
	//		int lift_port: port number of lifting motor

	return; //---------------------------------------------------------------------------------------------------

	writeDebugStreamLine("claw test start");

	writeDebugStreamLine("Hole -Home");
	motor[lift_port] = 307;
	wait1Msec(5000);

	writeDebugStreamLine("Hole Home");
	motor[lift_port] = 127;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 1");
	motor[lift_port] = 60;
	wait1Msec(2000);

	writeDebugStreamLine("claw test done");
}

// test claw functionallity
void claw_TEST(int claw_port) {
	// open close claw
	// PARAMS
	//		int claw_port: port number of claw motor

	return; //---------------------------------------------------------------------------------------------------

	writeDebugStreamLine("claw test start");

	writeDebugStreamLine("Hole -Home");
	motor[claw_port] = 307;
	wait1Msec(5000);

	writeDebugStreamLine("Hole Home");
	motor[claw_port] = 127;
	wait1Msec(2000);

	writeDebugStreamLine("Hole 1");
	motor[claw_port] = 60;
	wait1Msec(2000);

	writeDebugStreamLine("claw test done");
}

#endif
