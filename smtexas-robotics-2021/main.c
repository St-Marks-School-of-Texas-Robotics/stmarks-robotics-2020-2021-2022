// includes
#include "controller.h"
#include "joystick_drive.h" //joystick driving functions

// CONSTANTS
#define BASE_DEFAULT_MULT 1 // default multiplier for base movement control
#define BASE_PREC_MULT 0.3 // multiplier for precise base movement control


// movement function, controls the overall movement of the robot
void movement(Controller *c) {
	// moves robot
	//
	// PARAMS
	// 		Controller *c: controller object with input values

	// precise control when up button on right pad (btn8.up) is pressed
	if (c->btn8.up) {
		// multiply x,y joystick values by precise multiplier
		c->Left->x_scale = BASE_PREC_MULT;
		c->Left->y_scale = BASE_PREC_MULT;

	// reset multiplier when not pressing btn
	} else {
		// reset multiplier to the base default multiplier
		c->Left->x_scale = BASE_DEFAULT_MULT;
		c->Left->y_scale = BASE_DEFAULT_MULT;
	}

	// control the robot
	drive_control(c, port2, port3);
}

// main function
task main(){
	// controller initialization
		Controller _con;

		Joystick _LJ, _RJ;
		_LJ.x_scale = BASE_DEFAULT_MULT;
		_LJ.y_scale = BASE_DEFAULT_MULT;
		_RJ.x_scale = 1; // TODO -------------------------------------------------------------------
		_RJ.y_scale = 1; // TODO -------------------------------------------------------------------

		_con.Left = &_LJ;
		_con.Right = &_RJ;
		Controller *c = &_con;

	// TESTS - testing functionalities
		// Base Movement Tests
			// writeDebugStreamLine("instantiated");
			// auto_drive_Test(c, 1, 2);
			//writeDebugStreamLine("autodrive done");

	// main control loop
	while (true) {
		__update_controller(c); // continuously update controller value
		movement(c); // base robot movement
	}
}
