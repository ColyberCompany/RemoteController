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
