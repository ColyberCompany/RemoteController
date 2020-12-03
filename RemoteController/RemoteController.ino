/**
 * @file RemoteController.ino
 * @author Jan Wielgus
 * @date 2020-12-01
 * 
 */

#include "RemoteControllerSetup.h"


void setup()
{
    setupRemoteController();
}


void loop()
{
    Instance::tasker.runLoop();
    Instance::taskPlanner.execute();
}

