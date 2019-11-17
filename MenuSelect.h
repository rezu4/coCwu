#ifndef MENUSELECT_H
#define MENUSELECT_H

#include "MenuItem.h"


class MenuSelect : public MenuItem
{
    public:
        MenuSelect(char const * label, char const ** options, uint8_t optionCount);
        MenuSelect(MenuItem* parent, char const * label, char const ** options, uint8_t optionCount);
        uint8_t value;
        virtual void update(uint8_t action, uint64_t ms);

    protected:

    private:
        void refresh(uint8_t prevDisplayLine, uint8_t prevItem);
        void redraw();
        void updateBlink(uint64_t ms);
        char const ** _options;
        uint8_t _optionCount;
        uint8_t _currentItem;
        uint8_t _currentDisplayLine;
};

#endif // MENUSELECT_H
