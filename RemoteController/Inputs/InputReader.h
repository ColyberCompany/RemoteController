/**
 * @file InputReader.h
 * @author Jan Wielgus
 * @brief Basic class to read add input reading like
 * control sticks and left/right switches.
 * @date 2020-12-03
 * 
 */

#ifndef INPUTREADER_H
#define INPUTREADER_H

#include "Interfaces/IInputs.h"
#include <TaskPlanner.h>
#include <Task.h>
#include "ExtLibs/ADS1115.h"
#include "ControlStickFinalizer.h"


class InputReader : public Interfaces::IInputs, protected Task
{
private:
    TaskPlanner& taskPlanner;
    ADS1115 ads1115;

    uint16_t ADSMeasurements[4] = {};
    uint8_t currentADSPin = 0;

    ControlStickFinalizer throttle;
    ControlStickFinalizer pitch;
    ControlStickFinalizer roll;
    ControlStickFinalizer yaw;

    static const uint16_t ADSConversionTime_us = 1164; // 1000000 / RATE(860)


public:
    InputReader(TaskPlanner& taskPlanner);

    /**
     * @brief Call Wire.begin() before. Initialize everything.
     * @return true if everything went well, false otherwise.
     */
    bool initialize() override;
    ControlSticks readControlSticksValues() override;
    bool readLeftSwitch() override;
    bool readRightSwitch() override;

protected:
    /**
     * @brief Receive result from the last ADS reading
     * and trigger the next conversion.
     */
    void execute() override;

    /**
     * @brief Set multiplexer to the next pin
     * and triggers conversion on it.
     */
    void triggerNextADSConversion();
};


#endif

