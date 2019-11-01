#ifndef BASEEFFECT_H
#define BASEEFFECT_H
#include <inttypes.h>


class BaseEffect
{
    public:
        BaseEffect(uint8_t* x, uint8_t* y, char* text);
        uint8_t length;

    protected:
        uint8_t* _x;
        uint8_t* _y;
        char* _text;
    private:
};

#endif // BASEEFFECT_H
