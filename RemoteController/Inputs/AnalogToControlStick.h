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

#include "../Common/Mapper.h"

// TODO: refactor this class


/**
 * @brief This class is used to convert raw analog input readings
 * to control stick values (change range with option to set center value and offset).
 */
class AnalogToControlStick
{
    Mapper<int16_t> leftMapper; // Maps values between min and center
    Mapper<int16_t> rightMapper; // Maps values between center and max
    //uint16_t inMid;
    //uint16_t inMidOffset;
    int16_t outMid;

public:
    /**
     * @brief Initiallize the stick object.
     * @param inMin Raw input minimum value (can be higher than inMax).
     * @param inMid Raw input center value
     * (have to be between inMin and inMax, could be equal).
     * @param inMax Raw input maximum value (can be less than inMin).
     * @param inMidOffset Raw offset value (distance from inMid when output value remain outMid).
     * @param outMin Output minimum value (outMin < outMax).
     * @param outMid Output center value
     * (have to be between outMin and outMax, could be equal).
     * @param outMax Output maximum value (outMax > outMin).
     */
    AnalogToControlStick(uint16_t inMin, uint16_t inMid, uint16_t inMax, uint16_t inMidOffset,
        int16_t outMin, int16_t outMid, int16_t outMax)
    {
        setAnalogInputProperties(inMin, inMid, inMax, inMidOffset);
        setOutputProperties(outMin, outMid, outMax);
    }


    // TODO: refactor this method
    void setAnalogInputProperties(uint16_t inMin, uint16_t inMid, uint16_t inMax, uint16_t inMidOffset)
    {
        if (inMin <= inMax)
        {
            // If mid is not in <min:max> range
            if (inMid < inMin || inMid > inMax)
                return;

            leftMapper.setInputRange(inMin, inMid - inMidOffset);
            rightMapper.setInputRange(inMid + inMidOffset, inMax);
        }
        else // inverted range
        {
            // If mid is not in <min:max> range
            if (inMid < inMax || inMid > inMin)
                return;

            leftMapper.setInputRange(inMin, inMid + inMidOffset);
            rightMapper.setInputRange(inMid - inMidOffset, inMax);
        }
    }


    int16_t convert(uint16_t rawAnalog)
    {
        if (leftMapper.getInputMin() < rightMapper.getInputMax())
        {
            if (rawAnalog <= leftMapper.getInputMax())
                return leftMapper.map(rawAnalog);
            else if (rawAnalog >= rightMapper.getInputMin())
                return rightMapper.map(rawAnalog);
            else
                return outMid;
        }
        else // Inverted
        {
            if (rawAnalog >= leftMapper.getInputMax())
                return leftMapper.map(rawAnalog);
            else if (rawAnalog <= rightMapper.getInputMin())
                return rightMapper.map(rawAnalog);
            else
                return outMid;
        }
    }



private:
    void setOutputProperties(int16_t outMin, int16_t outMid, int16_t outMax)
    {
        if (outMax < outMin)
        {
            // Swap
            int16_t temp = outMin;
            outMin = outMax;
            outMax = temp;
        }

        // Check if mid is out of <min:max> range
        if (outMid < outMin)
            outMid = outMin;
        else if (outMid > outMax)
            outMid = outMax;

        leftMapper.setOutputRange(outMin, outMid);
        rightMapper.setOutputRange(outMid, outMax);

        this->outMid = outMid;
    }
};


#endif
