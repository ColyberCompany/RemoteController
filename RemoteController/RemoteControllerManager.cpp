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


void RemoteControllerManager::setFlightMode(FlightModeTypes flightModeType)
{
    currentFlightMode = flightModeType;
    
    commData.flightMode = (uint8_t)currentFlightMode;

    Instance::droneComm.sendDataPacket(&DataPackets::flightModeChange);
}


bool RemoteControllerManager::isArmed()
{
    return currentFlightMode == FlightModeTypes::UNARMED ? false : true;
}


FlightModeTypes RemoteControllerManager::getCurrentFlightModeType()
{
    return currentFlightMode;
}
