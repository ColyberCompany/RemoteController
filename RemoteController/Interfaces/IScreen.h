/**
 * @file IScreen.h
 * @author Jan Wielgus
 * @brief Common interface for all screens.
 * @date 2020-12-02
 * 
 */

#ifndef ISCREEN_H
#define ISCREEN_H

#include "Common/ScreenValues.h"


class IScreen
{
public:
    ~IScreen() {}

    virtual bool initialize() = 0;
    virtual void update(const ScreenValues& newValues) = 0;
};


#endif

