/* main.c
Main Code for Demolition 2021 BEST Robotics
St. Mark's Robotics Team
for help, consult c_help.txt and setup_help.txt
or contact Isaac Song at isaacsong03@gmail.com
*/

// INCLUDES
#include "helper.h" // helper functions
#include "controller.h" // controller object
#include "joystick_drive.h" // joystick driving functions
#include "lightpole.h" // lightpole operator
#include "lift.h" // operate lift
#include "autonomous.h" // autonomous portion

#include "calc_test.h" // testing calculations

// PORTS ASSIGNMENTS
#define LEFT_MOTOR port2
#define RIGHT_MOTOR port3
#define POLE_SERVO port5
#define ARM_MOTOR port7
#define LEFT_CLAW_SERVO port8
#define RIGHT_CLAW_SERVO port9

// CONSTANTS
#define BASE_DEFAULT_MULT 1 // default multiplier for base control
#define BASE_PREC_MULT 0.5 // multiplier for precise base control

// movement function, controls the overall movement of the robot
void movement(Controller *c, int left_port, int right_port) {
	// moves robot
	//
	// PARAMS
	// 		Controller *c: controller object with input values
	//		int left_port: left motor port number
	// 		int right_port: right motor port number

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
	joystick_drive_control(c, left_port, right_port);
}

// main function
task main(){
	// controller initialization
		// create controller objects
		Controller _con;

		// setup joystick
		Joystick _LJ, _RJ; // create joystick object
		_LJ.x_scale = BASE_DEFAULT_MULT; // base multiplier of left joystick x-values
		_LJ.y_scale = BASE_DEFAULT_MULT; // base multiplier of left joystick y-values
		_RJ.x_scale = 1; // base multiplier of right joystick x-values
		_RJ.y_scale = 1; // base multiplier of right joystick y-values

		_con.Left = &_LJ; // attach left joystick to controller object
		_con.Right = &_RJ; // attach right joystick to controller object
		Controller *c = &_con; // create pointer to controller

	// --- TESTS - testing functionalities ---
		// uncomment specific lines to test individual parts

		// Base  Tests
			//joystick_drive_test(LEFT_MOTOR, RIGHT_MOTOR);
			//tank_drive_test(LEFT_MOTOR, RIGHT_MOTOR);

		// Lightpole Servo Test
			//pole_test(POLE_SERVO);

		// Arm Movement Test
			//arm_test(port7);

		//Claw Test
			//claw_test(port8, port9);

		// Autonomous Test
			//auto_run(port2, port3, port7, port8, port9);

			//writeDebugStreamLine("testing done");

		// Calculation Tests
			//map_test();
			//motor_calc(0, 127);
			//motor_calc(0, -127);
			//motor_calc(127, 0);
			//motor_calc(-127, 0);
			//motor_calc(127 * sin(PI/4), 127 * cos(PI/4));
			//motor_calc(127 * sin(PI/4), -127 * cos(PI/4));
			//motor_calc(-127 * sin(PI/4), 127 * cos(PI/4));
			//motor_calc(-127 * sin(PI/4), -127 * cos(PI/4));
		//return;


	// main control loop
	while (true) {
	  update_controller(c); // continuously update controller value
		movement(c, LEFT_MOTOR, RIGHT_MOTOR); // base robot movement
		//drop_light_pole(c, POLE_SERVO); // control light pole
		move_claw(c, POLE_SERVO) // claw movement
		operate_arm(c, ARM_MOTOR); // operates the lift
		operate_claw(c, LEFT_CLAW_SERVO, RIGHT_CLAW_SERVO); // operates the claw
		autonomous(c, LEFT_MOTOR, RIGHT_MOTOR, ARM_MOTOR, LEFT_CLAW_SERVO, RIGHT_CLAW_SERVO); // runs continuous on button press

	}
}
