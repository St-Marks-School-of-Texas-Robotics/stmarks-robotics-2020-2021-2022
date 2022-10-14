/* tank_drive.h
Module to enbale movement controls with tank controls
Generic Code
*/

#ifndef TEST_DUAL_DRIVE_H // include guard
#define TEST_DUAL_DRIVE_H

// CONSTANTS


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

	float x_final = map(x,
															 	 JOYSTICK_MIN,
																 JOYSTICK_MAX,
																 MOTOR_MIN,
																 MOTOR_MAX);

	float denominator = max( abs(y_final) + abs(x_final) , 1);

	// set motor values (one motor should be negative
	//turn counter clockwise
  motor[left_port] = (y_final + x_final) / denominator;
  motor[right_port] = -( (y_final - x_final) / denominator );
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



#endif // close guard
