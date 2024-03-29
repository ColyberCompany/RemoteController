/**
 * @file Instances.h
 * @author Jan Wielgus
 * @brief Contain references to the most inportant instances.
 * @date 2020-12-28
 * 
 */

#ifndef INSTANCES_H
#define INSTANCES_H

#include "RemoteControllerManager.h"
#include <Tasker.h>
#include "Interfaces/Screen.h"
#include "Inputs/MeasurementsManager.h"
#include <PacketCommunication.h>
#include <Context.h>


namespace Instance
{
    extern RemoteControllerManager& remoteControllerManager;
    extern Tasker& tasker;
    extern Interfaces::Screen& screen;
    extern MeasurementsManager& measurementsManager;
    extern PacketComm::PacketCommunication& droneComm;
    extern Context& stickArmingContext;
}


#endif
