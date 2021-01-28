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
    // TODO: send packet to the drone

    Serial.println("armed");
}


void RemoteControllerManager::setDisarmed()
{
    currentFlightMode = FlightModeTypes::UNARMED;
    // TODO: send packet to the drone

    Serial.println("disarmed");
}


void RemoteControllerManager::setFlightMode(FlightModeTypes flightModeType)
{
    currentFlightMode = flightModeType;

    // TODO: send packet to the drone
}


bool RemoteControllerManager::isArmed()
{
    return currentFlightMode == FlightModeTypes::UNARMED ? false : true;
}


FlightModeTypes RemoteControllerManager::getCurrentFlightMode()
{
    return currentFlightMode;
}
