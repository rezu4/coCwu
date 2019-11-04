#ifndef MENUSELECT_H
#define MENUSELECT_H

#include <MenuItem.h>


class MenuSelect : public MenuItem
{
    public:
        MenuSelect(char const * label, char const ** options, uint8_t optionCount);
        MenuSelect(MenuItem* parent, char const * label, char const ** options, uint8_t optionCount);
        uint8_t value;
        virtual void update(uint8_t action, uint64_t ms);

    protected:

    private:
        char const ** _options;
        uint8_t _optionCount;
        static uint8_t _curValue;
};

#endif // MENUSELECT_H
