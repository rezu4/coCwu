#include "Menu.h"
#include <cstddef>
#include "BaseDisplay.h"

Menu::Menu(char const * label): MenuItem(label)
{
}

Menu::Menu(MenuItem* parent, char const * label): MenuItem(parent, label)
{
}

MenuItem* Menu::currentMenu = NULL;
BaseDisplay* Menu::display = NULL;

void Menu::setItems( MenuItem** items, uint8_t items_count)
{
    _items = items;
    _items_count = items_count;

    _currentItem=0;
    _currentDisplayLine=250;
}

void Menu::update(uint8_t action, uint64_t ms)
{
    if (action==0)
    {
        updateBlink(ms);
        return;
    }

    if (action==MENU_ACTION_ENTER)
    {
        Menu::currentMenu = *(_items+_currentItem);
        Menu::currentMenu->redraw();
        Menu::currentMenu->update(MENU_ACTION_NONE, ms);
        return;
    }

    if (action==MENU_ACTION_ESC)
    {
        Menu::currentMenu = parent;
        if (Menu::currentMenu)
        {
            Menu::currentMenu->redraw();
            Menu::currentMenu->update(MENU_ACTION_NONE, ms);
        }

        return;
    }

    if (action==MENU_ACTION_DOWN)
    {
        if (_currentItem<_items_count-1)
        {
            refresh(_currentDisplayLine++, _currentItem++);
        }
    }
    else if (action==MENU_ACTION_UP)
    {
        if (_currentItem>0)
        {
            refresh(_currentDisplayLine--, _currentItem--);
        }
    }
    else if (_currentDisplayLine>200)
    {
        refresh(_currentDisplayLine, _currentItem);
    }

    updateBlink(ms);
}

void Menu::refresh(uint8_t prevDisplayLine, uint8_t prevItem)
{
    uint8_t newDisplayLine = _currentDisplayLine;
    uint8_t lines = Menu::display->getLines();

    if (_currentDisplayLine>200)
    {
        newDisplayLine=0;
    }
    else if (_currentDisplayLine==255)
    {
        newDisplayLine=0;
    }
    else if (_currentDisplayLine>=lines)
    {
        newDisplayLine=lines-1;
    }

    if (newDisplayLine != _currentDisplayLine)
    {
        _currentDisplayLine = newDisplayLine;
       redraw();
    }

    if (prevDisplayLine!=_currentDisplayLine)
    {
        if (_blinkState==0)
        {
            MenuItem* item = *(_items+prevItem);
            Menu::display->print(0, prevDisplayLine,item->getLabel());
        }
    }
}

void Menu::redraw()
{
    uint8_t menuIdx;
    uint8_t lines = Menu::display->getLines();

    for (uint8_t i=0;i<lines;i++)
    {
        Menu::display->clearLine(0,i);
        menuIdx=_currentItem-_currentDisplayLine + i;
        if (menuIdx<_items_count)
        {
            MenuItem* item = *(_items+menuIdx);
            Menu::display->print(0,i,item->getLabel());
        }
    }
}

void Menu::updateBlink(uint64_t ms)
{
    if (_blinkState && ms-_lastBlink>700 || !_blinkState && ms-_lastBlink>200)
    {
        _blinkState=!_blinkState;
        _lastBlink = ms;

        MenuItem* item = *(_items+_currentItem);
        if (_blinkState)
        {
            Menu::display->print(0,_currentDisplayLine,item->getLabel());
        }
        else {
            Menu::display->clearLine(0,_currentDisplayLine);
        }
    }
}
