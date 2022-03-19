/**
 * @file MeasurementsManager.h
 * @author Jan Wielgus
 * @brief This class is used to access all measurements.
 * @date 2021-01-02
 * 
 */

#ifndef MEASUREMENTSMANAGER_H
#define MEASUREMENTSMANAGER_H

#include <GrowingArray.h>
#include "Measurement.h"
#include "Enums/MeasurementType.h"


class MeasurementsManager
{
    SimpleDataStructures::GrowingArray<Measurement*> measurementsArray;
    
public:
    MeasurementsManager();

    /**
     * @brief Add new measurement source that can be accessed later
     * through getMeasurement(_) method.
     * @param measurementSource Pointer to concrete instance that
     * extends Measurement abstract class.
     * @return false if measurement was not added, true otherwise.
     */
    bool addMeasurementSource(Measurement* measurementSource);

    /**
     * @brief Perform a measurement and return a result as float value.
     * @param measurementType Which measurement should be taken.
     * @return Measurement result (-1 could just be a result or
     * measurement source was not added before using addMeasurementSource(_) method).
     */
    float getMeasurement(Enums::MeasurementType measurementType);


private:
    Measurement* binarySearchMeasurementByType(Enums::MeasurementType type);
};


#endif
