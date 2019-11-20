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

void Menu::setCurrentMenu(MenuItem* menu)
{
  Menu::currentMenu = menu;
  menu->redrawRequired = true;
}

void Menu::setItems( MenuItem** items, uint8_t items_count)
{
    _items = items;
    _items_count = items_count;

    _currentItem=0;
    _currentDisplayLine=0;
}

void Menu::update(uint8_t action, uint64_t ms)
{
    if (redrawRequired)
    {
        redraw();
    }

    if (action==MENU_ACTION_NONE)
    {
        updateBlink(ms);
        return;
    }

    if (action==MENU_ACTION_ENTER)
    {
        MenuItem* item = *(_items+_currentItem);
        if (item->isEnabled())
        {
            Menu::setCurrentMenu(item);
            Menu::currentMenu->update(MENU_ACTION_NONE, ms);
        }
        return;
    }

    if (action==MENU_ACTION_ESC)
    {
        Menu::setCurrentMenu(parent);
        if (Menu::currentMenu)
        {
            Menu::currentMenu->update(MENU_ACTION_NONE, ms);
        }

        return;
    }

    if (action==MENU_ACTION_DOWN)
    {
        if (_currentItem<_items_count-1)
        {
            refresh(_currentDisplayLine++, _currentItem++);
            return;
        }
    }
    else if (action==MENU_ACTION_UP)
    {
        if (_currentItem>0)
        {
            refresh(_currentDisplayLine--, _currentItem--);
            return;
        }
    }
}

void Menu::refresh(uint8_t prevDisplayLine, uint8_t prevItem)
{
    uint8_t newDisplayLine = _currentDisplayLine;
    uint8_t cols = Menu::display->getCols();

    if (_currentDisplayLine==0xFF)
    {
        newDisplayLine=0;
    }
    else if (_currentDisplayLine>=cols)
    {
        newDisplayLine=cols-1;
    }

    if (newDisplayLine != _currentDisplayLine || redrawRequired)
    {
        _currentDisplayLine = newDisplayLine;
       redraw();
    }

    if (prevDisplayLine!=_currentDisplayLine)
    {
        if (_blinkState==0)
        {
            _blinkState=1;
            MenuItem* item = *(_items+prevItem);
            Menu::display->print(0, prevDisplayLine,item->getLabel(),DISPLAY_ALIGN_LEFT,0xFF);
        }
    }
}

void Menu::redraw()
{
    uint8_t menuIdx;
    uint8_t cols = Menu::display->getCols();

    for (uint8_t i=0;i<cols;i++)
    {
        menuIdx=_currentItem-_currentDisplayLine + i;

        if (menuIdx<_items_count)
        {
            MenuItem* item = *(_items+menuIdx);
            Menu::display->print(0,i,item->getLabel(),DISPLAY_ALIGN_LEFT,0xFF);

            char const * labelExt = item->getLabelExt();
            if (labelExt!=NULL)
            {
                Menu::display->print(Menu::display->getLines()-1, i, labelExt, DISPLAY_ALIGN_RIGHT);
            }
        }
        else {
            Menu::display->clearLine(i);
        }
    }

    redrawRequired = false;
}

void Menu::updateBlink(uint64_t ms)
{
    uint64_t elapsed = ms-_lastBlink;

    if ((_blinkState && elapsed>700) || (!_blinkState && elapsed>200))
    {
        _blinkState=!_blinkState;
        _lastBlink = ms;

        MenuItem* item = *(_items+_currentItem);

        if (_blinkState)
        {
            Menu::display->print(0,_currentDisplayLine,item->getLabel(),DISPLAY_ALIGN_LEFT,0xFF);
            char const * labelExt = item->getLabelExt();
            if (labelExt!=NULL)
            {
                Menu::display->print(Menu::display->getLines()-1, _currentDisplayLine, labelExt, DISPLAY_ALIGN_RIGHT);
            }
        }
        else {
            Menu::display->clearLine(_currentDisplayLine);
        }
    }
}
