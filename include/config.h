/**
 * @file config.h
 * @author Jan Wielgus
 * @brief Configuration file.
 * @date 2020-12-01
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <cstddef>
#include <IPAddress.h>

#define CI constexpr inline


namespace Config
{
    CI uint16_t MainFrequency_Hz = 250;
    CI uint16_t MainInterval_us = 1000000 / MainFrequency_Hz;
    CI float MainInterval_s = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    CI uint8_t MaxSimpleTaskerTasks = 15;

    CI size_t DroneCommMaxBufferSize = 40;
    CI uint16_t DroneCommReceivingFrequency_Hz = 20; // TODO: set receiving frequency
    CI uint16_t DroneCommSteeringSendingFrequency_Hz = 20;

    CI uint8_t LeftSwitchPin = D8;
    CI uint8_t RightSwitchPin = D7;

    CI uint16_t ControlSticksInputOffset = 450;

    CI const char* const WiFiSSID = "HUAWEI_P_smart";
	CI const char* const WiFiPassword = "22222222";
	CI uint16_t WiFiPort = 8888;
}

#undef CI

#endif
