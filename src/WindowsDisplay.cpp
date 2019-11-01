#include "WindowsDisplay.h"
#include<stdio.h>
#include "rlutil.h"

WindowsDisplay::WindowsDisplay(uint8_t lines, uint8_t cols): BaseDisplay(lines, cols)
{
    this->lines = lines;
    this->cols = cols;
    _x=10;
    _y=10;

    for (int i = 0; i < cols+2; i++)
    {
        gotoxy(_x-1+i, _y-1);
        printf("_");
        gotoxy(_x-1+i, _y+lines);
        printf("_");
    }

    for (int i = 0; i < lines; i++)
    {
        gotoxy(_x-1, _y+i);
        printf("|");

        gotoxy(_x+cols, _y+i);
        printf("|");
    }
}

 void WindowsDisplay:: print(uint8_t x, uint8_t y, const char str[])
 {
    gotoxy(_x+x, _y+y);
    printf(str);
 }

uint8_t WindowsDisplay:: getLines()
{
    return lines;
}

uint8_t WindowsDisplay:: getCols()
{
    return cols;
}

void WindowsDisplay::clearLine(uint8_t x, uint8_t y)
{
    gotoxy(_x+x, _y+y);
    printf("                 ");
}
