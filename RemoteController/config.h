/**
 * @file config.h
 * @author Jan Wielgus
 * @brief Configuration file.
 * @version 0.1
 * @date 2020-12-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef ARDUINO
    #include <arduino.h>
#endif


#include "Enums/BaudRateTypes.h"


namespace Config
{

    const size_t DroneCommMaxBufferSize = 40;
    const size_t DroneCommMaxQueuedBuffers = 30;

    const uint16_t MainFrequency_Hz = 250;
    const uint16_t MainInterval_us = 1000000 / MainFrequency_Hz;
    const float MainInterval_s = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    const uint8_t leftSwitchPin = D8;
    const uint8_t rightSwitchPin = D7;

    const char* const WiFiSSID = "HUAWEI_P_smart";
	const char* const WiFiPassword = "22222222";
	const uint16_t WiFiPort = 8888;
}


#endif
