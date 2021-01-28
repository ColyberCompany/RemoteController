/**
 * @file RemoteControllerManager.cpp
 * @author Jan Wielgus
 * @date 2021-01-28
 * 
 */

#include "RemoteControllerManager.h"
#include "Instances.h"

using namespace Instance;
using Enums::FlightModeTypes;
using Enums::StateType;


void RemoteControllerManager::setArmed()
{
    currentFlightMode = FlightModeTypes::STABILIZE; // FIXME: maybe add idle flight mode or something like that

    // TODO: change for data packets with acknowledgment if implemented
    Instance::droneComm.sendDataPacket(&Instance::droneCommManager.sending.armDrone);

    //Serial.println("armed");
}


void RemoteControllerManager::setDisarmed()
{
    currentFlightMode = FlightModeTypes::UNARMED;
    
    // TODO: change for data packets with acknowledgment if implemented
    Instance::droneComm.sendDataPacket(&Instance::droneCommManager.sending.disarmDrone);

    //Serial.println("disarmed");
}


void RemoteControllerManager::setFlightMode(FlightModeTypes flightModeType)
{
    currentFlightMode = flightModeType;

    Instance::droneCommManager.sending.data.flightMode = (uint8_t)currentFlightMode;
    Instance::droneComm.sendDataPacket(&Instance::droneCommManager.sending.newFlightMode);
}


bool RemoteControllerManager::isArmed()
{
    return currentFlightMode == FlightModeTypes::UNARMED ? false : true;
}


FlightModeTypes RemoteControllerManager::getCurrentFlightMode()
{
    return currentFlightMode;
}
