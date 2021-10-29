#ifndef CONTROLLER_H // include guard
#define CONTROLLER_H

// void loop(Controller *c);
// void __update_controller(Controller *c);

// void init(Controller *c);

// struct Buttons
typedef struct {
		// 4 button groups [5-8]

		// boolean values for button press
    bool up, down; // [5-8]
    bool left, right; // only the button pads [7-8]
} Buttons;

// struct Joystick
typedef struct {
		// 2 joysticks [(1,2), (3,4)]
		// ints range (-127, 127) for stick position

		// floats for multiplier
    int x_axis, y_axis; // [(1,2), (3,4)]
    float x_scale, y_scale; // scaling multiplier

} Joystick;

// struct Controller
typedef struct {
		// components of controller
		// 		2 joysticks [(1,2), (3,4)]
		// 		4 button groups [5-8]

		// Joysticks
    Joystick *Left, *Right; // joystick left and right

    // Buttons Groups
    Buttons btn5, btn6; // top left bumpers, top right bumpers separate because only top down buttons
    Buttons btn7, btn8; // left button group, right button group
} Controller;

// __update _controller
void __update_controller(Controller *c) {
  // updates controller with button and joystick values
	//
  // PARAMS
  // 		Controller *c:	Controller object with all input values

  // left joystick
  c->Left->x_axis = vexRT[Ch4];
  c->Left->y_axis = vexRT[Ch3];

  // right joystick
  c->Right->x_axis = vexRT[Ch1];
  c->Right->y_axis = vexRT[Ch2];

  // top left bumpers
  c->btn5.up = vexRT[Btn5U] > 0;
  c->btn5.down = vexRT[Btn5D] > 0;

  // top right bumpers
  c->btn6.up = vexRT[Btn6U] > 0;
  c->btn6.down = vexRT[Btn6D] > 0;

  // left button pad
  c->btn7.up = vexRT[Btn7U] > 0;
  c->btn7.down = vexRT[Btn7D] > 0;
  c->btn7.left = vexRT[Btn7L] > 0;
  c->btn7.right = vexRT[Btn7R] > 0;

  // right button pad
  c->btn8.up = vexRT[Btn8U] > 0;
  c->btn8.down = vexRT[Btn8D] > 0;
  c->btn8.left = vexRT[Btn8L] > 0;
  c->btn8.right = vexRT[Btn8R] > 0;
}

#endif
