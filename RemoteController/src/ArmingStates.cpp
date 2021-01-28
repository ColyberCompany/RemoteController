/**
 * @file ArmingStates.cpp
 * @author Jan Wielgus
 * @date 2021-01-27
 * 
 */

#include "../StickGestures/ArmingStates.h"
#include <Context.h>



ArmChangeState1::ArmChangeState1(Context* context)
    : SticksState(context)
{
    
}

void ArmChangeState1::updateState()
{
    updateSticksValues(); // update sticks values before use

    const uint16_t sticksThreshold = 480;

    // Change if left stick in bottom right corner and right stick in bottom left corner
    if (throttleNeutral() &&
        isYawGreaterThan(sticksThreshold) &&
        isPitchLessThan(-sticksThreshold) &&
        isRollLessThan(-sticksThreshold) )
    {
        // TODO: add timeout

        context->setState<ArmChangeState2>(context);
    }
}




ArmChangeState2::ArmChangeState2(Context* context)
    : SticksState(context)
{
    
}

void ArmChangeState2::updateState()
{
    updateSticksValues();

    if (sticksInNeutralPos())
    {
        // TODO: add timeout

        // TODO: do some action...
        Serial.println("state changed");

        context->setState<ArmChangeState1>(context);
    }
}



