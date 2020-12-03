/**
 * @file LCD.cpp
 * @author Jan Wielgus
 * @date 2020-12-02
 * 
 */

#include "LCD.h"


LCD::LCD()
    : lcd(LCD_ADDRESS, 16, 2)
{
    line1 = new char[16];
    line2 = new char[16];
}


LCD::~LCD()
{
    delete[] line1;
    delete[] line2;
}


bool LCD::initialize()
{
    lcd.init(); // Wire.begin() is here
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print("Colyber");
	lcd.setCursor(0, 1);
	lcd.print("RemoteController");
	delay(400);
	lcd.clear();

    updateLinesWithStaticParts();
}


void LCD::update(const ScreenValues& newValues)
{
    updateLinesWithNewValues(newValues);
    printLines();
}


void LCD::updateLinesWithStaticParts()
{
    
}


void LCD::updateLinesWithNewValues(const ScreenValues& newValues)
{
    lcd.clear();
    lcd.print(newValues.stickThrottle);
}


void LCD::printLines()
{
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}


char LCD::stickValToSymbolHorizontal(int16_t value)
{
    if (value > 0)
		return '>';
	if (value < 0)
		return '<';
	return '|';
}


char LCD::stickValToSymbolVertical(int16_t value)
{
    if (value > 0)
        return '^';
    if (value < 0)
        return 'v';
    return '-';
}

