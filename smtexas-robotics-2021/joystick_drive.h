#ifndef JOYSTICK_DRIVE_H // include guard
#define JOYSTICK_DRIVE_H

// void loop(Controller *c);
// void __update_controller(Controller *c);

// void init(Controller *c);

void drive_control(Controller *c, int lport, int rport) {
	Joystick *j = c->Left; // joystick

	// general movement scaling
  int x = j->x_axis * j->x_scale; // x value of movement [-127, 127]
  int y = j->y_axis * j->y_scale; // y value of movement [-127, 127]

  // calculate the base (unscaled) values for the forward motor outputs
  float left_motor_base, right_motor_base; // right motor base power, left motor base power

  // motor directions (assuming 127, 127 top right)
  // motor values [-100, 100]
  // if fowards

  float mag = sqrt(x * x + y * y); // magnitude of the vector
  float bearing = x < 0 | y < 0 ? radiansToDegrees(atan(y/x)) + 180: radiansToDegrees(atan(y/x)); // direction of joystick relative to origin in degrees

  if (y >= 0) {
  		// assuming right = x positive
      left_motor_base = mag * cos(bearing - 45); // max value if x is positive, else
      right_motor_base = mag * sin(bearing - 45);

  } else {
    // scale the motor outputs (throttle)
    left_motor_base *= y / 128.0;
    right_motor_base *= y / 128.0;

    // calculate the pivot (0 if no scale, > 0 if should scale)
    float piv_scale = abs(y) > __PivThreshold ? 0.0 : 1.0-abs(y)/__PivThreshold;

    // apply the pivot to calculate the final forward motor outputs
    float motorlf_out = (1 - piv_scale) * motorlf_base + piv_scale * x;
    float motorrf_out = (1 - piv_scale) * motorrf_base + piv_scale * -x;

    motor[lport] = (int)(motorlf_out * lscale);
    motor[rport] = (int)(motorrf_out * rscale);
	}
}

// arduino equivalent mapping
// returns proportional equivalent of x in a to b for f to g
float map(float x, float a, float b, float f, float g) {
	return (f - g) * (x - a) / (b - a) + f;
}


#endif
