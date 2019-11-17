#include "WindowsDisplay.h"
#include <cstring>
#include "rlutil.h"

WindowsDisplay::WindowsDisplay(uint8_t lines, uint8_t cols): BaseDisplay(lines, cols)
{
    this->lines = lines;

    this->cols = cols;
    _x=10;
    _y=10;

    for (int i = 0; i < lines+2; i++)
    {
        gotoxy(_x-1+i, _y-1);
        printf("-");
        gotoxy(_x-1+i, _y+cols);
        printf("-");
    }

    for (int i = 0; i < cols; i++)
    {
        gotoxy(_x-1, _y+i);
        printf("|");

        gotoxy(_x+lines, _y+i);
        printf("|");
    }
}

 void WindowsDisplay:: print(uint8_t x, uint8_t y, const char str[], uint8_t align, uint8_t lineWidth)
 {
    uint8_t l = strlen(str);
    if (lineWidth>lines)
    {
        lineWidth=lines;
    }

    uint8_t i;
    uint8_t textPos=0;
    uint8_t tbeg=0;
    uint8_t tend=0;

    for (i=0;i<lines;i++)
    {
        _template[i] = ' ';
    }

    _template[lines+1]=char(0);

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

    gotoxy(_x+tbeg, _y+y);
    printf(_template+tbeg);

 }

uint8_t WindowsDisplay:: getLines()
{
    return lines;
}

uint8_t WindowsDisplay:: getCols()
{
    return cols;
}

void WindowsDisplay::clearLine(uint8_t y)
{
    print(0,y," ",DISPLAY_ALIGN_LEFT, lines);
}
