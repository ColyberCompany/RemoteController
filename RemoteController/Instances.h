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
#include "Interfaces/Screen.h"


namespace Instance
{
    extern ITasker& tasker;
    extern Interfaces::Screen& screen;
}


#endif
