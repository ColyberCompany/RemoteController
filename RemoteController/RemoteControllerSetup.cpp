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
#include "Inputs/AnalogToControlStick.h"
#include "Inputs/PinAdapter.h"
#include "Tasks.h"
#include "ESP8266WiFiComm/ESP8266WiFiComm.cpp" // Including a cpp file was a simplest solution
#include "Communication/DroneCommManager.h"
#include "PacketCommunicationWithQueue.h"


// Helper functions
void addTasksToTasker();
void setupControlStickInitialInputRanges();
void setupMeasurements();
void setupDroneCommunication();
//...


/**
 * @brief This class enables wifi state to be available outside this file.
 */
class Esp8266WiFiStateMeasurementAdapter : public Measurement
{
public:
    Esp8266WiFiStateMeasurementAdapter() : Measurement(Enums::MeasurementType::ESP8266WiFiState) {}
    float getNewValue() override;
};



namespace Assemble
{
    // Tasker and TaskPlanner
    SimpleTasker simpleTasker(Config::MaxSimpleTaskerTasks);
    TaskPlanner taskPlanner(Config::MaxTaskPlannerTasks);

    // Communication
    ESP8266WiFiComm esp8266WiFiComm(Config::WiFiSSID, Config::WiFiPassword, Config::WiFiPort, Config::DroneCommMaxBufferSize);
    PacketCommunicationWithQueue droneComm(&esp8266WiFiComm, Config::DroneCommMaxQueuedBuffers);
    DroneCommManager droneCommManager(droneComm);

    // Screen
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
    Esp8266WiFiStateMeasurementAdapter esp8266WiFiStateMeasurementAdapter;
}


namespace Instance
{
    using namespace Interfaces;

    ITasker& tasker = Assemble::simpleTasker;
    TaskPlanner& taskPlanner = Assemble::taskPlanner;
    Screen& screen = Assemble::lcdScreen;
    MeasurementsManager& measurementsManager = Assemble::measurementsManager;
    PacketCommunication& droneComm = Assemble::droneComm;
    DroneCommManager& droneCommManager = Assemble::droneCommManager;
}



void setupRemoteController()
{
    Serial.begin(Enums::BAUD_115200);
    Serial.println("Program has started");

    delay(200);

    Serial.print("Adds tasker tasks");
    addTasksToTasker();
    Serial.println(" OK");

    Serial.print("Initialize lcd");
    Assemble::lcdScreen.initialize();
    Wire.setClock(400000L);
    Serial.println(" OK");

    Serial.print("Initialize sticks input ranges");
    setupControlStickInitialInputRanges();
    Serial.println(" OK");

    Serial.print("Initialize measurements");
    setupMeasurements();
    Serial.println(" OK");

    Serial.print("Setup communication");
    setupDroneCommunication();
    Serial.println(" OK");

    // ...
}


class : public Task
{
    void execute() override
    {
        Instance::screen.getScreenDataPointer()->droneConnectionState = Assemble::esp8266WiFiComm.isConnected();
    }
} tempUpdateScreenWifiStateTask;



void addTasksToTasker()
{
    using Instance::tasker;

    tasker.addTask(&Tasks::debugTask, 10);
    tasker.addTask(&Assemble::lcdScreen, 13);
    tasker.addTask(&Tasks::updateScreenData, 13);

    tasker.addTask(&tempUpdateScreenWifiStateTask, 13);

    // add other tasks...
}


void setupControlStickInitialInputRanges()
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

    // Initialize digital pins
    Assemble::leftSwitch.initializePin(INPUT_PULLUP);
    Assemble::rightSwitch.initializePin(INPUT_PULLUP);

    // Add all measurement sources to the measurementsManager
    Assemble::measurementsManager.addMeasurementSource(&Assemble::throttleADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::yawADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::pitchADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::rollADCAdapter);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::leftSwitch);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::rightSwitch);
    Assemble::measurementsManager.addMeasurementSource(&Assemble::esp8266WiFiStateMeasurementAdapter);
    // add other measurements sources...
}


void setupDroneCommunication()
{
    Assemble::esp8266WiFiComm.begin();
    // TODO: set target IP address
    Assemble::droneComm.adaptConnectionStabilityToInterval();
}




float Esp8266WiFiStateMeasurementAdapter::getNewValue()
{
    return Assemble::esp8266WiFiComm.isConnected() ? 1.f : 0.f;
}
