/**
 * @file PinAdapter.h
 * @author Jan Wielgus
 * @brief Class used to add single analog pin as Measurement to the MeasurementsManager.
 * @date 2021-01-02
 * 
 */

#ifndef PINADAPTER_H
#define PINADAPTER_H

#include "Measurement.h"


class PinAdapter : public Measurement
{
protected:
    uint8_t pin;

public:
    PinAdapter(Enums::MeasurementType measurementType, uint8_t pin)
        : Measurement(measurementType)
    {
        this->pin = pin;
    }
};



class AnalogPinAdapter : public PinAdapter
{
public:
    AnalogPinAdapter(Enums::MeasurementType measurementType, uint8_t analogPin)
        : PinAdapter(measurementType, analogPin)
    {}

    float getNewValue() override
    {
        return analogRead(pin);
    }
};



class DigitalPinAdapter : public PinAdapter
{
public:
    DigitalPinAdapter(Enums::MeasurementType measurementType, uint8_t digitalPin)
        : PinAdapter(measurementType, digitalPin)
    {}

    /**
     * @brief Have to be called before the first reading.
     * @param mode INPUT or INPUT_PULLUP
     */
    void initializePin(uint8_t mode)
    {
        pinMode(pin, mode);
    }

    float getNewValue() override
    {
        return (float)digitalRead(pin);
    }
};


#endif
