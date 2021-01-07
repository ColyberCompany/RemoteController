/**
 * @file Tasks.h
 * @author Jan Wielgus
 * @brief List of all tasks and executables.
 * @date 2021-01-05
 * 
 */

#ifndef TASKS_H
#define TASKS_H

#include <Task.h>
#include "Instances.h"
#include "Common/ScreenData.h"


namespace Tasks
{


    class : public Task
    {
        void execute() override
        {
            //Serial.println("dziala");
            //Serial.println(Assemble::ads1115Handler.getRawRoll());
            //Serial.println(Assemble::pitchADCAdapter.getNewValue());
        }
    } debugTask;


    class : public Task
    {
        void execute() override
        {
            using namespace Instance;
            using Enums::MeasurementType;
            ScreenData screenData;

            screenData.stickThrottle = measurementsManager.getMeasurement(MeasurementType::ThrottleStick);
            screenData.stickYaw = measurementsManager.getMeasurement(MeasurementType::YawStick);
            screenData.stickPitch = measurementsManager.getMeasurement(MeasurementType::PitchStick);
            screenData.stickRoll = measurementsManager.getMeasurement(MeasurementType::RollStick);

            screenData.leftSwitchState = !(int)measurementsManager.getMeasurement(MeasurementType::LeftSwitch);
            screenData.rightSwitchState = !(int)measurementsManager.getMeasurement(MeasurementType::RightSwitch);

            screenData.flightMode = Enums::FlightModeTypes::UNARMED; // TODO: update flight mode here

            Instance::screen.updateScreenData(screenData);
        }
    } updateScreenData;


}


#endif