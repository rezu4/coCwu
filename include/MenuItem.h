#ifndef MENUITEM_H
#define MENUITEM_H
#include <inttypes.h>

const uint8_t MENU_ACTION_NONE=0;
const uint8_t MENU_ACTION_UP=1;
const uint8_t MENU_ACTION_DOWN=2;
const uint8_t MENU_ACTION_ENTER=3;
const uint8_t MENU_ACTION_ESC=4;

class MenuItem
{
    public:
        MenuItem(char const * label);
        MenuItem(MenuItem* parent, char const * label);
        MenuItem* parent;
        char const * label;
        uint8_t idx;
        virtual const char* getLabel();
        virtual void update(uint8_t action, uint64_t ms) =0;
        virtual void redraw()=0;
    protected:

    private:
};

#endif // MENUITEM_H
