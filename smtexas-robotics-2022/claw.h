/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef SQUEAKY_MODE_H // include guard
#define squeaky_MODE_H


void squeaky_mode(Controller *c, int left_claw_port,  int right_claw_port, int front_left_port, int back_left_port, int front_right_port, int back_right_port) {
	////left side
	while(SensorValue[front_left_port] && c->btn5.up)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		//move claw forward
		motor[left_claw_port] = 10;
	}
	//Once the sensor is touched, the program will end and motors will stop.
	while(SensorValue[back_left_port] && c->btn5.down)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		//move claw backwards
		motor[right_claw_port] = -10;  //Set the rightMotor (motor6) to half power (50)
	}



	while(SensorValue[front_right_port] && c->btn6.up)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		motor[left_claw_port] = 10;
	}
	//Once the sensor is touched, the program will end and motors will stop.
	while(SensorValue[back_right_port] && c->btn6.down)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		motor[right_claw_port] = -10;  //Set the rightMotor (motor6) to half power (50)
	}
/*
	////right side
	while(switchFR && c->btn6.up)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		setMotorSpeed(right_claw_port, 10);  //Set the rightMotor (motor6) to half power (50)
	}
	//Once the sensor is touched, the program will end and motors will stop.
	while(switchFL && c->btn6.down)	// Loop while robot's bumper/touch sensor isn't pressed in
	{
		setMotorSpeed(right_claw_port, -10);  //Set the rightMotor (motor6) to half power (50)
	}
	*/
}

#endif // close guard
