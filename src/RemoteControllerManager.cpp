/**
 * @file RemoteControllerManager.cpp
 * @author Jan Wielgus
 * @date 2021-01-28
 * 
 */

#include "RemoteControllerManager.h"
#include "Instances.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"

using namespace Instance;
using Enums::FlightModeTypes;
using Enums::StateType;


bool RemoteControllerManager::isArmed()
{
    return currentFlightMode == FlightModeTypes::UNARMED ? false : true;
}


FlightModeTypes RemoteControllerManager::getCurrentFlightModeType()
{
    return currentFlightMode;
}


void RemoteControllerManager::setFlightMode(FlightModeTypes flightModeType)
{
    currentFlightMode = flightModeType;
    
    commData.flightModeChange.flightMode = (uint8_t)currentFlightMode;
    Instance::droneComm.send(&DataPackets::flightModeChange);
    Instance::droneComm.send(&DataPackets::flightModeChange);
    Instance::droneComm.send(&DataPackets::flightModeChange); // send 3 times for certanity
}
