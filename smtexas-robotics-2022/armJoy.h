/* lightpole.h
code for lightpole dropper, specific to 2021 BEST game
Non-Generic Code
*/

#ifndef ARMJOY_H // include guard
#define ARMJOY_H


float armPos = 140; //default position
int armHigh = -65; //low position
int armLow = 140; //high position
float slowMulti = 1;

bool once = true;

// control motor to drop light pole
void arm_joy(Controller *c, int arm_port1) {

	if (c->btn5.up) {
		slowMulti = 0.5;
	} else {
		slowMulti = 1;
	}

	if(c->btn8.right && once) { //box grabber pressed
		armPos = 20; 
		once = false;
	}



	if (vexRT[Ch2] >= 45) {
  			armPos -= .1 * slowMulti;	// move up
  	} else if (vexRT[Ch2] <= -45) {
  			armPos += .1 * slowMulti;	// move down
  	}

  	if (armPos < armHigh){
  		armPos = armHigh;
  	} else if (armPos > armLow){
  		armPos = armLow;
  	}

  	motor[arm_port1] = armPos;

}


#endif // close guard
