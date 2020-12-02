/**
 * @file LCD.h
 * @author Jan Wielgus
 * @brief Class for LCD screen handling.
 * @date 2020-12-02
 * 
 */

#ifndef LCD_H
#define LCD_H

#include "Interfaces/IScreen.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>


class LCD : public IScreen
{
private:
    LiquidCrystal_I2C lcd;
    static const uint8_t LCD_ADDRESS = 0x3F;

    char* line1;
    char* line2;

public:
    LCD();
    ~LCD();

    bool initialize() override;
    void update(const ScreenValues& newValues) override;


private:
    void updateLinesWithStaticParts();
    void updateLinesWithNewValues();
    void printLines();



    /**
     * @brief Change signed value for one char that resemble the value.
     */
    char stickValToSymbolHorizontal(int16_t value);

    /**
     * @brief Change signed value for one char that resemble the value.
     */
    char stickValToSymbolVertical(int16_t value);

    /*
    void intToSizedString(String& outString, int16_t value, uint8_t length); // eg. value = 15, length = 4  ->  output: "  15"
	String intToSizedString(int16_t value, uint8_t length); // eg. value = 15, length = 4  ->  output: "  15"
    */
};


#endif

