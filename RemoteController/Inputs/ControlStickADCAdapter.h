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

        switch (measurementType)
        {
        case MeasurementType::ThrottleStick:
            return sticksADC.getThrottle();
        case MeasurementType::YawStick:
            return sticksADC.getYaw();
        case MeasurementType::PitchStick:
            return sticksADC.getPitch();
        case MeasurementType::RollStick:
            return sticksADC.getRoll();
        default:
            return 0; // ERROR, this should never occure
        }
    }

    void setAnalogInputProperties(uint16_t inMin, uint16_t inMid, uint16_t inMax, uint16_t inMidOffset)
    {
        valueConverter.setAnalogInputProperties(inMin, inMid, inMax, inMidOffset);
    }
};


#endif
