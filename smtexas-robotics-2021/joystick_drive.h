/* joystick_drive.h
Module to enbale movement controls with joystick
Generic Code
*/

#ifndef JOYSTICK_DRIVE_H // include guard
#define JOYSTICK_DRIVE_H

// returns proportional equivalent of x in a to b for f to g
float map(float x, float a, float b, float f, float g) {
	// returns value from one range to another range
	//
	// PARAMS
	//		x: value to map
	// 		a: min for initial range
	// 		b: max for initial range
	// 		f: min for resultant range
	// 		g: max for resultant range

	// formula for ratio
	return (f - g) * (x - a) / (b - a) + f;
}

// calculate angle of y/x with correct signs and catches corner cases
float atan2(int y, int x) {
	// returns angle of y/x
	//
	// PARAMS
	//		 y: y in y/x
  //		 x: x in y/x
	//
	// Note: unorthodox order of (y, x) bc of intentioanlly similarity with default func atan(y/x)

	// result variable
	long result;

	// avoid /0
	if (x == 0) {
		// pi rad when vertical
		result = PI;
	} else {
		// arctan elsewise
		result = atan(y/x);
	}

	// add pi when in 3rd 4th quadrant
	return y < 0 ? result + PI : result;
}


// drive control with x and y values
void joystick_drive(float x, float y, int left_port, int right_port) {
	// move robot with magnitude and direction from x and y value of joystick
	//
	// PARAMS
	// 		float x: pot x value
	// 		float y: pot y value
	// 		int left_port: port num of left motor
	// 		int right_port: port num of right motor

	// writeDebugStreamLine("x: %d", x);
	// writeDebugStreamLine("y: %d", y);

	// calculate the base (unscaled) values for the forward motor outputs
  float left_motor_base, right_motor_base; // right motor base power, left motor base power

  // motor directions (assuming 127, 127 top right)
  // motor values [-100, 100]
  // if fowards

  float mag = sqrt(x * x + y * y); // magnitude of the vector

	// writeDebugStreamLine("mag: %d", mag);
  float bearing = x < 0 | y < 0 ? atan2(y, x) : atan2(y, x); // direction of joystick relative to origin in degrees

  // offset vector by pi/4 degrees
  left_motor_base = mag * cos(bearing - PI/4);
  right_motor_base = mag * sin(bearing - PI/4);


	// writeDebugStreamLine("Left Motor: %d", left_motor_base);
	// writeDebugStreamLine("Right Motor: %d", right_motor_base);
	// writeDebugStreamLine("");

	// set motor values (one motor should be negative
  motor[left_port] = -left_motor_base;
  motor[right_port] = right_motor_base;
}

void drive_control(Controller *c, int left_port, int right_port) {
	// controls base movement with joystick
	//
	// PARAMS
	// 		Controller *c: controller object with its values
	// 		int left_port: port num for left motor
	// 		int right_port: port num for right motor

	Joystick *j = c->Left; // joystick

	// general movement scaling
  int x = j->x_axis * j->x_scale; // x value of movement [-127, 127]
  int y = j->y_axis * j->y_scale; // y value of movement [-127, 127]

  // move robot with joystick values
  joystick_drive(x, y, left_port, right_port);
}


// testing the motor functions with basic movement controls
void drive_test(Controller *c, int left_port, int right_port) {
	// tests basic outputs, used for testing
	//
	// PARAMS
	//		 Controller *c: controller object with input values
	// 		 int left_port: port num of left motor
	//		 int right_port: port num of right motor

	writeDebugStreamLine("Moved Forwards");
	joystick_drive(0, 127, left_port, right_port); // move straight
	wait1Msec(1000); // keep moving straight for 5 secs
	joystick_drive(0, 0, left_port, right_port); // move straight
	wait1Msec(3000); // keep moving straight for 5 secs

	writeDebugStreamLine("Moved Forwards Slower");
	joystick_drive(0, 63, left_port, right_port); // moe straight but slower
	wait1Msec(1000);
	joystick_drive(0, 0, left_port, right_port); // move straight
	wait1Msec(3000); // keep moving straight for 5 secs


	writeDebugStreamLine("Spin");
	joystick_drive(127, 0, left_port, right_port); // spin in place
	wait1Msec(1000); //  for 3 secs
	joystick_drive(0, 0, left_port, right_port); // move straight
	wait1Msec(3000); // keep moving straight for 5 secs

	writeDebugStreamLine("Turn");
	joystick_drive(127*cos(PI/4), 127*sin(PI/4), left_port, right_port); // turn right
	wait1Msec(1000); //  for 3 secs
	joystick_drive(0, 0, left_port, right_port); // move straight
	wait1Msec(3000); // keep moving straight for 5 secs

	writeDebugStreamLine("motor test done");
}

#endif // close guard
