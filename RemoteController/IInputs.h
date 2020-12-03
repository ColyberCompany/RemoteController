/**
 * @file IInputs.h
 * @author Jan Wielgus
 * @brief Interface for performing all input operations.
 * @date 2020-12-03
 * 
 */

#ifndef IINPUTS_H
#define IINPUTS_H

#include "ControlSticks.h"


namespace Interfaces
{
    class IInputs
    {
    public:
        virtual ~IInputs() {}

        virtual bool initialize() = 0;
        virtual ControlSticks readControlSticksValues() = 0;
        virtual bool readLeftSwitch() = 0;
        virtual bool readRightSwitch() = 0;
    };
}


#endif

