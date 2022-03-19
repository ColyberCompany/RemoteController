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

#include "Common/ControlSticks.h"
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
    
// helper sticks checks:

    /**
     * @return true if throttle value = 0;
     */
    bool throttleNeutral() const;

    /**
     * @return true if all stick values = 0.
     */
    bool sticksInNeutralPos() const;

    /**
     * @return true if value >= min && value <= max.
     */
    static bool isWithinRange(int16_t value, int16_t min, int16_t max);

    bool isThrottleGreaterThan(int16_t value) const;
    bool isThrottleLessThan(int16_t value) const;
    bool isYawGreaterThan(int16_t value) const;
    bool isYawLessThan(int16_t value) const;
    bool isPitchGreaterThan(int16_t value) const;
    bool isPitchLessThan(int16_t value) const;
    bool isRollGreaterThan(int16_t value) const;
    bool isRollLessThan(int16_t value) const;
};


#endif
