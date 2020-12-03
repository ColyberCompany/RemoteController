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
#include "Interfaces/IInputs.h"
#include "Interfaces/IScreen.h"


namespace Instance
{
    using namespace Interfaces;

    extern ITasker& tasker;
    extern TaskPlanner& taskPlanner;
    extern IInputs& readings;
    extern IScreen& screen;
}


#endif

