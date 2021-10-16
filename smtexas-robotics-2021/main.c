// includes
#include "controller.h"
#include "joystick_drive.h" //joystick driving functions

void loop(Controller *c) {
	drive_control(c, port2, port3);
}

task main(){
	// controller initialization
  Controller _con;

  Joystick _LJ, _RJ;
  _LJ.x_scale = 1;
  _LJ.y_scale = 1;
  _RJ.x_scale = 1;
  _RJ.y_scale = 1;

  _con.Left = &_LJ;
  _con.Right = &_RJ;
  Controller *c = &_con;

  // user initialization
  // init(c);

  // main control loop
  while (true) {
      __update_controller(c); // continuously update controller value

      loop(c);
  }
}
