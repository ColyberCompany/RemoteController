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

#include "../Interfaces/Screen.h"
#include <LiquidCrystal_I2C.h>
#include <Task.h>


class LCDScreen : public Interfaces::Screen, public Task
{
private:
    static const uint8_t LCD_ADDRESS = 0x3F;
    static const uint8_t Rows = 2;
    static const uint8_t Cols = 16;

    static const char FlightModesLabels[][5];
    static const char* const UnknownFlightModeLabel;

    LiquidCrystal_I2C lcd;

    char line1[Cols + 1];
    char line2[Cols + 1];

    ScreenData screenData;

public:
    LCDScreen();
    ~LCDScreen();

    bool initialize() override;
    void execute() override;
    ScreenData* getScreenDataPointer() override;


private:
    /**
     * @brief Update line1 and line2 textx with data from screenData.
     */
    void updateLinesFromScreenData();

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
     * @param number Any number.
     * @return Last decimal digit of passed number.
     */
    uint8_t getLastDigit(int number);

    /**
     * @param number Checked number.
     * @return How many digits this number has in decimal form.
     */
    uint8_t getDigitsAmount(int number);

    uint16_t getTextLength(const char* text);

    /**
     * @brief Update outputText with value (as text).
     * If alignLeft is true - first digit will be on position index, next digits on next indexes.
     * If alignLeft is false - whole value (as text) will be placed that last digit will be on
     * position index (previous digits will be on previous indexes).
     * @param outputText C style string.
     * @param position Index in array (placement depends on this and alignment parameter).
     * @param value Value to be placed in the char array.
     * @param alignLeft Boolean value. Check brief.
     */
    void updateText(char* outputText, size_t position, int value, bool alignLeft = true);

    /**
     * @brief Update outputText with one char.
     * @param outputText C style string.
     * @param position Index of replaced char in string.
     * @param character Character to replace.
     * @param howManyTimes eg. if 1 - only replace char at position,
     * if 2 - replace char at position and at the next position, etc.
     */
    void updateText(char* outputText, size_t position, char character, int howManyTimes = 1);

    /**
     * @brief Update outputText with whole C style string starting from position index.
     * @param outputText C style string.
     * @param position Index from where text will start in the char array
     * (remember that text have to be not too long).
     * @param text Text to be put to the outputText starting from position index
     * (have to end with '\n').
     */
    void updateText(char* outputText, size_t position, const char* text);

    /**
     * @brief Change signed value for one char that resemble the value.
     */
    char stickValToSymbolHorizontal(int16_t value);

    /**
     * @brief Change signed value for one char that resemble the value.
     */
    char stickValToSymbolVertical(int16_t value);

    /**
     * @brief Change switch state so some corresponding symbol.
     */
    char boolStateToSymbol(bool state);
};


#endif
