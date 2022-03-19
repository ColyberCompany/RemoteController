#include <Arduino.h>
#include "RemoteControllerSetup.h"

void setup()
{
	setupRemoteController();
}

void loop()
{
	Instance::tasker.loop();
}
