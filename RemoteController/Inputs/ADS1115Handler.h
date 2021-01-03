/**
 * @file ADS1115Handler.h
 * @author Jan Wielgus
 * @brief Class that use ADS1115 to read control sticks values.
 * @date 2021-01-02
 * 
 */

#ifndef ADS1115HANDLER_H
#define ADS1115HANDLER_H

#include "../Interfaces/ControlSticksADC.h"
#include <Task.h>
#include <TaskPlanner.h>
#include <ADS1115.h>


class ADS1115Handler : public Interfaces::ControlSticksADC, public Task
{
    TaskPlanner& taskPlanner;
    ADS1115 ads1115;

    uint16_t adsMeasurements[4] = {};
    uint8_t currentADSPin = 0;

    static const uint16_t ADSConversionTime_us = 1164; // 1000000 / RATE   (for RATE = 860)

public:
    ADS1115Handler(TaskPlanner& taskPlanner);

    /**
     * @brief Call Wire.begin() outside. Initializes ads1115.
     * @return true if everything went well, false otherwise.
     */
    bool initialize() override;
    uint16_t getRawThrottle() override;
    int16_t getRawYaw() override;
    int16_t getRawPitch() override;
    int16_t getRawRoll() override;


private:
    /**
     * @brief Receive result from the last ADS reading
     * and triggers conversion on the the next pin.
     */
    void execute() override;

    /**
     * @brief Set multiplexer to the next pin
     * and triggers conversion on it.
     */
    void triggerNextADSConversion();
};


#endif
