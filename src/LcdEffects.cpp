#include "LcdEffects.h"
#include "BaseDisplay.h"
#include "BaseEffect.h"
#include "BlinkEffect.h"
#include<stdio.h>
#include <string.h>

LcdEffects::LcdEffects(BaseDisplay* display): _display(*display)
{
    _lines = _display.getLines();
    _cols = _display.getLines();
    _effects = new BaseEffect**[_lines];

    for (uint8_t i=0;i<_lines;i++)
    {
        _effects[i] = new BaseEffect*[_cols];
    }
}

void LcdEffects::blink(uint8_t x, uint8_t y, char* str)
{
    _display.print(x,y,str);
    BlinkEffect bl(&x,&y,str);

    for (uint8_t i=x;i<strlen(str);i++)
    {
        if (i>=_cols)
        {
            bl.length=i-x;
            break;
        }

        BaseEffect* uu = _effects[i][y];
        if (uu)
        {
_effects[i][y]=NULL;        }


    }
}
