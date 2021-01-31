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


void RemoteControllerManager::setFlightMode(FlightModeTypes flightModeType)
{
    currentFlightMode = flightModeType;
    
    Instance::droneCommManager.sending.data.flightMode = (uint8_t)currentFlightMode;

    Instance::droneComm.sendDataPacket(&Instance::droneCommManager.sending.flightModeChange);
}


bool RemoteControllerManager::isArmed()
{
    return currentFlightMode == FlightModeTypes::UNARMED ? false : true;
}


FlightModeTypes RemoteControllerManager::getCurrentFlightModeType()
{
    return currentFlightMode;
}
