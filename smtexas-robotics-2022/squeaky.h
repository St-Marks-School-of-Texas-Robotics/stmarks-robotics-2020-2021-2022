/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef SQUEAKY_H // include guard
#define SQUEAKY_H

int prevState = 0;
int curState = 0;

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






  if ( (lift_value != 0) && (abs(x_final) > 5) ) {     // turn + lift

  	curState = 1;

  	if (curState != prevState) {
  		for (int i=0; i<3; i++)
      {
        sendChar(UART1, 0x5A);
      }

  	}




						//left claw forward
  	if ( (SensorValue[CLAW_FL_SWITCH] == 1) && (x_final > 5) ) {

			motor[left_claw_port] = x_final;

		} else if ( (SensorValue[CLAW_BL_SWITCH] == 1) && (x_final < -5) ) {   //right claw back

			motor[left_claw_port] = x_final;

		} else {
			motor[left_claw_port] = 0;
		}


				//right claw forward
  	if ( (SensorValue[CLAW_FR_SWITCH] == 1) && (lift_value == -1) ) {

			motor[right_claw_port] = -lift_value * 50;

		} else if ( (SensorValue[CLAW_BR_SWITCH] == 1) && (lift_value == 1) ) {   //right claw back

			motor[right_claw_port] = -lift_value * 50;

		} else {
			motor[right_claw_port] = 0;
		}

  }
  else if (lift_value != 0) {    // drive + lift

  	curState = 2;

  	if (curState != prevState) {
  		for (int i=0; i<3; i++)
      {
        sendChar(UART1, 0x55);
      }

  	}




		//left claw forward
  	if ( (SensorValue[CLAW_FL_SWITCH] == 1) && (y_final > 5) ) {

			motor[left_claw_port] = -y_final;

		} else if ( (SensorValue[CLAW_BL_SWITCH] == 1) && (y_final < -5) ) {   //left claw back

			motor[left_claw_port] = -y_final;

		} else {
			motor[left_claw_port] = 0;
		}




				//right claw forward
  	if ( (SensorValue[CLAW_FR_SWITCH] == 1) && (lift_value == -1) ) {

			motor[right_claw_port] = lift_value * 50;

		} else if ( (SensorValue[CLAW_BR_SWITCH] == 1) && (lift_value == 1) ) {   //right claw back

			motor[right_claw_port] = lift_value * 50;

		} else {
			motor[right_claw_port] = 0;
		}


	}
  else { // drive + turn

  	curState = 3;

  	if (curState != prevState) {
  		for (int i=0; i<3; i++)
      {
        sendChar(UART1, 0x33);
      }

  	}





		//left claw forward
  	if ( (SensorValue[CLAW_FL_SWITCH] == 1) && (y_final > 5) ) {

			motor[left_claw_port] = -y_final;

		} else if ( (SensorValue[CLAW_BL_SWITCH] == 1) && (y_final < -5) ) {   //left claw back

			motor[left_claw_port] = -y_final;

		} else {
			motor[left_claw_port] = 0;
		}


				//right claw forward
  	if ( (SensorValue[CLAW_FR_SWITCH] == 1) && (x_final > 5) ) {

			motor[right_claw_port] = -x_final;

		} else if ( (SensorValue[CLAW_BR_SWITCH] == 1) && (x_final < -5) ) {   //right claw back

			motor[right_claw_port] = -x_final;

		} else {
			motor[right_claw_port] = 0;
		}


  }







	prevState = curState;


}

void joystick_squeaky_control(Controller *c, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {
	// controls base movement with joystick
	//
	// PARAMS
	// 		Controller *c: controller object with its values
	// 		int left_port: port num for left motor
	// 		int right_port: port num for right motor

	Joystick *l = c->Left; // joystick
	Joystick *r = c->Right; // joystick

	// general movement scaling
  int x = r->x_axis * r->x_scale; // x value of movement [-127, 127]
  int y = l->y_axis * l->y_scale; // y value of movement [-127, 127]

  // move robot with joystick values
  squeaky_drive(c, x, y, left_claw_port, right_claw_port, front_left_port, back_left_port, front_right_port, back_right_port); // claw movement
}


#endif // close guard
