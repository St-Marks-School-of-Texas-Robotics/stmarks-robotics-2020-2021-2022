/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef ARMJOY_H // include guard
#define ARMJOY_H


int armPos = 0; //default position
int armHigh = 0; //low position
int armLow = 0; //high position
// control motor to drop light pole
void arm_joy(Controller *c, int arm_port1) {
		if (vexRT[Ch2] >= 15) {
  			armPos ++;	// move up
  	} else if (vexRT[Ch2] <= -15) {
  			armPos --;	// move down
  	}

  	if (armPos > armHigh){
  		armPos = armHigh;
  	} else if (armPos < armLow){
  		armPos = armLow;
  	}

  	motor[arm_port1] = armPos;

}


#endif // close guard
