/**
 * @file ControlSticksADC.h
 * @author Jan Wielgus
 * @brief Adapter for control sticks values reading class.
 * @date 2021-01-02
 * 
 */

#ifndef CONTROLSTICKSADC_H
#define CONTROLSTICKSADC_H


namespace Interfaces
{
    class ControlSticksADC
    {
    public:
        virtual ~ControlSticksADC() {}

        virtual bool initialize() = 0;
        virtual uint16_t getThrottle() = 0;
        virtual int16_t getYaw() = 0;
        virtual int16_t getPitch() = 0;
        virtual int16_t getRoll() = 0;
    };
}


#endif
