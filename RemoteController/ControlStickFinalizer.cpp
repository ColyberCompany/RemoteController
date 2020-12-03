/**
 * @file ControlStickFinalizer.cpp
 * @author Jan Wielgus
 * @date 2020-12-03
 * 
 */

#include "ControlStickFinalizer.h"


ControlStickFinalizer::ControlStickFinalizer()
    : filter(0.3f)
{
}


void ControlStickFinalizer::setProperties(uint16_t rawMin, uint16_t rawCenter, uint16_t rawMax,
        int16_t finalMin, int16_t finalCen, int16_t finalMax,
        uint16_t deadZone)
{
    raw.min = rawMin;
    raw.center = rawCenter;
    raw.max = rawMax;
    output.min = finalMin;
    output.center = finalCen;
    output.max = finalMax;
    output.deadZone = deadZone;
}


int16_t ControlStickFinalizer::update(uint16_t rawReading)
{
    int16_t outputVal;

    outputVal = filter.update(rawReading);

    // TODO: if when values should be reversed this approach don't work,
    // just reverse values there

    // calculate the output values
	if (outputVal > raw.center + output.deadZone)
	{
		outputVal = map(outputVal,
			raw.center + output.deadZone, raw.max,
			output.center, output.max);

		outputVal = constrain(outputVal, output.center, output.max);
	}
	else if (outputVal < raw.center - output.deadZone)
	{
		outputVal = map(outputVal,
			raw.min, raw.center - output.deadZone,
			output.min,	output.center);

		outputVal = constrain(outputVal, output.min, output.center);
	}
	else
		outputVal = output.center;

    return outputVal;
}

