/**
 * @file Instances.h
 * @author Jan Wielgus
 * @brief Contain references to the most inportant instances.
 * @date 2020-12-28
 * 
 */

#ifndef INSTANCES_H
#define INSTANCES_H

#include <ITasker.h>
#include <TaskPlanner.h>
#include "Interfaces/Screen.h"
#include "Inputs/MeasurementsManager.h"


namespace Instance
{
    extern ITasker& tasker;
    extern TaskPlanner& taskPlanner;
    extern Interfaces::Screen& screen;
    extern MeasurementsManager& measurementsManager;
}


#endif
