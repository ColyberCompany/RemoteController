/**
 * @file ArmingStates.h
 * @author Jan Wielgus
 * @brief All states needed for changing arming state (arming and disarming).
 * @date 2021-01-27
 * 
 */

#ifndef ARMINGSTATES_H
#define ARMINGSTATES_H

#include "SticksState.h"


class WaitingForNeutralSticksState : public SticksState
{
public:
    WaitingForNeutralSticksState(Context* context);

private:
    void updateState() override;
};


class ArmChangeState1 : public SticksState
{
    uint32_t stateStartTime_ms;
    const uint32_t Timeout_ms = 1000;
    const uint16_t sticksThreshold = 480;

public:
    ArmChangeState1(Context* context);

private:
    void entryEvent() override;
    void updateState() override;
};


class ArmChangeState2 : public SticksState
{
    uint32_t stateStartTime_ms;
    const uint32_t Timeout_ms = 2000;

public:
    ArmChangeState2(Context* context);

private:
    void entryEvent() override;
    void updateState() override;
};


#endif
