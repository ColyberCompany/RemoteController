/**
 * @file Instances.h
 * @author Jan Wielgus
 * @brief Contain references to the most inportant instances.
 * @date 2020-12-02
 * 
 */

#ifndef INSTANCES_H
#define INSTANCES_H

#include <ITasker.h>
#include <TaskPlanner.h>
#include "InputReader.h"
#include "IScreen.h"
#include <PacketCommunication.h>


namespace Instance
{
    using namespace Interfaces;

    extern ITasker& tasker;
    extern TaskPlanner& taskPlanner;
    extern InputReader& readings;
    extern IScreen& screen;
    extern PacketCommunication& dronePacketComm;

    extern ScreenValues& screenValues;
}


#endif

