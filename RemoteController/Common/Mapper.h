/**
 * @file Mapper.h
 * @author Jan Wielgus
 * @brief Class used to map values.
 * @date 2020-12-29
 * 
 */

#ifndef MAPPER_H
#define MAPPER_H


/**
 * @brief Class used to map values from input range to optput range.
 * @tparam T 
 */
template <class T>
class Mapper
{
    T inMin;
    T inMax;
    T outMin;
    T outMax;

public:
    Mapper(T inputMin, T inputMax, T outputMin, T outputMax)
    {
        setInputRange(inputMin, inputMax);
        setOutputRange(outputMin, outputMax);
    }

    void setInputRange(T inputMin, T inputMax)
    {
        inMin = inputMin;
        inMax = inputMax;
    }

    void setOutputRange(T outputMin, T outputMax)
    {
        outMin = outputMin;
        outMax = outputMax;
    }

    T map(T value)
    {
        // Formula from: https://www.arduino.cc/reference/en/language/functions/math/map/
        return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }
};


#endif
