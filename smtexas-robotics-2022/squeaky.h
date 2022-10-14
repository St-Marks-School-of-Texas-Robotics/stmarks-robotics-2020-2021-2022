/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef SQUEAKY_H // include guard
#define SQUEAKY_H


void squeaky_drive(Controller *c, float x, float y, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {

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


	int lift_value;

	if (c->btn6.up) {
		lift_value = -1;
	}
	else if (c->btn6.down) {
		lift_value = 1;
	} else {
		lift_value = 0;
	}



	if ( (lift_value != 0) && (y_final != 0) ) {    // drive + lift
    //sendChar(UART1, 0x55);

		if ( SensorValue[front_left_port] != 1 && SensorValue[back_left_port] != 1 ) {
			motor[left_claw_port] = y_final;
		}

		//right claw
  	if ( SensorValue[front_right_port] != 1 && SensorValue[back_right_port] != 1 ) {
			motor[right_claw_port] = lift_value * 100; // scale to motor value
		}

	}
  else if ( (lift_value != 0) && (x_final != 0) ) {     // turn + lift
    //sendChar(UART1, 0x5A);

    //left claw
  	if ( SensorValue[front_left_port] != 1 && SensorValue[back_left_port] != 1 ) {
			motor[left_claw_port] = x_final;
		}

		//right claw
  	if ( SensorValue[front_right_port] != 1 && SensorValue[back_right_port] != 1 ) {
			motor[right_claw_port] = lift_value * 100; // scale to motor value
		}

  }
  else { // drive + turn
  	//sendChar(UART1, 0x33);



  	if ( SensorValue[front_left_port] != 1 && SensorValue[back_left_port] != 1 ) {
			motor[left_claw_port] = y_final;
		}
		if ( SensorValue[front_right_port] != 1 && SensorValue[back_right_port] != 1 ) {
			motor[right_claw_port] = x_final;
		}

  }










}

void joystick_squeaky_control(Controller *c, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {
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
  squeaky_drive(c, x, y, left_claw_port, right_claw_port, front_left_port, back_left_port, front_right_port, back_right_port); // claw movement
}


#endif // close guard
