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
#include <Tasker.h>
#include "config.h"
#include "Enums/BaudRateTypes.h"
#include "Inputs/ADS1115Handler.h"
#include "Inputs/ControlStickADCAdapter.h"
#include "Inputs/AnalogToControlStick.h"
#include "Inputs/PinAdapter.h"
#include "Tasks.h"
#include "ESP8266WiFiComm/ESP8266WiFiComm.cpp" // Including a cpp file was a simplest solution
#include <PacketCommunication.h>
#include "StickGestures/ArmingStates.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"

#include "tempChangeIPFunc.h"


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

    Tasker tasker(Config::MaxSimpleTaskerTasks);

    namespace Communication {
        PacketComm::ESP8266WiFiComm esp8266WiFiComm(Config::WiFiPort, Config::DroneCommMaxBufferSize);
        PacketComm::PacketCommunication droneComm(&esp8266WiFiComm);
    }

    // Screen
    LCDScreen lcdScreen;

    // Inputs
    MeasurementsManager measurementsManager;
    ADS1115Handler ads1115Handler;

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
    DigitalPinAdapter leftSwitch(Enums::MeasurementType::LeftSwitch, Config::LeftSwitchPin, true);
    DigitalPinAdapter rightSwitch(Enums::MeasurementType::RightSwitch, Config::RightSwitchPin, true);
    Esp8266WiFiStateMeasurementAdapter esp8266WiFiStateMeasurementAdapter;
}


void tempSetIPToDrone() {
    Assemble::Communication::esp8266WiFiComm.setTargetIPAddress(192, 168, 43, 151); // drone WiFi device address
}
void tempSetIPToAndroidApp() {
    Assemble::Communication::esp8266WiFiComm.setTargetIPAddress(192, 168, 43, 1);
}


namespace Instance
{
    using namespace Interfaces;

    RemoteControllerManager& remoteControllerManager = Assemble::remoteControllerManager;
    Tasker& tasker = Assemble::tasker;
    Screen& screen = Assemble::lcdScreen;
    MeasurementsManager& measurementsManager = Assemble::measurementsManager;
    PacketComm::PacketCommunication& droneComm = Assemble::Communication::droneComm;
    //DroneCommManager& droneCommManager = Assemble::droneCommManager;
    Context& stickArmingContext = Assemble::stickArmingContext;
}



class : public IExecutable
{
    void execute() override
    {
        //Serial.println("dziala");
        //Serial.println(Assemble::ads1115Handler.getRawRoll());
        //Serial.println(Assemble::pitchADCAdapter.getNewValue());
        //Serial.println(Assemble::Communication::esp8266WiFiComm.getLocalIP());
        //Serial.println(Assemble::tasker.getLoad());
        //Serial.println(Instance::measurementsManager.getMeasurement())
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

    tasker.addTask_Hz(&debugTask, 10);
    tasker.addTask_Hz(&Assemble::lcdScreen, 10);
    tasker.addTask_Hz(&Assemble::ads1115Handler, 700, TaskType::NO_CATCHING_UP);
    tasker.addTask_Hz(&Tasks::stickArmingContext, 15);
    tasker.addTask_Hz(&Tasks::changeWatcher, 4);
    tasker.addTask_Hz(&Tasks::steeringSending, Config::DroneCommSteeringSendingFrequency_Hz);
    tasker.addTask_Hz(&Tasks::droneCommReceiving, Config::DroneCommReceivingFrequency_Hz);

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
    WiFi.mode(WIFI_STA);
    WiFi.begin(Config::WiFiSSID, Config::WiFiPassword);
    Assemble::Communication::esp8266WiFiComm.setTargetIPAddress(192, 168, 43, 151); // drone WiFi device address
    Instance::droneComm.adaptConnStabilityToFrequency(Config::DroneCommReceivingFrequency_Hz);

    Instance::droneComm.registerReceivePacket(&DataPackets::droneMeasurementsAndState);  
    Instance::droneComm.registerReceivePacket(&DataPackets::pidTuningAndroid);
    // add other data packets that could be received...
}


void setupStickGestureRecognition()
{
    Assemble::stickArmingContext.setState<ArmChangeState1>(&Assemble::stickArmingContext);
}




float Esp8266WiFiStateMeasurementAdapter::getNewValue()
{
    return Assemble::Communication::esp8266WiFiComm.isConnected() ? 1.f : 0.f;
}
