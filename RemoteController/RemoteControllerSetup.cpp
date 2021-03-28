/**
 * @file RemoteControllerSetup.cpp
 * @author Jan Wielgus
 * @date 2020-12-28
 * 
 */

#include "RemoteControllerSetup.h"
#include "RemoteControllerManager.h"
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
#include "PacketCommunicationWithQueue.h"
#include "StickGestures/ArmingStates.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"


// Helper functions
void addTasksToTasker();
void setupControlStickInitialInputRanges();
void setupMeasurements();
void setupCommunication();
void setupStickGestureRecognition();
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
    RemoteControllerManager remoteControllerManager;

    // Tasker and TaskPlanner
    SimpleTasker simpleTasker(Config::MaxSimpleTaskerTasks);
    TaskPlanner taskPlanner(Config::MaxTaskPlannerTasks);

    // Communication
    ESP8266WiFiComm esp8266WiFiComm(Config::WiFiSSID, Config::WiFiPassword, Config::WiFiPort, Config::DroneCommMaxBufferSize);
    PacketCommunicationWithQueue droneComm(&esp8266WiFiComm, Config::DroneCommMaxQueuedBuffers);

    // Screen
    LCDScreen lcdScreen;

    // Inputs
    MeasurementsManager measurementsManager;
    ADS1115Handler ads1115Handler(taskPlanner);

    // Gesture recognition
    Context stickArmingContext;

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

    RemoteControllerManager& remoteControllerManager = Assemble::remoteControllerManager;
    ITasker& tasker = Assemble::simpleTasker;
    TaskPlanner& taskPlanner = Assemble::taskPlanner;
    Screen& screen = Assemble::lcdScreen;
    MeasurementsManager& measurementsManager = Assemble::measurementsManager;
    PacketCommunication& droneComm = Assemble::droneComm;
    //DroneCommManager& droneCommManager = Assemble::droneCommManager;
    Context& stickArmingContext = Assemble::stickArmingContext;
}



class : public Task
    {
        void execute() override
        {
            //Serial.println("dziala");
            //Serial.println(Assemble::ads1115Handler.getRawRoll());
            //Serial.println(Assemble::pitchADCAdapter.getNewValue());
            Serial.println(Assemble::esp8266WiFiComm.getLocalIP());
        }
    } debugTask;




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
    setupCommunication();
    Serial.println(" OK");

    Serial.print("Setup stick gesture recognition");
    setupStickGestureRecognition();
    Serial.println(" OK");

    // ...
}




void addTasksToTasker()
{
    using Instance::tasker;

    tasker.addTask(&debugTask, 10);
    tasker.addTask(&Assemble::lcdScreen, 13);
    tasker.addTask(&Tasks::updateScreenData, 13);
    tasker.addTask(&Tasks::stickArmingContext, 15);
    tasker.addTask(&Tasks::steeringSending, Config::DroneCommSteeringSendingFrequency_Hz);
    tasker.addTask(&Tasks::droneCommReceiving, Config::DroneCommReceivingFrequency_Hz);

    // add other tasks...
}


void setupControlStickInitialInputRanges()
{
    using Config::ControlSticksInputOffset;

    // There you can set control sticks raw calibration values \/ \/
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
    using Assemble::measurementsManager;
    measurementsManager.addMeasurementSource(&Assemble::throttleADCAdapter);
    measurementsManager.addMeasurementSource(&Assemble::yawADCAdapter);
    measurementsManager.addMeasurementSource(&Assemble::pitchADCAdapter);
    measurementsManager.addMeasurementSource(&Assemble::rollADCAdapter);
    measurementsManager.addMeasurementSource(&Assemble::leftSwitch);
    measurementsManager.addMeasurementSource(&Assemble::rightSwitch);
    measurementsManager.addMeasurementSource(&Assemble::esp8266WiFiStateMeasurementAdapter);
    // add other measurements sources...
}


void setupCommunication()
{
    Assemble::esp8266WiFiComm.begin();
    // TODO: set target IP address
    Instance::droneComm.adaptConnStabilityToFrequency(Config::DroneCommReceivingFrequency_Hz);

    Instance::droneComm.addReceiveDataPacketPointer(&DataPackets::droneMeasurementsAndState);  
}


void setupStickGestureRecognition()
{
    Assemble::stickArmingContext.setState<ArmChangeState1>(&Assemble::stickArmingContext);
}




float Esp8266WiFiStateMeasurementAdapter::getNewValue()
{
    return Assemble::esp8266WiFiComm.isConnected() ? 1.f : 0.f;
}
