/**
 * @file RemoteControllerSetup.cpp
 * @author Jan Wielgus
 * @date 2020-12-28
 * 
 */

#include "RemoteControllerSetup.h"
#include "Instances.h"
#include "Screen/LCDScreen.h"
#include <SimpleTasker.h>
#include "config.h"
#include "Enums/BaudRateTypes.h"
#include "Inputs/ADS1115Handler.h"
#include "Inputs/ControlStickADCAdapter.h"
#include "Inputs/PinAdapter.h"
#include "Inputs/AnalogToControlStick.h"


// Helper functions
void setupControlStickInputRanges();
void setupMeasurements();
void addTasksToTasker();
//...


namespace Assemble
{
    SimpleTasker simpleTasker(Config::MaxSimpleTaskerTasks);
    TaskPlanner taskPlanner(Config::MaxTaskPlannerTasks);

    LCDScreen lcdScreen;

    // Inputs
    MeasurementsManager measurementsManager;
    ADS1115Handler ads1115Handler(taskPlanner);

    // Measurements - control sticks
    ControlStickADCAdapter throttleADCAdapter(Enums::MeasurementType::ThrottleStick,
        ads1115Handler, AnalogToControlStick(0, 512, 1023, 10, 0, 0, 1000));
    AnalogToControlStick symmetricStickInitSetup(0, 512, 1023, 10, -500, 0, 500);
    ControlStickADCAdapter yawADCAdapter(Enums::MeasurementType::YawStick,
        ads1115Handler, symmetricStickInitSetup);
    ControlStickADCAdapter pitchADCAdapter(Enums::MeasurementType::PitchStick,
        ads1115Handler, symmetricStickInitSetup);
    ControlStickADCAdapter rollADCAdapter(Enums::MeasurementType::RollStick,
        ads1115Handler, symmetricStickInitSetup);
    
    // Other measurements
    DigitalPinAdapter leftSwitch(Enums::MeasurementType::LeftSwitch, Config::LeftSwitchPin);
    DigitalPinAdapter rightSwitch(Enums::MeasurementType::RightSwitch, Config::RightSwitchPin);
}


namespace Instance
{
    using namespace Interfaces;

    ITasker& tasker = Assemble::simpleTasker;
    TaskPlanner& taskPlanner = Assemble::taskPlanner;
    Screen& screen = Assemble::lcdScreen;
    MeasurementsManager& measurementsManager = Assemble::measurementsManager;
}


class TestTask : public Task
{
    void execute() override
    {
        //Serial.println("dziala");
        //Serial.println(Assemble::ads1115Handler.getRawRoll());
        Serial.println(Assemble::pitchADCAdapter.getNewValue());
    }
};



void setupRemoteController()
{
    Serial.begin(Enums::BAUD_115200);
    Serial.println("Program has started");

    delay(200);

    Serial.print("Initialize lcd");
    Assemble::lcdScreen.initialize();
    Wire.setClock(400000L);
    Serial.println(" OK");

    Serial.print("Initialize sticks input ranges");
    setupControlStickInputRanges();
    Serial.println(" OK");

    Serial.print("Initialize measurements");
    setupMeasurements();
    Serial.println(" OK");

    Serial.print("Adds tasker tasks");
    addTasksToTasker();
    Serial.println(" OK");

    // ...
}



void setupControlStickInputRanges()
{
    using Config::ControlSticksInputOffset;

    Assemble::throttleADCAdapter.setAnalogInputProperties(16050, 16050, 790, ControlSticksInputOffset);
    Assemble::yawADCAdapter.setAnalogInputProperties(16400, 8800, 950, ControlSticksInputOffset);
    Assemble::pitchADCAdapter.setAnalogInputProperties(15790, 7660, 790, ControlSticksInputOffset);
    Assemble::rollADCAdapter.setAnalogInputProperties(16950, 9110, 1300, ControlSticksInputOffset);
}


void setupMeasurements()
{
    // Initialize external ADC
    Assemble::ads1115Handler.initialize();
    Serial.println("asdfasdfasfd");

    // Initialize digital pins
    Assemble::leftSwitch.initializePin(INPUT_PULLUP);
    Assemble::rightSwitch.initializePin(INPUT_PULLUP);

    // Add all measurement sources to the measurementsManager

    /*
    Assemble::measurementsManager.addMeasurementSource(&Assemble::throttleADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::yawADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::pitchADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::rollADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::leftSwitch);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::rightSwitch);*/
    // add other measurements sources...
}


void addTasksToTasker()
{
    using Instance::tasker;

    tasker.addTask(&Assemble::lcdScreen, 20);
    tasker.addTask(new TestTask, 10);
    // TODO: create and add tasks
}
