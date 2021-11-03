#ifndef LIFT_H // include guard
#define LIFT_H


// CONSTANTS
#define ARM_DEFAULT_POWER 0 // default power for arm
#define ARM_UP_POWER 127 // default power for arm upwards
#define ARM_DOWN_POWER 63 // default power for arm downwards
#define ARM_DEFAULT_MULT 1 // default multiplier for arm control
#define ARM_PREC_MULT 0.3 // multiplier for precise arm control

#define CLAW_OPEN 100 // claw position for open claw
#define CLAW_CLOSE 0 // claw position for closed claw

// control motor to lift the claw
void operate_arm(Controller *c, int arm_port) {
	// [button] to go up, [button] to go down
	//
	// PARAMS
	// 		Controller *c: Controller object to retrieve input values
	//		int arm_port: port number of motor to lift claw

	float arm_mult; // multiplier for arm power

	// turn on arm precision control when button pressed
	// 		right button group left button
	if (c->btn8.left) {
		arm_mult = ARM_PREC_MULT; // set multiplier to precise
	} else {
		arm_mult = ARM_DEFAULT_MULT; // reset multiplier to default
	}

	// lift claw when left top bumper pressed
	// 		group 5 up button
	if (c->btn5.up) {
		motor[arm_port] = ARM_UP_POWER * arm_mult; // motor power upwards

	// lower claw when left bottom bumper pressed
	// 		group 5 down button
	} else if (c->btn5.down) {
		motor[arm_port] = -ARM_DOWN_POWER * arm_mult; // motor power downwards

	// passive motor power
	} else {
		motor[arm_port] = ARM_DEFAULT_POWER * arm_mult; // motor at default power
	}
}

// control motor to open/close the claw
void operate_claw(Controller *c, int left_claw_port, int right_claw_port) {
    // open/closes claw
    // right top bumper to close claw
    // right bottom bumper to open claw
    //
    // PARAMS
    //        Controller *c: Controller object to retrieve input values
    //        int left_claw_port: left claw servo port number
		//        int right_claw_port: right claw servo port number


    // close the claw if top bottom right bumper is pressed
    //        button group 6 up  button
    if (c->btn6.up) {
        motor[left_claw_port] = CLAW_CLOSE; // close the claw
        motor[right_claw_port] = -CLAW_CLOSE; // open the claw, negative value of left claw

    // open the claw if bottom right bumper is pressed
    //        button group 6 down button
    } else if (c->btn6.down) {
        motor[left_claw_port] = CLAW_OPEN; // open the claw
        motor[right_claw_port] = -CLAW_OPEN; // close the claw, negative value of left claw
    }
}

// test arm functionallity
void arm_test(int arm_port) {
	// test arm movement
	// PARAMS
	//		int lift_port: port number of lifting motor
 //---------------------------------------------------------------------------------------------------

	writeDebugStreamLine("arm test start");

	writeDebugStreamLine("arm up");
	motor[arm_port] = 127;
	wait1Msec(1000);

	writeDebugStreamLine("arm stay");
	motor[arm_port] = 0;
	wait1Msec(5000);

	writeDebugStreamLine("arm down");
	motor[arm_port] = -63;
	wait1Msec(500);

	writeDebugStreamLine("arm test done");
}

// test claw functionallity
void claw_test(int left_claw_port, int right_claw_port) {
    // open close claw
    // PARAMS
    //        int claw_port: port number of claw motor

    writeDebugStreamLine("claw test start");

    writeDebugStreamLine("claw close");
    motor[left_claw_port] = 127;
    motor[right_claw_port] = -127;
    wait1Msec(3000);

    writeDebugStreamLine("claw open");
    motor[left_claw_port] = 0;
    motor[right_claw_port] = 0;
    wait1Msec(3000);

    writeDebugStreamLine("claw test done");
}

#endif
