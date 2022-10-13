/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef CLAW_H // include guard
#define CLAW_H

int switchFL = getBumperValue(bumpSwitch);
int switchBL = getBumperValue(bumpSwitch);// hole 0 is no hole

int switchFR = getBumperValue(bumpSwitch);
int switchBR = getBumperValue(bumpSwitch);

void move_claw(Controller *c, int pole_port) {
	////left side
	while(switchFL && c->btn5.up)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		setMotorSpeed(left_claw_motor, 10);  //Set the rightMotor (motor6) to half power (50)
	}
	//Once the sensor is touched, the program will end and motors will stop.
	while(switchFR && c->btn5.down)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		setMotorSpeed(left_claw_motor, -10);  //Set the rightMotor (motor6) to half power (50)
	}

	////right side
	while(switchFR && c->btn6.up)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		setMotorSpeed(right_claw_motor, 10);  //Set the rightMotor (motor6) to half power (50)
	}
	//Once the sensor is touched, the program will end and motors will stop.
	while(switchFL && c->btn6.down)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		setMotorSpeed(right_claw_motor, -10);  //Set the rightMotor (motor6) to half power (50)
	}
}

#endif // close guard
