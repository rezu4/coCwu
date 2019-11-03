#ifndef MENUINT_H
#define MENUINT_H

#include <MenuItem.h>


class MenuInt : public MenuItem
{
    public:
        MenuInt();
        MenuInt(char const * label, uint16_t min, uint16_t max, char const * unit);
        MenuInt(MenuItem* parent, char const * label, uint16_t min, uint16_t max, char const * unit);
        virtual void update(uint8_t action, uint64_t ms);
        uint16_t value;

    protected:

    private:
        char const * _unit;
        uint16_t _minValue;
        uint16_t _maxValue;
        uint64_t _lastBlink;
        uint8_t _blinkState=1;
        uint8_t _editState=0;
        char _template[10];
        uint16_t _curValue;
};

#endif // MENUINT_H
