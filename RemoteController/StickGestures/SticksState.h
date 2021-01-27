/**
 * @file SticksState.h
 * @author Jan Wielgus
 * @brief Base class for all sticks states
 * (contain sticks values and updateSticksValues method inside).
 * @date 2021-01-27
 * 
 */

#ifndef STICKSSTATE_H
#define STICKSSTATE_H

#include "../Common/ControlSticks.h"
#include <State.h>


class SticksState : public State
{
protected:
    ControlSticks sticks;

public:
    SticksState(Context* context);

    virtual ~SticksState();

protected:
    void updateSticksValues();
};


#endif
