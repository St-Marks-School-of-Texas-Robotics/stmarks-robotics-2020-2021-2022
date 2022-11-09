#pragma config(Sensor, dgtl3,  CLAW_FR_SWITCH, sensorDigitalIn)
#pragma config(Sensor, dgtl5,  encoder,        sensorDigitalIn)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define RIGHT_CLAW_MOTOR port5


//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                        - Wait for Push 1 -                                         *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward at half speed until the bumper sensor is         *|
|*  pressed.  There is a two second pause at the beginning of the program.                            *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 2        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 3        leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital Port 6      touchSensor         VEX Bumper Switch     Front mounted, facing forward.    *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	while (true) {
		if (SensorValue[encoder] == 0)	{
			motor[RIGHT_CLAW_MOTOR] = -35;
		} else {
			motor[RIGHT_CLAW_MOTOR] = 0;
		}
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++