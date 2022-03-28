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
    #include <Arduino.h>
#endif

#include "Enums/BaudRateTypes.h"


namespace Config
{
    const uint16_t MainFrequency_Hz = 250;
    const uint16_t MainInterval_us = 1000000 / MainFrequency_Hz;
    const float MainInterval_s = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    const uint8_t MaxSimpleTaskerTasks = 15;

    const size_t DroneCommMaxBufferSize = 40;
    const uint16_t DroneCommReceivingFrequency_Hz = 20; // TODO: set receiving frequency
    const uint16_t DroneCommSteeringSendingFrequency_Hz = 20;

    const uint8_t LeftSwitchPin = D8;
    const uint8_t RightSwitchPin = D7;

    const uint16_t ControlSticksInputOffset = 450;

    const char* const WiFiSSID = "HUAWEI_P_smart";
	const char* const WiFiPassword = "22222222";
	const uint16_t WiFiPort = 8888;
}


#endif
