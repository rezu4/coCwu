#ifndef WINDOWSDISPLAY_H
#define WINDOWSDISPLAY_H

#include <BaseDisplay.h>


class WindowsDisplay : public BaseDisplay
{
    public:
        WindowsDisplay(uint8_t lines, uint8_t cols);

        virtual void print(uint8_t x, uint8_t y, const char str[]);
        virtual void clearLine(uint8_t x, uint8_t y);
        virtual uint8_t getLines();
        virtual uint8_t getCols();

    protected:

    private:
        uint8_t _x;
        uint8_t _y;
        uint8_t lines;
        uint8_t cols;
};

#endif // WINDOWSDISPLAY_H
