/**
 * @file RemoteControllerSetup.cpp
 * @author Jan Wielgus
 * @date 2020-12-28
 * 
 */

#include "RemoteControllerSetup.h"
#include "Screen/LCDScreen.h"
#include <SimpleTasker.h>
#include "config.h"


// Helper functions
void addTasksToTasker();
//...


namespace Assemble
{
    SimpleTasker simpleTasker(Config::MaxSimpleTaskerTasks);
    LCDScreen lcdScreen;
}


namespace Instance
{
    using namespace Interfaces;

    ITasker& tasker = Assemble::simpleTasker;
    Screen& screen = Assemble::lcdScreen;
}



void setupRemoteController()
{
    addTasksToTasker();
    Assemble::lcdScreen.initialize();
    Wire.setClock(400000L);
    // ...
}



void addTasksToTasker()
{
    using Instance::tasker;

    // TODO: create and add tasks
}
