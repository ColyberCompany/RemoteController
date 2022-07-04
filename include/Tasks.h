/**
 * @file Tasks.h
 * @author Jan Wielgus
 * @brief List of all tasks and executables.
 * @date 2021-01-05
 * 
 */

#ifndef TASKS_H
#define TASKS_H

#include <IExecutable.h>
#include "Instances.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"


namespace Tasks
{
    class : public IExecutable
    {
        void execute() override
        {
            Instance::stickArmingContext.updateState();
        }
    } stickArmingContext;



    class : public IExecutable
    {
        void execute() override
        {
            using Instance::measurementsManager;
            using Enums::MeasurementType;

            auto& data = commData.steering;

            data.throttle = measurementsManager.getMeasurement(MeasurementType::ThrottleStick);
            data.yaw = measurementsManager.getMeasurement(MeasurementType::YawStick);
            data.pitch = measurementsManager.getMeasurement(MeasurementType::PitchStick);
            data.roll = measurementsManager.getMeasurement(MeasurementType::RollStick);

            if (data.throttle < 10)
            {
                data.yaw = 0;
                data.pitch = 0;
                data.roll = 0;
            }

            Instance::droneComm.send(&DataPackets::steering);
        }
    } steeringSending;



    class : public IExecutable
    {
        void execute() override
        {
            Instance::droneComm.receive();
        }
    } droneCommReceiving;



    class : public IExecutable
    {
        bool lastRightStickState = false;

        void execute() override
        {
            bool rightStickState = Instance::measurementsManager.getMeasurement(Enums::MeasurementType::RightSwitch) == 1.f;
            
            if (Instance::remoteControllerManager.getCurrentFlightModeType() != Enums::FlightModeTypes::UNARMED)
            {
                if (!lastRightStickState && rightStickState)
                    Instance::remoteControllerManager.setFlightMode(Enums::FlightModeTypes::ALT_HOLD);
                else if (lastRightStickState && !rightStickState)
                    Instance::remoteControllerManager.setFlightMode(Enums::FlightModeTypes::STABILIZE);
            }

            lastRightStickState = rightStickState;
        }
    } changeWatcher;
}


#endif
