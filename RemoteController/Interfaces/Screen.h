/**
 * @file Screen.h
 * @author Jan Wielgus
 * @brief Interface for all screen implementations.
 * @date 2020-12-28
 * 
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../Common/ScreenData.h"


namespace Interfaces
{
    class Screen
    {
    public:
        virtual ~Screen() {}

        virtual bool initialize() = 0;
        virtual void updateScreenData(const ScreenData& newData) = 0;
        // virtual bool forceScreenUpdate() = 0; // TODO: think whether this method will be needed
    };
}


#endif
