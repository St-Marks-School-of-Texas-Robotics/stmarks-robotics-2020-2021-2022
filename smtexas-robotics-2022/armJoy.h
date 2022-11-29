/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef ARMJOY_H // include guard
#define ARMJOY_H


float armPos = 0; //default position
int armHigh = -100; //low position
int armLow = -15; //high position
// control motor to drop light pole
void arm_joy(Controller *c, int arm_port1) {
		if (vexRT[Ch2] >= 45) {
  			armPos -= .02;	// move up
  	} else if (vexRT[Ch2] <= -45) {
  			armPos += .02;	// move down
  	}

  	if (armPos < armHigh){
  		armPos = armHigh;
  	} else if (armPos > armLow){
  		armPos = armLow;
  	}

  	motor[arm_port1] = armPos;

}


#endif // close guard
