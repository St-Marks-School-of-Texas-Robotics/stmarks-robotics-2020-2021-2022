/* joystick_drive.h
Module to enbale movement controls with joystick
Generic Code
*/

#ifndef JOYSTICK_DRIVE_H // include guard
#define JOYSTICK_DRIVE_H

// CONSTANTS
#define MOTOR_MAX 100 // maximum power of motor
#define MOTOR_MIN -100 // minimum power of motor

#define JOYSTICK_MAX 127 // maximum joystick value
#define JOYSTICK_MIN -127 // minimum joystick value

// drive control with x and y values
void joystick_drive(float x, float y, int left_port, int right_port) {
	// move robot with magnitude and direction from x and y value of joystick
	//
	// PARAMS
	// 		float x: pot x value
	// 		float y: pot y value
	// 		int left_port: port num of left motor
	// 		int right_port: port num of right motor

  // motor directions (assuming 127, 127 top right)
  // motor values [-127, 127]

  float mag = sqrt(x * x + y * y); // magnitude of the vector

  float bearing = atan2(y, x); // direction of joystick relative to origin in degrees
	bearing -= PI / 4; // offset bearing by pi / 4 radians

	// calculate the base (unscaled) values for the forward motor outputs
  // offset vector by pi/4 degrees
  float left_motor_base = mag * cos(bearing); // left motor base power
  float right_motor_base = mag * sin(bearing); // right motor base power

  // if 0, make value very very close to 0 but not 0 to prevent division by 0
  left_motor_base = left_motor_base < 0 ? min(left_motor_base, -.000001) :
  																	 			max(left_motor_base, .000001);

  right_motor_base = right_motor_base < 0 ? min(right_motor_base, -.000001) :
  																	 			max(right_motor_base, .000001);

  float left_motor_mapped = map(left_motor_base,
																JOYSTICK_MIN * abs(cos(bearing)),
																JOYSTICK_MAX * abs(cos(bearing)),
																MOTOR_MIN,
																MOTOR_MAX);

	float right_motor_mapped = map(right_motor_base,
															 	 JOYSTICK_MIN * abs(sin(bearing)),
																 JOYSTICK_MAX * abs(sin(bearing)),
																 MOTOR_MIN,
																 MOTOR_MAX);

  float mult = min(abs(left_motor_mapped / left_motor_base), abs(right_motor_mapped / right_motor_base));

  // map motors from angled proportion to to max motor proportion
  float left_motor_final = left_motor_base * mult;
	float right_motor_final = right_motor_base * mult;

	// set motor values (one motor should be negative
  motor[left_port] = -left_motor_final;
  motor[right_port] = right_motor_final;
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
void drive_test(int left_port, int right_port) {
	// tests basic outputs, used for testing
	//
	// PARAMS
	//		 Controller *c: controller object with input values
	// 		 int left_port: port num of left motor
	//		 int right_port: port num of right motor

	// writeDebugStreamLine("100 Speed");
	// motor[left_port] = 100;
	// wait1Msec(30000);

	// motor[left_port] = 0;
	//wait1Msec(5000);

	writeDebugStreamLine("127 Speed");
	motor[left_port] = 127;
	wait1Msec(30000);

	writeDebugStreamLine("100 Speed");

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
