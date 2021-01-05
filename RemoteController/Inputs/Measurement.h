/**
 * @file Measurement.h
 * @author Jan Wielgus
 * @brief Abstract base class for all concrete single measurement classes.
 * @date 2021-01-02
 * 
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "../Enums/MeasurementType.h"


class Measurement
{
protected:
    const Enums::MeasurementType measurementType;

public:
    Measurement(Enums::MeasurementType _measurementType)
        : measurementType(_measurementType)
    {
    }

    Enums::MeasurementType getType() const
    {
        return measurementType;
    }

    virtual float getNewValue() = 0;
};


#endif
