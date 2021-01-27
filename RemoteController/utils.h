/**
 * @file utils.h
 * @author Jan Wielgus
 * @brief Some useful functinos.
 * @date 2021-01-27
 * 
 */

#ifndef UTILS_H
#define UTILS_H

#include "Inputs/MeasurementsManager.h"
#include "Common/ControlSticks.h"


namespace Utils
{
    ControlSticks controlSticksFromMeasurementsManager(MeasurementsManager& measurementsManager)
    {
        using Enums::MeasurementType;

        ControlSticks controlSticks(
            measurementsManager.getMeasurement(MeasurementType::ThrottleStick),
            measurementsManager.getMeasurement(MeasurementType::YawStick),
            measurementsManager.getMeasurement(MeasurementType::PitchStick),
            measurementsManager.getMeasurement(MeasurementType::RollStick)
        );

        return controlSticks;
    }


    // other utilities..
}


#endif
