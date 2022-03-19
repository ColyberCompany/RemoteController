/**
 * @file ADS1115Handler.cpp
 * @author Jan Wielgus
 * @date 2021-01-02
 * 
 */

#include "Inputs/ADS1115Handler.h"
#include "config.h"


ADS1115Handler::ADS1115Handler()
    : ads1115(ADS1115_DEFAULT_ADDRESS)
{
}


bool ADS1115Handler::initialize()
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
    pinMode(Config::LeftSwitchPin, INPUT_PULLUP);
    pinMode(Config::RightSwitchPin, INPUT_PULLUP);

    return true;
}


uint16_t ADS1115Handler::getRawThrottle()
{
    return adsMeasurements[0];
}


int16_t ADS1115Handler::getRawYaw()
{
    return adsMeasurements[1];
}


int16_t ADS1115Handler::getRawPitch()
{
    return adsMeasurements[2];
}


int16_t ADS1115Handler::getRawRoll()
{
    return adsMeasurements[3];
}



void ADS1115Handler::execute()
{
    //ads1115.getMilliVolts(false);

    if (ads1115.pollConversion(10))
        adsMeasurements[currentADSPin] = ads1115.getConversion(false);

    triggerNextADSConversion();
}


void ADS1115Handler::triggerNextADSConversion()
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
}
