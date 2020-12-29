/**
 * @file LCDScreen.cpp
 * @author Jan Wielgus
 * @date 2020-12-28
 * 
 */

#include "../Screen/LCDScreen.h"

 
LCDScreen::LCDScreen()
    : lcd(LCD_ADDRESS, Cols, Rows)
{
    for (int i=0; i < Cols; i++)
    {
        line1[i] = 'a';
        line2[i] = 'a';
    }

    line1[Cols] = '\n';
    line2[Cols] = '\n';
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


uint8_t LCDScreen::getLastDigit(int number)
{
    return abs(number) % 10;
}


uint8_t LCDScreen::getDigitsAmount(int number)
{
    uint8_t digitsCounter = 1;
    while (number != 0)
    {
        digitsCounter++;
        number /= 10;
    }
    return digitsCounter;
}


void LCDScreen::updateCharArray(char* charArray, size_t position, int value, bool alignLeft = true)
{
    if (alignLeft)
        updateCharArray(charArray, position + getDigitsAmount(value), value, false);
    else
    {
        int temp = value; // TODO: figure out better name
        int index = position;
        do
        {
            charArray[index] = getLastDigit(temp) + '0';
            temp / 10;
            index--;
        } while (temp != 0);
    }
}


void LCDScreen::updateCharArray(char* charArray, size_t position, char character)
{
    charArray[position] = character;
}


void LCDScreen::updateCharArray(char* charArray, size_t position, const char* text)
{
    for (size_t i = 0; text[i] != '\n'; i++)
        charArray[position + i] = text[i];
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

