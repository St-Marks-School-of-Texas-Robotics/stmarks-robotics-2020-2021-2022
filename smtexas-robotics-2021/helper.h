/* helper.h
Common helper functions for calculations
Generic Code
*/

#ifndef HELPER_H // include guard
#define HELPER_H

// min function
// calculate smallest value between a and b
float min(float a, float b) {
	// returns smaller of a and b
	//
	// PARAMS
	//		 float a: value of a
  //		 float b: value of b

	return a < b ? a : b;
}

// max function
// calculate larger value between a and b
float max(float a, float b) {
	// returns larger of a and b
	//
	// PARAMS
	//		 float a: value of a
  //		 float b: value of b

	return a > b ? a : b;
}

// returns proportional equivalent of x in a to b for f to g
float map(float i, float i_min, float i_max, float f_min, float f_max) {
	// returns value from one range to another range
	//
	// PARAMS
	//		i: initial value to map
	// 	 	i_min: min for initial range
	// 		i_max: max for initial range
	// 		f_min: min for final range
	// 		f_max: max for final range

	// Corner Case: avoid dividing by 0
	if (i_max == i_min) {
		return i_max
	}

	// formula for ratio
	return ((i - i_min) * (f_max - f_min) / (i_max - i_min)) + f_min
}

#endif // close guard
