#ifndef LCDEFFECTS_H
#define LCDEFFECTS_H

#include "BaseDisplay.h"
#include "BaseEffect.h"

class LcdEffects
{
    public:
        LcdEffects( BaseDisplay* display);
        void blink(uint8_t x, uint8_t y, char* str);

    protected:

    private:
        BaseDisplay& _display;
        BaseEffect*** _effects;
        uint8_t _lines;
        uint8_t _cols;
};

#endif // LCDEFFECTS_H
