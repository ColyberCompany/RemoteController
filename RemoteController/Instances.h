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
#include "IInputs.h"
#include "IScreen.h"


namespace Instance
{
    using namespace Interfaces;

    extern ITasker& tasker;
    extern TaskPlanner& taskPlanner;
    extern IInputs& readings;
    extern IScreen& screen;

    extern ScreenValues& screenValues;
}


#endif

