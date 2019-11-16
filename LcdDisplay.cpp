#include "LcdDisplay.h"
#include <cstring>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LcdDisplay::LcdDisplay(LiquidCrystal_I2C *lcd, uint8_t lines, uint8_t cols): BaseDisplay(lines, cols)
{
	_lcd = lcd;
    this->lines = lines;
    this->cols = cols;
	
}

void LcdDisplay::begin()
{
	_lcd->begin(D2,D1);  
	_lcd->backlight();
}

 void LcdDisplay:: print(uint8_t x, uint8_t y, const char str[], uint8_t align, uint8_t lineWidth)
 {
    uint8_t l = strlen(str);
    if (lineWidth>cols)
    {
        lineWidth=cols;
    }

    uint8_t i;
    uint8_t textPos=0;
    uint8_t tbeg=0;
    uint8_t tend=0;

    for (i=0;i<cols;i++)
    {
        _template[i] = ' ';
    }

    _template[cols+1]=char(0);

    if (align==DISPLAY_ALIGN_LEFT)
    {
        textPos = tbeg = x;
        tend=x+ l;

        if (lineWidth>l)
        {
            tend=x + lineWidth;
        }
    }
    else if (align==DISPLAY_ALIGN_RIGHT)
    {
        textPos = tbeg = x-l+1;
        tend=x;
        if (lineWidth>l)
        {
            tbeg = x-lineWidth+1;
        }
    }
    else if (align==DISPLAY_ALIGN_CENTER)
    {
        textPos = tbeg=x-l/2;
        tend=tbeg+l;

        if (lineWidth>l)
        {
            tbeg = x-lineWidth/2;
            tend=tbeg+lineWidth;
        }
    }

    for (i=0;i<l;i++)
    {
        _template[textPos+i]=str[i];
    }

    _template[tend+1]=(char)0;

	_lcd->setCursor(tbeg, y);
	_lcd->print(_template+tbeg);
 }

uint8_t LcdDisplay:: getLines()
{
    return lines;
}

uint8_t LcdDisplay:: getCols()
{
    return cols;
}

void LcdDisplay::clearLine(uint8_t y)
{
    print(0,y," ",DISPLAY_ALIGN_LEFT, cols);
}
