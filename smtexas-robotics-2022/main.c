#pragma config(UART_Usage, UART1, uartUserControl, baudRate1200, IOPins, None, None)
#pragma config(Sensor, dgtl10,  CLAW_FL_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl8,  CLAW_BL_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl9,  CLAW_FR_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl7,  CLAW_BR_SWITCH, sensorDigitalIn)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//2022
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* main.c
Main Code for Demolition 2022 BEST Robotics
St. Mark's Robotics Team
for help, consult c_help.txt and setup_help.txt
or contact Isaac Song at isaacsong03@gmail.com
*/

// INCLUDES
#include "helper.h" // helper functions
#include "controller.h" // controller object
#include "joystick_drive.h" // joystick driving functions


#include "squeaky.h" // squeaky mode

#include "hinge.h" // hinge for box
#include "battery.h" // battery dropper
#include "arm.h" // battery dropper

#include "test_dualdrive.h" // 2 joystick drive

#include "ir_baud.h" // ir uart

#include "armJoy.h" // battery dropper

#include "drive_selector.h" // selects regular vs squeaky

#include "retract.h" //retract squeaky claws



// PORTS ASSIGNMENTS
#define LEFT_MOTOR port2
#define RIGHT_MOTOR port6 //6
#define LEFT_CLAW_MOTOR port4
#define RIGHT_CLAW_MOTOR port8 //8
#define HINGE_SERVO port3  //3
#define WHEEL_SERVO1 port7 //left
#define WHEEL_SERVO2 port5 //right //5
#define ARM_SERVO1 port9





/*
#define ARM_MOTOR port7
#define LEFT_CLAW_SERVO port8
#define RIGHT_CLAW_SERVO port9
*/


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
	if (c->btn5.up) {
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

	//dirve selector function
	drive_mode(c, LEFT_MOTOR, RIGHT_MOTOR, LEFT_CLAW_MOTOR, RIGHT_CLAW_MOTOR, CLAW_FL_SWITCH, CLAW_BL_SWITCH, CLAW_FR_SWITCH, CLAW_BR_SWITCH, ARM_SERVO1);

	//joystick_drive_control(c, left_port, right_port);

	//joystick_squeaky_control(c, LEFT_CLAW_MOTOR, RIGHT_CLAW_MOTOR, CLAW_FL_SWITCH, CLAW_BL_SWITCH, CLAW_FR_SWITCH, CLAW_BR_SWITCH);

	//dual_drive_control(c, left_port, right_port);


}

// main function
task main(){
	//ir init
	setBaud(UART1, 600);

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
			//hinge_test(HINGE_SERVO);

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
		close_hinge(c, HINGE_SERVO); // control light pole
		drop_battery(c, WHEEL_SERVO1, WHEEL_SERVO2); // control light pole
		//  drop_arm(c, ARM_SERVO1, ARM_SERVO2); // control light pole

		 retract_claw(c , LEFT_CLAW_MOTOR, RIGHT_CLAW_MOTOR);


		//move_claw(c, LEFT_CLAW_MOTOR, RIGHT_CLAW_MOTOR, CLAW_FL_SWITCH, CLAW_BL_SWITCH, CLAW_FR_SWITCH, CLAW_BR_SWITCH); // claw movement
		//operate_arm(c, ARM_MOTOR); // operates the lift
		//operate_claw(c, LEFT_CLAW_SERVO, RIGHT_CLAW_SERVO); // operates the claw
		//autonomous(c, LEFT_MOTOR, RIGHT_MOTOR, ARM_MOTOR, LEFT_CLAW_SERVO, RIGHT_CLAW_SERVO); // runs continuous on button press

	}

}
