#ifndef WINDOWSDISPLAY_H
#define WINDOWSDISPLAY_H

#include <BaseDisplay.h>


class WindowsDisplay : public BaseDisplay
{
    public:
        WindowsDisplay(uint8_t lines, uint8_t cols);

        virtual void print(uint8_t x, uint8_t y, const char str[], uint8_t align = 0, uint8_t lineWidth=0);
        virtual void clearLine(uint8_t y);
        virtual uint8_t getLines();
        virtual uint8_t getCols();

    protected:

    private:
        uint8_t _x;
        uint8_t _y;
        uint8_t lines;
        uint8_t cols;
        char _template[32];
};

#endif // WINDOWSDISPLAY_H
