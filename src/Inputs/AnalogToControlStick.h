/**
 * @file AnalogToControlStick.h
 * @author Jan Wielgus
 * @brief Class used to convert raw analog reading to final stick output value.
 * Input and output range and center point can be set.
 * @date 2020-12-29
 * 
 */

#ifndef ANALOGTOCONTROLSTICK_H
#define ANALOGTOCONTROLSTICK_H

#include "Common/Mapper.h"
#include "utils.h"

// TODO: refactor this class


/**
 * @brief This class is used to convert raw analog input readings
 * to control stick values (change range with option to set center value and offset).
 */
class AnalogToControlStick
{
    Mapper<int16_t> leftMapper; // Maps values between min and center
    Mapper<int16_t> rightMapper; // Maps values between center and max
    int16_t outMid;
    bool invertedOutputRangeFlag = false;

public:
    /**
     * @brief Initiallize the stick object.
     * @param inMin Raw input minimum value (can be higher than inMax).
     * @param inMid Raw input center value
     * (have to be between inMin and inMax, could be equal).
     * @param inMax Raw input maximum value (can be less than inMin).
     * @param inMidOffset Raw offset value (distance from inMid when output value remain outMid).
     * @param outMin Output minimum value.
     * @param outMid Output center value
     * (have to be between outMin and outMax, could be equal).
     * @param outMax Output maximum value.
     */
    AnalogToControlStick(uint16_t inMin, uint16_t inMid, uint16_t inMax, uint16_t inMidOffset,
        int16_t outMin, int16_t outMid, int16_t outMax)
    {
        setAnalogInputProperties(inMin, inMid, inMax, inMidOffset);
        setOutputProperties(outMin, outMid, outMax);
    }


    void setAnalogInputProperties(uint16_t inMin, uint16_t inMid, uint16_t inMax, uint16_t inMidOffset)
    {
        if (inMin > inMax)
        {
            Utils::swap(inMin, inMax);

            // Assure mid is in <min:max> range
            if (inMid < inMin)
                inMid = inMin;
            else if (inMid > inMax)
                inMid = inMax;

            if (invertedOutputRangeFlag == false) // if output range wasn't inverted before
                invertMappersOutputRange();

            invertedOutputRangeFlag = true;
        }

        leftMapper.setInputRange(inMin, inMid - inMidOffset);
        rightMapper.setInputRange(inMid + inMidOffset, inMax);
    }


    int16_t convert(uint16_t rawAnalog)
    {
        int16_t output;

        if (rawAnalog <= leftMapper.getInputMax())
            output = leftMapper.map(rawAnalog);
        else if (rawAnalog >= rightMapper.getInputMin())
            output = rightMapper.map(rawAnalog);
        else
            return outMid;

        return getConstrainedOutput(output);
    }



private:
    void setOutputProperties(int16_t outMin, int16_t outMid, int16_t outMax)
    {
        leftMapper.setOutputRange(outMin, outMid);
        rightMapper.setOutputRange(outMid, outMax);

        if (invertedOutputRangeFlag)
            invertMappersOutputRange();

        this->outMid = outMid;
    }


    void invertMappersOutputRange()
    {
        Mapper<int16_t> oldLeftMapper = leftMapper;
        leftMapper.setOutputRange(rightMapper.getOutputMax(), rightMapper.getOutputMin());
        rightMapper.setOutputRange(oldLeftMapper.getOutputMax(), oldLeftMapper.getOutputMin());
    }


    int16_t getConstrainedOutput(int16_t value)
    {
        int16_t outMin = leftMapper.getOutputMin();
        int16_t outMax = rightMapper.getOutputMax();

        if (invertedOutputRangeFlag)
            Utils::swap(outMin, outMax);

        return constrain(value, outMin, outMax);
    }
};


#endif
