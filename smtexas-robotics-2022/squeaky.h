/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef SQUEAKY_H // include guard
#define SQUEAKY_H

int prevState = 0;
int curState = 0;

bool curA = false;
bool prevA = false;
bool curB = false;
bool prevB = false;

bool curC = false;
bool prevC = false;
bool curD = false;
bool prevD = false;

int up = 0;
int down = 0;

char posR = NULL;
char prevPosR = NULL;
char posL = NULL;
char prevPosL = NULL;

void squeaky_drive(Controller *c, float x, float y, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {


	if ((vexRT[Btn6D] == 1 || vexRT[Btn6U] == 1) && (abs(vexRT[Ch3]) > 15)) {
			curState = 1;
	}


	// Change between states
	switch (curState) {
		case 1: // open position

			break;

		case 2: // close position

			break;
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
