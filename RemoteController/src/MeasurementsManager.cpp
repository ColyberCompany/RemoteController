/**
 * @file MeasurementsManager.cpp
 * @author Jan Wielgus
 * @brief Manages all measurements. Get measurements from here.
 * @date 2021-01-02
 * 
 */

#include "../Inputs/MeasurementsManager.h"

using Enums::MeasurementType;


MeasurementsManager::MeasurementsManager()
{
}


bool MeasurementsManager::addMeasurementSource(Measurement* measurement)
{
    // add in ascending order by type
    size_t index = 0;
    while (index < measurementsArray.size() &&
        measurement->getType() > measurementsArray[index]->getType())
        index++;

    return measurementsArray.add(measurement, index);
}


float MeasurementsManager::getMeasurement(MeasurementType measurementType)
{
    Measurement* measurement = binarySearchMeasurementByType(measurementType);
    if (measurement != nullptr)
        return measurement->getNewValue();
    return -1; // Measurement was not added or not found in the array.
}



Measurement* MeasurementsManager::binarySearchMeasurementByType(MeasurementType type)
{
    if (measurementsArray.size() == 0)
        return nullptr;

    int leftIndex = 0;
    int rightIndex = measurementsArray.size();

    while (leftIndex <= rightIndex)
    {
        int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
        Measurement* midMsmt = measurementsArray[midIndex]; // midMeasurement

        // Check if x is present at mid
        if (midMsmt->getType() == type)
            return midMsmt;
        
        // If x is greater, ignore left half
        else if (type > midMsmt->getType())
            leftIndex = midIndex + 1;

        // If x is smaller, ignore right half
        else
            rightIndex = midIndex - 1;
    }

    return nullptr;
}
