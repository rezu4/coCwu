#ifndef MENU_H
#define MENU_H

#include <MenuItem.h>
#include <BaseDisplay.h>

class Menu : public MenuItem
{
    public:
        Menu(char const * label);
        Menu(MenuItem* parent, char const * label);
        virtual void setItems( MenuItem** items, uint8_t items_count);
        virtual void update(uint8_t action, uint64_t ms);
        static MenuItem* currentMenu;
        static void setCurrentMenu(MenuItem* menu);
        static BaseDisplay* display;

    protected:

    private:
        void refresh(uint8_t prevDisplayLine, uint8_t prevItem);
        uint8_t _currentItem;
        uint8_t _currentDisplayLine;
        uint64_t _lastBlink;
        uint8_t _blinkState=1;
        MenuItem** _items;
        uint8_t _items_count;
        void updateBlink(uint64_t ms);
        void redraw();
};

#endif // MENU_H
