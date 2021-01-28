/**
 * @file ArmingStates.cpp
 * @author Jan Wielgus
 * @date 2021-01-27
 * 
 */

#include "../StickGestures/ArmingStates.h"
#include <Context.h>
#include "../Instances.h"



WaitingForNeutralSticksState::WaitingForNeutralSticksState(Context* context)
    : SticksState(context)
{

}

void WaitingForNeutralSticksState::updateState()
{
    updateSticksValues();

    if (sticksInNeutralPos())
        context->setState<ArmChangeState1>(context);
}


// ------------


ArmChangeState1::ArmChangeState1(Context* context)
    : SticksState(context)
{
    
}

void ArmChangeState1::entryEvent()
{
    stateStartTime_ms = millis();
}

void ArmChangeState1::updateState()
{
    updateSticksValues(); // update sticks values before use

    if (millis() > stateStartTime_ms + Timeout_ms)
        context->setState<WaitingForNeutralSticksState>(context);

    // Change if left stick in bottom right corner and right stick in bottom left corner
    if (throttleNeutral() &&
        isYawGreaterThan(sticksThreshold) &&
        isPitchLessThan(-sticksThreshold) &&
        isRollLessThan(-sticksThreshold) )
    {
        context->setState<ArmChangeState2>(context);
    }
}


// ------------


ArmChangeState2::ArmChangeState2(Context* context)
    : SticksState(context)
{
    
}

void ArmChangeState2::entryEvent()
{
    stateStartTime_ms = millis();
}

void ArmChangeState2::updateState()
{
    updateSticksValues();

    if (millis() > stateStartTime_ms + Timeout_ms)
        context->setState<WaitingForNeutralSticksState>(context);

    if (sticksInNeutralPos())
    {
        // <<<< There is a arming changing action >>>>
        changeArmState();

        context->setState<WaitingForNeutralSticksState>(context);
    }
}

void ArmChangeState2::changeArmState()
{
    using Instance::remoteControllerManager;
    if (remoteControllerManager.isArmed())
        remoteControllerManager.setDisarmed();
    else
        remoteControllerManager.setArmed();
}



