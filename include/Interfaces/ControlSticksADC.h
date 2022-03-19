/**
 * @file ControlSticksADC.h
 * @author Jan Wielgus
 * @brief Adapter for control sticks values reading class.
 * @date 2021-01-02
 * 
 */

#ifndef CONTROLSTICKSADC_H
#define CONTROLSTICKSADC_H

#ifdef ARDUINO
    #include <Arduino.h>
#endif


namespace Interfaces
{
    class ControlSticksADC
    {
    public:
        virtual ~ControlSticksADC() {}

        virtual bool initialize() = 0;
        virtual uint16_t getRawThrottle() = 0;
        virtual int16_t getRawYaw() = 0;
        virtual int16_t getRawPitch() = 0;
        virtual int16_t getRawRoll() = 0;
    };
}


#endif
