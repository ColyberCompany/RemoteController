/**
 * @file LCDScreen.cpp
 * @author Jan Wielgus
 * @date 2020-12-28
 * 
 */

#include "Screen/LCDScreen.h"


LCDScreen::LCDScreen()
    : lcd(LCD_ADDRESS, Cols, Rows)
{
    for (int i=0; i < Cols; i++)
    {
        line1[i] = ' ';
        line2[i] = ' ';
    }
}


LCDScreen::~LCDScreen()
{
}


bool LCDScreen::initialize()
{
    lcd.init(); // Wire.begin() is here
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Colyber");
    lcd.setCursor(0, 1);
    lcd.print("RemoteController");
    delay(400);
    lcd.clear();

    fillLinesWithFixedText();
}


void LCDScreen::execute()
{
    printLines();
}


void LCDScreen::updateScreenData(const ScreenData& newData)
{
    // TODO: update line1 and line2 directly, don't store newData copy
}


void LCDScreen::fillLinesWithFixedText()
{
    // TODO: fill with fixed text
}


void LCDScreen::printLines()
{
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}


char LCDScreen::stickValToSymbolHorizontal(int16_t value)
{
    if (value > 0)
		return '>';
	if (value < 0)
		return '<';
	return '|';
}


char LCDScreen::stickValToSymbolVertical(int16_t value)
{
    if (value > 0)
        return '^';
    if (value < 0)
        return 'v';
    return '-';
}

