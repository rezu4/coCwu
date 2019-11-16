#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include "BaseDisplay.h"
#include <LiquidCrystal_I2C.h>

class LcdDisplay : public BaseDisplay
{
    public:
        LcdDisplay(LiquidCrystal_I2C *lcd, uint8_t lines, uint8_t cols);

        virtual void print(uint8_t x, uint8_t y, const char str[], uint8_t align = 0, uint8_t lineWidth=0);
        virtual void clearLine(uint8_t y);
        virtual uint8_t getLines();
        virtual uint8_t getCols();
		void begin();

    protected:

    private:
        LiquidCrystal_I2C* _lcd;
        uint8_t lines;
        uint8_t cols;
        char _template[32];
};

#endif // LCDDISPLAY_H
