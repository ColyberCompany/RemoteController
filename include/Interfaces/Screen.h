/**
 * @file Screen.h
 * @author Jan Wielgus
 * @brief Interface for all screen implementations.
 * @date 2020-12-28
 * 
 */

#ifndef SCREEN_H
#define SCREEN_H


namespace Interfaces
{
    class Screen
    {
    public:
        virtual ~Screen() {}

        virtual bool initialize() = 0;
    };
}


#endif
