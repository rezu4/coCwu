#include "MenuSelect.h"
#include "Menu.h"
#include <cstring>

char const *  MenuSelectSelected = "*";

MenuSelect::MenuSelect(char const * label, char const** options, uint8_t optionCount): MenuItem(label)
{
    _options = options;
    _optionCount = optionCount;
    value=0;
     _currentItem=0;
    _currentDisplayLine=0;
}

MenuSelect::MenuSelect(MenuItem* parent, char const * label, char const** options, uint8_t optionCount): MenuItem(parent, label)
{
    _options = options;
    _optionCount = optionCount;
    value=0;
     _currentItem=0;
    _currentDisplayLine=0;
}

void MenuSelect::update(uint8_t action, uint64_t ms)
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
        value = _currentItem;
        redraw();
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
        if (_currentItem<_optionCount-1)
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

void MenuSelect::refresh(uint8_t prevDisplayLine, uint8_t prevItem)
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
            char const * option = *(_options+prevItem);
            Menu::display->print(0, prevDisplayLine,option,DISPLAY_ALIGN_LEFT,0xFF);
        }
    }
}

void MenuSelect::redraw()
{
    uint8_t optionIdx;
    uint8_t cols = Menu::display->getCols();

    for (uint8_t i=0;i<cols;i++)
    {
        optionIdx=_currentItem-_currentDisplayLine + i;

        if (optionIdx<_optionCount)
        {
            char const * option = *(_options+optionIdx);
            Menu::display->print(0,i,option, DISPLAY_ALIGN_LEFT,0xFF);

            if (value==optionIdx)
            {
                Menu::display->print(Menu::display->getLines()-1, i, MenuSelectSelected, DISPLAY_ALIGN_RIGHT);
            }
        }
        else {
            Menu::display->clearLine(i);
        }
    }

    redrawRequired = false;
}

void MenuSelect::updateBlink(uint64_t ms)
{
    uint64_t elapsed = ms-_lastBlink;

    if ((_blinkState && elapsed>700) || (!_blinkState && elapsed>200))
    {
        _blinkState=!_blinkState;
        _lastBlink = ms;

        char const * option = *(_options+_currentItem);

        if (_blinkState)
        {
            Menu::display->print(0,_currentDisplayLine,option,DISPLAY_ALIGN_LEFT,0xFF);
            if (value==_currentItem)
            {
                Menu::display->print(Menu::display->getLines()-1, _currentDisplayLine, MenuSelectSelected, DISPLAY_ALIGN_RIGHT);
            }
        }
        else {
            Menu::display->clearLine(_currentDisplayLine);
        }
    }
}
