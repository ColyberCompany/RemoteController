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


class ArmChangeState1 : public SticksState
{
public:
    ArmChangeState1(Context* context);

private:
    //bool sticksAreWithinThreshold();
    void updateState() override;
};


class ArmChangeState2 : public SticksState
{
public:
    ArmChangeState2(Context* context);

private:
    void updateState() override;
};


#endif
