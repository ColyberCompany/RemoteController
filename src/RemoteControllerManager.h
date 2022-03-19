/**
 * @file RemoteControllerManager.h
 * @author Jan Wielgus
 * @brief This object manages crucial data and performing
 * important actions like arming the drone.
 * Classes that can change state have to be friends of this class.
 * There should be only one instance of this class.
 * @date 2021-01-28
 * 
 */

#ifndef REMOTECONTROLLERMANAGER_H
#define REMOTECONTROLLERMANAGER_H

#include "Enums/FlightModeTypes.h"
#include <PacketCommunication.h>
#include "StickGestures/ArmingStates.h"
#include "Enums/FlightModeTypes.h"
#include "Enums/StateType.h"


class RemoteControllerManager
{
    Enums::FlightModeTypes currentFlightMode = Enums::FlightModeTypes::UNARMED;

public:
    bool isArmed();
    Enums::FlightModeTypes getCurrentFlightModeType();

    void setFlightMode(Enums::FlightModeTypes flightModeType);
};


#endif
