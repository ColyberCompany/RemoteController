/**
 * @file SticksState.cpp
 * @author Jan Wielgus
 * @date 2021-01-27
 * 
 */

#include "../StickGestures/SticksState.h"
#include "../Instances.h"
#include "../utils.h"


SticksState::SticksState(Context* context)
    : State(context)
{
}


SticksState::~SticksState()
{
}


void SticksState::updateSticksValues()
{
    using Instance::measurementsManager;
    sticks = Utils::controlSticksFromMeasurementsManager(measurementsManager);
}


bool SticksState::throttleNeutral() const
{
    return sticks.getThrottle() == 0;
}


bool SticksState::sticksInNeutralPos() const
{
    return sticks.getThrottle() == 0 && sticks.getYaw() == 0 &&
        sticks.getPitch() == 0 && sticks.getRoll() == 0;
}


bool SticksState::isWithinRange(int16_t value, int16_t min, int16_t max)
{
    return value >= min && value <= max;
}



bool SticksState::isThrottleGreaterThan(int16_t value) const
{
    return sticks.getThrottle() > value;
}

bool SticksState::isThrottleLessThan(int16_t value) const
{
    return sticks.getThrottle() < value;
}

bool SticksState::isYawGreaterThan(int16_t value) const
{
    return sticks.getYaw() > value;
}

bool SticksState::isYawLessThan(int16_t value) const
{
    return sticks.getYaw() < value;
}

bool SticksState::isPitchGreaterThan(int16_t value) const
{
    return sticks.getPitch() > value;
}

bool SticksState::isPitchLessThan(int16_t value) const
{
    return sticks.getPitch() < value;
}

bool SticksState::isRollGreaterThan(int16_t value) const
{
    return sticks.getRoll() > value;
}

bool SticksState::isRollLessThan(int16_t value) const
{
    return sticks.getRoll() < value;
}
