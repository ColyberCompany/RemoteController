/**
 * @file ControlStickFinalizer.h
 * @author Jan Wielgus
 * @brief Class that from raw ananlog value of a control stick makes
 * output value in the set range and other properties.
 * @date 2020-12-03
 * 
 */

#ifndef CONTROLSTICKFINALIZER_H
#define CONTROLSTICKFINALIZER_H

#include "EVAFilter.h"


class ControlStickFinalizer
{
private:
    struct
	{
		uint16_t min;
		uint16_t center;
		uint16_t max;
	} raw;
	
	struct
	{
		int16_t min;
		int16_t center;
		int16_t max;
		uint16_t deadZone;
	} output;

    EVAFilter filter;


public:
    ControlStickFinalizer();

    /**
     * @brief Set all the proterties.
     * @param rawMin Minimum raw input reading.
     * @param rawCenter Raw reading in center.
     * @param rawMax Maximum raw input reading.
     * @param finalMin Output value for rawMin reading.
     * @param finalCen Output value when input is rawCenter.
     * @param finalMax Output value for rawMax reading.
     * @param deadZone Raw distance from center when
     * output value remain finalCen
     */
    void setProperties(
        uint16_t rawMin, uint16_t rawCenter, uint16_t rawMax,
        int16_t finalMin, int16_t finalCen, int16_t finalMax,
        uint16_t deadZone = 0);

    int16_t update(uint16_t rawReading);
};


#endif

