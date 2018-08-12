/*
 * MathUtil.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef MATH_MATHUTIL_H_
#define MATH_MATHUTIL_H_

#include <string>
using namespace std;

class MathUtil {
public:

	static float map(long value, short int in_min,
			short int in_max, float out_min, float out_max)	{
	  return (float)(value - in_min) * (out_max - out_min) /
			  (in_max - in_min) + out_min;
	}

	static float map(short int value, short int in_min,
			short int in_max, short int out_min, short int out_max)	{
	  return (float)(value - in_min) * (out_max - out_min) /
			  (in_max - in_min) + out_min;
	}

	static float mapRange(short int value, short int in_min,
			short int in_max, short int out_min, short int out_max)	{
		short int val = value;
		if(val<in_min)
			val = in_min;
		if(val>in_max)
			val = in_max;

		return (float)(val - in_min) * (out_max - out_min) /
			  (in_max - in_min) + out_min;
	}

	float binaryToVoltage(short int value, float VREF){
		return (float)(VREF * value)/1023;
	}

	short int voltageToBinary(float value, float VREF){
		return (value * 1023)/VREF;
	}

	float stringToFloat(const char* str){
		return std::atof(str);
	}

};

#endif /* MATH_MATHUTIL_H_ */
