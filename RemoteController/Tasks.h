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
#include "Common/ScreenData.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"


namespace Tasks
{

    class : public IExecutable
    {
        void execute() override
        {
            using Instance::measurementsManager;
            using Enums::MeasurementType;
            
            ScreenData& screenData = *Instance::screen.getScreenDataPointer();

            screenData.stickThrottle = measurementsManager.getMeasurement(MeasurementType::ThrottleStick);
            screenData.stickYaw = measurementsManager.getMeasurement(MeasurementType::YawStick);
            screenData.stickPitch = measurementsManager.getMeasurement(MeasurementType::PitchStick);
            screenData.stickRoll = measurementsManager.getMeasurement(MeasurementType::RollStick);

            screenData.leftSwitchState = !(bool)measurementsManager.getMeasurement(MeasurementType::LeftSwitch);
            screenData.rightSwitchState = !(bool)measurementsManager.getMeasurement(MeasurementType::RightSwitch);

            screenData.flightMode = Instance::remoteControllerManager.getCurrentFlightModeType();

            screenData.droneConnectionState = (bool)measurementsManager.getMeasurement(MeasurementType::ESP8266WiFiState);

            screenData.dronePitch = commData.drone.pitchAngle_deg;
            screenData.droneRoll = commData.drone.rollAngle_deg;
        }
    } updateScreenData;


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

            commData.pilot.stick.throttle = measurementsManager.getMeasurement(MeasurementType::ThrottleStick);
            commData.pilot.stick.yaw = measurementsManager.getMeasurement(MeasurementType::YawStick);
            commData.pilot.stick.pitch = measurementsManager.getMeasurement(MeasurementType::PitchStick);
            commData.pilot.stick.roll = measurementsManager.getMeasurement(MeasurementType::RollStick);

            if (commData.pilot.stick.throttle < 10)
            {
                commData.pilot.stick.yaw = 0;
                commData.pilot.stick.pitch = 0;
                commData.pilot.stick.roll = 0;
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
}


#endif
