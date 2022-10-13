/* autonomous.h
enables autonomous code for 2021 BEST competition
Non-Generic Code but can be easily modified by changing motor values
*/

#ifndef AUTO_H // include guard
#define AUTO_H

// CONSTANTS
#define WAIT_ITER 3000 // number of program iterations open to abort

// STATES
bool auto_run_state = false; // if the autonomous is running
int wait_iter = WAIT_ITER; // the width of time window for abort

// pure autonomous code, NON-ABORT, for testing and for in game
void auto_run(int left_port, int right_port, int arm_port, int left_claw_port, int right_claw_port) {
	// autonomous mode
	// start from arm up, claw closed, and alligned outside of box
	// moves forward, drops arm, and moves back, pulling the bundle out
	// lifts arm, and moves back to allow for easy transition to pickup
	//
	// PARAMS
	// 		int left_port: left motor port number
	// 		int right_port: right motor port number
	// 		int arm_port: arm motor port number
	// 		int left_claw_port: left claw motor port number
	// 		int right_claw_port: right claw motor port number

	writeDebugStreamLine("autonomous start");

	// move forwards
	motor[left_port] = -127;
	motor[right_port] = 85;

	// arm up
	writeDebugStreamLine("arm up");
	motor[arm_port] = 127;

	// open claw
	writeDebugStreamLine("claw open");
	motor[left_claw_port] = 127;
	motor[right_claw_port] = -127;

	wait1Msec(1800);

	// stop
	writeDebugStreamLine("move stop");
	motor[left_port] = 0;
	motor[right_port] = 0;


	// drop arm down
	writeDebugStreamLine("arm down");
	motor[arm_port] = -100;

	wait1Msec(880);

	// close claw
	writeDebugStreamLine("claw close");
	motor[left_claw_port] = -100;
	motor[right_claw_port] = 100;

	// wait quickly
	wait1Msec(500);

	// move back
	writeDebugStreamLine("move back");
	motor[left_port] = 127;
	motor[right_port] = -85;

	wait1Msec(2700);

	// motor stop
	motor[left_port] = 0;
	motor[right_port] = 0;

	// arm up
	motor[arm_port] = 127;

	wait1Msec(400);

	// move back
	motor[left_port] = 85;
	motor[right_port] = -127;

	wait1Msec(500);

	writeDebugStreamLine("autonomous end");
	}

// first part of autonomous, for testing and for in game
void auto_run_first(int left_port, int right_port, int arm_port, int left_claw_port, int right_claw_port) {
	// autonomous mode
	// start from arm up, claw closed, and alligned outside of box
	// moves forward, drops arm, and moves back, pulling the bundle out
	// lifts arm, and moves back to allow for easy transition to pickup
	//
	// PARAMS
	// 		int left_port: left motor port number
	// 		int right_port: right motor port number
	// 		int arm_port: arm motor port number
	// 		int left_claw_port: left claw motor port number
	// 		int right_claw_port: right claw motor port number

	writeDebugStreamLine("autonomous start");

	// move forwards
	motor[left_port] = -127;
	motor[right_port] = 85;

	// arm up
	writeDebugStreamLine("arm up");
	motor[arm_port] = 127;

	// open claw
	writeDebugStreamLine("claw open");
	motor[left_claw_port] = 127;
	motor[right_claw_port] = -127;

	wait1Msec(1000);

	// stop
	writeDebugStreamLine("move stop");
	motor[left_port] = 0;
	motor[right_port] = 0;

	writeDebugStreamLine("autonomous end");
	}

// second part of autonomous, for testing and for in game
void auto_run_second(int left_port, int right_port, int arm_port, int left_claw_port, int right_claw_port) {
	// autonomous mode
	// start from arm up, claw closed, and alligned outside of box
	// moves forward, drops arm, and moves back, pulling the bundle out
	// lifts arm, and moves back to allow for easy transition to pickup
	//
	// PARAMS
	// 		int left_port: left motor port number
	// 		int right_port: right motor port number
	// 		int arm_port: arm motor port number
	// 		int left_claw_port: left claw motor port number
	// 		int right_claw_port: right claw motor port number

	writeDebugStreamLine("autonomous start");

	// move forwards
	motor[left_port] = -127;
	motor[right_port] = 85;

	// arm up
	writeDebugStreamLine("arm up");
	motor[arm_port] = 127;

	// open claw
	writeDebugStreamLine("claw open");
	motor[left_claw_port] = 127;
	motor[right_claw_port] = -127;

	wait1Msec(800);

	// stop
	writeDebugStreamLine("move stop");
	motor[left_port] = 0;
	motor[right_port] = 0;

	writeDebugStreamLine("autonomous end");

	// drop arm down
	writeDebugStreamLine("arm down");
	motor[arm_port] = -100;

	wait1Msec(880);

	// close claw
	writeDebugStreamLine("claw close");
	motor[left_claw_port] = -100;
	motor[right_claw_port] = 100;

	// wait quickly
	wait1Msec(500);

	// move back
	writeDebugStreamLine("move back");
	motor[left_port] = 127;
	motor[right_port] = -85;

	wait1Msec(2700);

	// motor stop
	motor[left_port] = 0;
	motor[right_port] = 0;

	// arm up
	motor[arm_port] = 127;

	wait1Msec(400);

	// move back
	motor[left_port] = 85;
	motor[right_port] = -127;

	wait1Msec(500);

	writeDebugStreamLine("autonomous end");
}

// autonomous portion of competition
// pull arm up while going in
// wait in between to allow for abort
// if not abort
		// pick drop arm down, grap bundle with claw
		// lift bundle up and move back out
// if abort
		// move back
void autonomous(Controller *c, int left_port, int right_port, int arm_port, int left_claw_port, int right_claw_port) {
	// runs autonomous when detect controller
	//
	// PARAMS
	//		Controller *c: controller object to read input
	//		int left_port: left motor port number
	//		int right_port: right motor port number
	//		int arm_port: arm motor port number
	// 		int left_claw_port: left claw motor port number
	// 		int right_claw_port: right claw motor port number


	// run when left button left group pressed
	//		left group left button
	if (c->btn7.left) {
		// auto_run(left_port, right_port, arm_port, left_claw_port, right_claw_port);
		auto_run_first(left_port, right_port, arm_port, left_claw_port, right_claw_port);
		auto_run_state = true; // auto mode is on
	}

	// if automode is on
	if (auto_run_state){
		// if abort is activated
		// 		left group top button
		if (c->btn7.up) {
			// move back
			writeDebugStreamLine("move back");
			motor[left_port] = 127;
			motor[right_port] = -85;

			wait1Msec(1900);

			// motor stop
			motor[left_port] = 0;
			motor[right_port] = 0;
			auto_run_state = false;

			wait_iter = WAIT_ITER; // reset wait iterations

		// run second half of auto if wait time over
		} else if (wait_iter < 0) {
			auto_run_second(left_port, right_port, arm_port, left_claw_port, right_claw_port); // second half of auto
			wait_iter = WAIT_ITER; // reset wait time
			auto_run_state = false; // not in auto

		} else {
			wait_iter -= 1; // decrement iter counter
		}
	}
}

#endif // close guard
