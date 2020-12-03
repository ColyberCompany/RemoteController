/**
 * @file RemoteControllerSetup.cpp
 * @author Jan Wielgus
 * @date 2020-12-03
 * 
 */

#include "RemoteControllerSetup.h"
#include "Instances.h"
#include "Inputs/InputReader.h"
#include "Screen/LCD.h"
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
}



namespace Instance
{
    ITasker& tasker = Assemble::tasker;
    TaskPlanner& taskPlanner = Assemble::taskPlanner;
    IInputs& readings = Assemble::inputReader;
    IScreen& screen = Assemble::lcdScreen;
}






void setupRemoteController()
{
    addTasksToTasker();
    Instance::readings.initialize();
    Instance::screen.initialize();
    setupDroneComm();
}

