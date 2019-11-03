#ifndef BASEDISPLAY_H
#define BASEDISPLAY_H
#include <inttypes.h>

const uint8_t DISPLAY_ALIGN_LEFT=0;
const uint8_t DISPLAY_ALIGN_RIGHT=1;
const uint8_t DISPLAY_ALIGN_CENTER=2;
class BaseDisplay
{
    public:
        BaseDisplay(uint8_t lines, uint8_t cols);
        virtual void print(uint8_t x, uint8_t y, const char str[], uint8_t align = 0, uint8_t lineWidth=0)=0;
        virtual void clearLine(uint8_t y)=0;
        virtual uint8_t getLines()=0;
        virtual uint8_t getCols()=0;


    protected:

    private:
};

#endif // BASEDISPLAY_H
