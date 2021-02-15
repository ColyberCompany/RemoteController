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

            screenData.dronePitch = Instance::droneCommManager.receiving.data.pitchAngle_deg;
            screenData.droneRoll = Instance::droneCommManager.receiving.data.rollAngle_deg;
        }
    } updateScreenData;


    class : public Task
    {
        void execute() override
        {
            Instance::stickArmingContext.updateState();
        }
    } stickArmingContext;



    class : public Task
    {
        void execute() override
        {
            using Instance::measurementsManager;
            using Enums::MeasurementType;

            DataForDrone& dataForDrone = Instance::droneCommManager.sending.data;
            dataForDrone.throttle = measurementsManager.getMeasurement(MeasurementType::ThrottleStick);
            dataForDrone.yaw = measurementsManager.getMeasurement(MeasurementType::YawStick);
            dataForDrone.pitch = measurementsManager.getMeasurement(MeasurementType::PitchStick);
            dataForDrone.roll = measurementsManager.getMeasurement(MeasurementType::RollStick);

            Instance::droneComm.sendDataPacket(&Instance::droneCommManager.sending.steering);
        }
    } steeringSending;



    class : public Task
    {
        void execute() override
        {
            Instance::droneComm.receiveAndUpdatePackets();
        }
    } droneCommReceiving;
}


#endif
