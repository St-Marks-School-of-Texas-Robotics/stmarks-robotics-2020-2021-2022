/* tank_drive.h
Module to enbale movement controls with tank controls
Generic Code
*/

#ifndef TEST_DUAL_DRIVE_H // include guard
#define TEST_DUAL_DRIVE_H


// CONSTANTS
#define MOTOR_MAX 100 // maximum power of motor
#define MOTOR_MIN -100 // minimum power of motor

#define JOYSTICK_MAX 127 // maximum joystick value
#define JOYSTICK_MIN -127 // minimum joystick value

// drive control with x and y values
void dual_drive(float y, float x, int left_port, int right_port) {
	// move robot with y value of left joystick controlling left motor and right joystick controlling right motor
	//
	// PARAMS
	// 		float left_motor_base: base value of left joystick y axis
	// 		float right_v: value of right joystick y axis
	// 		int left_port: port num of left motor
	// 		int right_port: port num of right motor

  // motor directions (assuming 127, 127 top right)
  // motor values [-127, 127]

	// map joystick values to motor values
  float y_final = map(y,
																JOYSTICK_MIN,
																JOYSTICK_MAX,
																MOTOR_MIN,
																MOTOR_MAX);
	print

	float x_final = map(x,
															 	 JOYSTICK_MIN,
																 JOYSTICK_MAX,
																 MOTOR_MIN,
																 MOTOR_MAX);

	motor[left_port] = x;
  motor[right_port] = y;
																 /*
	float denominator = max( abs(y_final) + abs(x_final) , 1);

	// set motor values (one motor should be negative
	//turn counter clockwise
  motor[left_port] = (y_final + x_final) / denominator;
  motor[right_port] = -( (y_final - x_final) / denominator );
  */
}

void dual_drive_control(Controller *c, int left_port, int right_port) {
	// controls base movement with joystick
	//
	// PARAMS
	// 		Controller *c: controller object with its values
	// 		int left_port: port num for left motor
	// 		int right_port: port num for right motor

	Joystick *left_joystick = c->Left; // joystick
	Joystick *right_joystick = c->Right; // joystick

	// general movement scaling
  int y = left_joystick->y_scale; // y value of movement [-127, 127]
  int x = right_joystick->x_scale; // x value of movement [-127, 127]

  // move robot with joystick values
  dual_drive(y, x, left_port, right_port);
}

/*
// testing the motor functions with basic movement controls
void tank_drive_test(int left_port, int right_port) {
	// tests basic outputs, used for testing
	//
	// PARAMS
	//		 Controller *c: controller object with input values
	// 		 int left_port: port num of left motor
	//		 int right_port: port num of right motor

	writeDebugStreamLine("Moved Forwards");
	tank_drive(127, 127, left_port, right_port); // move straight
	wait1Msec(1000); // keep moving straight for 1 secs
	tank_drive(0, 0, left_port, right_port); // stop
	wait1Msec(3000); // stop for 3 secs

	writeDebugStreamLine("Moved Forwards Slower");
	tank_drive(63, 63, left_port, right_port); // moe straight but slower
	wait1Msec(1000); // keep moving straight but slower for 1 sec
	tank_drive(0, 0, left_port, right_port); // stop
	wait1Msec(3000); // stop moving for 3 sec

	writeDebugStreamLine("Spin");
	joystick_drive(127, 0, left_port, right_port); // spin right in place
	wait1Msec(1000); // spin for 1 sec
	joystick_drive(0, 0, left_port, right_port); // stop
	wait1Msec(3000); // stop spinning for 3 sec

	writeDebugStreamLine("Turn");
	joystick_drive(127, 63, left_port, right_port); // turn right
	wait1Msec(1000); // turn for 1 secs
	joystick_drive(0, 0, left_port, right_port); // stop
	wait1Msec(3000); // stop turning for 3 sec

	writeDebugStreamLine("tank drive test done");
}
*/

#endif // close guard
