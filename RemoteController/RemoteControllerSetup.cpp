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
#include "Enums/BaudRateTypes.h"


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


class TestTask : public Task
{
    void execute() override
    {
        //Serial.println("dziala");
    }
};



void setupRemoteController()
{
    Serial.begin(Enums::BAUD_115200);
    Serial.println("Program has started");

    delay(200);

    addTasksToTasker();
    Assemble::lcdScreen.initialize();
    Wire.setClock(400000L);
    // ...
}



void addTasksToTasker()
{
    using Instance::tasker;

    tasker.addTask(&Assemble::lcdScreen, 20);
    tasker.addTask(new TestTask, 1);
    // TODO: create and add tasks
}
