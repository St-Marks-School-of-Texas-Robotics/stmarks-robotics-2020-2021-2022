#pragma config(Motor,  port2,           servo1,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           servo2,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           servo3,        tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//servo position values

int servo1Close = 0;
int servo1Middle = 0;
int servo1Far = 0;

int servo2Close = 0;
int servo2Middle = 0;
int servo2Far = 0;

int servo3Close = 0;
int servo3Middle = 0;
int servo3Far = 0;

task main()
{
	while (true) {


		if (vexRT[Btn6D] == 1) {
			motor[servo1] = servo1Far; // Servo 1 Far position - Lift Down

		} else if (vexRT[Btn6U] == 1) {
			motor[servo1] = servo1Close; // Servo 1 Close position - Lift Up

		} else {
			motor[servo1] = servo1Middle; // Servo 1 Middle position - Lift Stop
		}


		if (vexRT[Ch3] > 25) {
			motor[servo2] = servo2Far; // Servo 2 Far position - Drive Forward

		} else if (vexRT[Ch3] < -25) {
			motor[servo2] = servo2Close; // Servo 2 Close position - Drive Backwards

		} else {
			motor[servo2] = servo2Middle; // Servo 2 Middle position - Drive Stop
		}


		if (vexRT[Ch1] > 25) {
			motor[servo3] = servo3Far; // Servo 3 Far position - Rotate Right

		} else if (vexRT[Ch1] < -25) {
			motor[servo3] = servo3Close; // Servo 3 Close position - Rotate Left

		} else {
			motor[servo3] = servo3Middle; // Servo 3 Middle position - Rotate Stop
		}





	} //while end



} //main end
