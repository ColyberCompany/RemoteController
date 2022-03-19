/**
 * @file MeasurementType.h
 * @author Jan Wielgus
 * @brief List of all measurements.
 * @date 2021-01-02
 * 
 */

#ifndef MEASUREMENTTYPE_H
#define MEASUREMENTTYPE_H


namespace Enums
{
    enum MeasurementType
    {
        ThrottleStick,
        YawStick,
        PitchStick,
        RollStick,
        LeftSwitch,
        RightSwitch,
        ESP8266WiFiState
        // add new here...
    };
}


#endif
