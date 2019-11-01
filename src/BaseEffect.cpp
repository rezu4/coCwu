#include "BaseEffect.h"
#include "string.h"

BaseEffect::BaseEffect(uint8_t* x, uint8_t* y, char* text)
{
    _x=x;
    _y=y;
    _text=text;
    length=strlen(text);

}
