/**
 * @file RemoteControllerSetup.cpp
 * @author Jan Wielgus
 * @date 2020-12-03
 * 
 */

#include "RemoteControllerSetup.h"
#include "Instances.h"
#include "InputReader.h"
#include "LCD.h"
#include <SimpleTasker.h>
#include <StreamComm.h>
#include <PacketCommunicationWithQueue.h>


using namespace Interfaces;


// Helper functions
void addTasksToTasker();
void setupDroneComm();



namespace Assemble
{
    SimpleTasker tasker(15);
    TaskPlanner taskPlanner(7);
    InputReader inputReader(taskPlanner);
    LCD lcdScreen;

    ScreenValues screenValues;
}



namespace Instance
{
    ITasker& tasker = Assemble::tasker;
    TaskPlanner& taskPlanner = Assemble::taskPlanner;
    IInputs& readings = Assemble::inputReader;
    IScreen& screen = Assemble::lcdScreen;

    ScreenValues& screenValues = Assemble::screenValues;
}


class TestTask : public Task
{
    void execute() override
    {
        Instance::screenValues.stickThrottle = Instance::readings.readRightSwitch();
        Instance::screen.update(Instance::screenValues);
    }
};




void setupRemoteController()
{
    addTasksToTasker();
    Instance::readings.initialize();
    Instance::screen.initialize();
    setupDroneComm();
}




void addTasksToTasker()
{
    using Instance::tasker;

    // TODO: task that updates screen

    tasker.addTask(new TestTask(), 5);
}


void setupDroneComm()
{
    // TODO: setup comm
}

