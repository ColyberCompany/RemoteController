/**
 * @file utils.h
 * @author Jan Wielgus
 * @brief Some useful functinos.
 * @date 2021-01-27
 * 
 */

#ifndef UTILS_H
#define UTILS_H


namespace Utils
{
    template <class T>
    void swap(T& first, T& second)
    {
        T temp = first;
        first = second;
        second = temp;
    }
}


#endif
