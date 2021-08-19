/**
 * @file LCDScreen.cpp
 * @author Jan Wielgus
 * @date 2020-12-28
 * 
 */

#include "../Screen/LCDScreen.h"
#include "../Instances.h"
#include "../Communication/CommData.h"


const char LCDScreen::FlightModesLabels[][5] = {"||||", "stab", "alth", "posh"};
const char* const LCDScreen::UnknownFlightModeLabel = "unk!";

 
LCDScreen::LCDScreen()
    : lcd(LCD_ADDRESS, Cols, Rows)
{
    for (int i=0; i < Cols; i++)
    {
        line1[i] = ' ';
        line2[i] = ' ';
    }

    line1[Cols] = '\0';
    line2[Cols] = '\0';
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

    return true;
}


void LCDScreen::execute()
{
    updateLines();
    printLines();
}


void LCDScreen::updateLines()
{
    using Instance::measurementsManager;
    using Enums::MeasurementType;

    updateText(line1, 0, ' ', 3); // clear old throttle value
    updateText(line1, 0, (int16_t)measurementsManager.getMeasurement(MeasurementType::ThrottleStick) / 10);
    updateText(line1, 3, stickValToSymbolHorizontal(measurementsManager.getMeasurement(MeasurementType::YawStick)));
    updateText(line1, 4, stickValToSymbolVertical(measurementsManager.getMeasurement(MeasurementType::PitchStick)));
    updateText(line1, 5, stickValToSymbolHorizontal(measurementsManager.getMeasurement(MeasurementType::RollStick)));

    // drone angles
    updateText(line1, 7, ' ', 3);
    updateText(line1, 7, commData.drone.pitchAngle_deg);

    updateText(line1, 12, boolStateToSymbol(measurementsManager.getMeasurement(MeasurementType::LeftSwitch)));
    updateText(line1, 13, boolStateToSymbol(measurementsManager.getMeasurement(MeasurementType::RightSwitch)));

    updateText(line1, 15, boolStateToSymbol(measurementsManager.getMeasurement(MeasurementType::ESP8266WiFiState)));

    auto curFlightMode = Instance::remoteControllerManager.getCurrentFlightModeType();
    switch (curFlightMode)
    {
        case Enums::FlightModeTypes::UNARMED:
        case Enums::FlightModeTypes::STABILIZE:
        case Enums::FlightModeTypes::ALT_HOLD:
        case Enums::FlightModeTypes::POS_HOLD:
            updateText(line2, 0, FlightModesLabels[(int)curFlightMode]);
            break;
        default:
            updateText(line2, 0, UnknownFlightModeLabel);
    }

    // update other data here...
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
    if (number == 0)
        return 1;

    uint8_t digitsCounter = 0;
    while (number != 0)
    {
        digitsCounter++;
        number /= 10;
    }
    return digitsCounter;
}


uint16_t LCDScreen::getTextLength(const char* text)
{
    uint16_t length = 0;
    while (text[length] != '\0')
        ++length;
    return length;
}


void LCDScreen::updateText(char* outputText, size_t position, int value, bool alignLeft)
{
    // TODO: protect against going beyond outputText last char
    if (outputText == nullptr)
        return;

    if (alignLeft)
    {
        size_t newPosition = position + getDigitsAmount(value) - (value<0 ? 0 : 1);
        updateText(outputText, newPosition, value, false);
    }
    else
    {
        int temp = value; // TODO: figure out better name
        int index = position;
        do
        {
            char charDigit = getLastDigit(temp) + '0';
            outputText[index] = charDigit;
            temp /= 10;
            index--;
        } while (temp != 0 && index >= 0);

        if (value < 0 && index >= 0)
            outputText[index] = '-';
    }
}


void LCDScreen::updateText(char* outputText, size_t position, char character, int howManyTimes)
{
    if (outputText == nullptr)
        return;

    for (size_t i = 0; i < howManyTimes && outputText[position + i] != '\0'; i++)
        outputText[position + i] = character;
}


void LCDScreen::updateText(char* outputText, size_t position, const char* text)
{
    if (outputText == nullptr)
        return;

    if (text == nullptr)
        return;

    for (size_t i = 0; text[i] != '\0' && text[position + i] != '\0'; i++)
        outputText[position + i] = text[i];
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


char LCDScreen::boolStateToSymbol(bool state)
{
    return state ? 255 : '_';
}

