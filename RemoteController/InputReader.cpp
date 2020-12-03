/**
 * @file InputReader.cpp
 * @author Jan Wielgus
 * @date 2020-12-03
 * 
 */

#include "InputReader.h"
#include "config.h"


InputReader::InputReader(TaskPlanner& _taskPlanner)
    : taskPlanner(_taskPlanner), ads1115(ADS1115_DEFAULT_ADDRESS)
{

}


bool InputReader::initialize()
{
    ads1115.initialize();
    ads1115.setMode(ADS1115_MODE_SINGLESHOT);
    ads1115.setRate(ADS1115_RATE_860);
    // Set the gain (PGA) +/- 6.144V
    // Note that any analog input must be higher than -0.3V and less than VDD +0.3
    ads1115.setGain(ADS1115_PGA_6P144);

    // ADDITIONAL PIN CAN BE USED TO INDICATE CONVERSION READY
    /*pinMode(alertReadyPin, INPUT_PULLUP);
    adc.setConversionReadyPinMode();*/

    triggerNextADSConversion();


    // Left/right switches analog read
    pinMode(Config::leftSwitchPin, INPUT_PULLUP);
    pinMode(Config::rightSwitchPin, INPUT_PULLUP);







    // TODO: !!!! SET PROPERTIES OF ALL STICKS
    //throttle.setProperties();







    return true;
}


ControlSticks InputReader::readControlSticksValues()
{
    return ControlSticks(
        throttle.update(ADSMeasurements[0]),
        yaw.update(ADSMeasurements[1]),
        pitch.update(ADSMeasurements[2]),
        roll.update(ADSMeasurements[3])
    );
}


bool InputReader::readLeftSwitch()
{
    return digitalRead(Config::leftSwitchPin) == LOW;
}


bool InputReader::readRightSwitch()
{
    return digitalRead(Config::rightSwitchPin) == LOW;
}


void InputReader::execute()
{
    //ADSMeasurements[currentADSPin] = ads1115.getMilliVolts(false);
    ADSMeasurements[currentADSPin] = ads1115.getConversion();
    triggerNextADSConversion();
}


void InputReader::triggerNextADSConversion()
{
    currentADSPin++;
    currentADSPin %= 4;

    switch (currentADSPin)
    {
        case 0:
            ads1115.setMultiplexer(ADS1115_MUX_P0_NG);
            break;
        case 1:
            ads1115.setMultiplexer(ADS1115_MUX_P1_NG);
            break;
        case 2:
            ads1115.setMultiplexer(ADS1115_MUX_P2_NG);
            break;
        case 3:
            ads1115.setMultiplexer(ADS1115_MUX_P3_NG);
            break;
    }

    ads1115.triggerConversion();
    taskPlanner.scheduleTask_us(this, ADSConversionTime_us);
}


