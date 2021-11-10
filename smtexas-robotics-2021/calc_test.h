/* calc_test.h
Testing calculations and logic
Non-Generic Code
*/

#ifndef CALC_TEST_H // include guard
#define CALC_TEST_H

void map_test() {
	writeDebugStreamLine("map(-3, -10, 10, -10, 10): %f", map(-3, -10, 10, -10, 10));
	writeDebugStreamLine("map(-0.000006, -127, 127, -127, 127): %f", map(-0.000006, -127, 127, -127, 127));
	writeDebugStreamLine("abs(-0.000006): %f", abs(-0.000006));
	writeDebugStreamLine("");
}


void motor_calc(float x, float y) {
	writeDebugStreamLine("(%f, %f)", x, y);
	float mag = sqrt(x * x + y * y); // magnitude of the vector
	writeDebugStreamLine("mag: %d", mag);

	// writeDebugStreamLine("mag: %d", mag);
  float bearing = atan2(y, x); // direction of joystick relative to origin in degrees
	bearing -= PI / 4; // offset bearing by pi / 4 radians
	writeDebugStreamLine("bearing: %f", radiansToDegrees(bearing));


  // offset vector by pi/4 degrees
  float left_motor_base = mag * cos(bearing);
  float right_motor_base = mag * sin(bearing);
	writeDebugStreamLine("Base1: (%f, %f)", left_motor_base, right_motor_base);

  // if 0, make value very very close to 0 but not 0 to prevent division by 0
  left_motor_base = left_motor_base < 0 ? min(left_motor_base, -.000001) :
  																	 			max(left_motor_base, .000001);

  right_motor_base = right_motor_base < 0 ? min(right_motor_base, -.000001) :
  																	 			max(right_motor_base, .000001);

	writeDebugStreamLine("Base2: (%f, %f)", left_motor_base, right_motor_base);
  float left_motor_mapped = map(left_motor_base,
																JOYSTICK_MIN * abs(cos(bearing)),
																JOYSTICK_MAX * abs(cos(bearing)),
																MOTOR_MIN,
																MOTOR_MAX);

	float right_motor_mapped = map(right_motor_base,
															 	 JOYSTICK_MIN * abs(sin(bearing)),
																 JOYSTICK_MAX * abs(sin(bearing)),
																 MOTOR_MIN,
																 MOTOR_MAX);
	writeDebugStreamLine("Mapped: (%f, %f)", left_motor_mapped, right_motor_mapped);

  float mult = min(abs(left_motor_mapped / left_motor_base), abs(right_motor_mapped / right_motor_base));

  // map motors from angled proportion to to max motor proportion
  float left_motor_final = left_motor_base * mult;
	float right_motor_final = right_motor_base * mult;

  writeDebugStreamLine("map(%f, -127, 127, -127, 127): %f", left_motor_base, left_motor_final);
  writeDebugStreamLine("map(%f, -127, 127, -127, 127): %f", right_motor_base, right_motor_final);
  writeDebugStreamLine("");
}


#endif // close guard
