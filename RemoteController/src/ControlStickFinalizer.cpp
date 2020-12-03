/**
 * @file ControlStickFinalizer.cpp
 * @author Jan Wielgus
 * @date 2020-12-03
 * 
 */

#include "Inputs/ControlStickFinalizer.h"


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
	if (outputVal > calib.rawCenterValue + outputProperties.deadZone)
	{
		outputVal = map(outputVal,
			calib.rawCenterValue + outputProperties.deadZone,	calib.rawMaxValue,
			outputProperties.finalCenterValue,					outputProperties.finalMaxValue	);

		outputVal = constrain(outputVal, outputProperties.finalCenterValue, outputProperties.finalMaxValue);
	}
	else if (outputVal < calib.rawCenterValue - outputProperties.deadZone)
	{
		outputVal = map(outputVal,
			calib.rawMinValue,				calib.rawCenterValue - outputProperties.deadZone,
			outputProperties.finalMinValue,	outputProperties.finalCenterValue					);

		outputVal = constrain(outputVal, outputProperties.finalMinValue, outputProperties.finalCenterValue);
	}
	else
		outputVal = outputProperties.finalCenterValue;

    return outputVal;
}

