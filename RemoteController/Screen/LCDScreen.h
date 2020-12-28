/**
 * @file LCDScreen.h
 * @author Jan Wielgus
 * @brief Concrete implementaiton of Screen interface
 * that use LCD screen.
 * @date 2020-12-28
 * 
 */

#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include "Interfaces/Screen.h"
#include <LiquidCrystal_I2C.h>
#include <Task.h>


class LCDScreen : public Interfaces::Screen, public Task
{
private:
    LiquidCrystal_I2C lcd;
    static const uint8_t LCD_ADDRESS = 0x3F;
    static const uint8_t Rows = 2;
    static const uint8_t Cols = 16;

    char line1[Cols];
    char line2[Cols];

public:
    LCDScreen();
    ~LCDScreen();

    bool initialize() override;
    void execute() override;
    void updateScreenData(const ScreenData& newData) override;


private:
    /**
     * @brief Put to line1 and line2 all things that won't change
     * with updateScreenData() method call. 
     */
    void fillLinesWithFixedText();

    /**
     * @brief Immediately print line1 and line2 on the screen.
     */
    void printLines();

    /**
     * @brief Update charArray with value (as text).
     * If alignLeft is true - first digit will be on position index, next digits on next indexes.
     * If alignRight is false - whole value (as text) will be placed that last digit will be on
     * position index (previous digits will be on previous indexes).
     * @param charArray String as char array.
     * @param position Index in array (placement depends on this and alignment parameter).
     * @param value Value to be placed in the char array.
     * @param alignLeft Boolean value. Check brief.
     */
    void updateCharArray(char* charArray, size_t position, int value, bool alignLeft = true);

    /**
     * @brief 
     * 
     * @param charArray 
     * @param position 
     * @param character 
     */
    void updateCharArray(char* charArray, size_t position, char character);

    /**
     * @brief Change signed value for one char that resemble the value.
     */
    char stickValToSymbolHorizontal(int16_t value);

    /**
     * @brief Change signed value for one char that resemble the value.
     */
    char stickValToSymbolVertical(int16_t value);
};


#endif
