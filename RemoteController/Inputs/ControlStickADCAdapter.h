/**
 * @file ControlStickADCAdapter.h
 * @author Jan Wielgus
 * @brief Adapter that enable to add one stick to MeasurementsManager
 * @date 2021-01-02
 * 
 */

#ifndef CONTROLSTICKADCADAPTER_H
#define CONTROLSTICKADCADAPTER_H

#include "Measurement.h"
#include "AnalogToControlStick.h"
#include "../Interfaces/ControlSticksADC.h"
#include "../Enums/MeasurementType.h"

class ControlStickADCAdapter : public Measurement
{
    Interfaces::ControlSticksADC& sticksADC;
    AnalogToControlStick valueConverter;

public:
    /**
     * @brief Ctor.
     * @param stickType Which control stick it will be.
     * Be sure to pass only stick types.
     * @param controlSticksADC Reference to control sticks ADC instance.
     * @param _valueConverter AnalogToControlStick object to initialize this class.
     */
    ControlStickADCAdapter(Enums::MeasurementType stickType, Interfaces::ControlSticksADC& controlSticksADC, const AnalogToControlStick& _valueConverter)
        : Measurement(stickType), sticksADC(controlSticksADC), valueConverter(_valueConverter)
    {
    }

    float getNewValue() override
    {
        using Enums::MeasurementType;
        float newRawValue;

        switch (measurementType)
        {
        case MeasurementType::ThrottleStick:
            newRawValue = sticksADC.getRawThrottle();
            break;
        case MeasurementType::YawStick:
            newRawValue = sticksADC.getRawYaw();
            break;
        case MeasurementType::PitchStick:
            newRawValue = sticksADC.getRawPitch();
            break;
        case MeasurementType::RollStick:
            newRawValue = sticksADC.getRawRoll();
            break;
        default:
            return -2.2f; // ERROR, this should never occure
        }

        return valueConverter.convert(newRawValue);
    }

    void setAnalogInputProperties(uint16_t inMin, uint16_t inMid, uint16_t inMax, uint16_t inMidOffset)
    {
        valueConverter.setAnalogInputProperties(inMin, inMid, inMax, inMidOffset);
    }
};


#endif
