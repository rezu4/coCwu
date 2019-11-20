#include "MenuInt.h"
#include "Menu.h"
#include <cstdlib>

MenuInt::MenuInt(char const * label, uint16_t min, uint16_t max, char const * unit): MenuItem(label)
{
    _unit = unit;
    _minValue = min;
    _maxValue = max;

    if (value<min || value>max)
    {
        value = min;
    }
}

uint16_t MenuInt::_curValue=0;

MenuInt::MenuInt(MenuItem* parent, char const * label, uint16_t min, uint16_t max, char const * unit): MenuItem(parent, label)
{
    _unit = unit;
    _minValue = min;
    _maxValue = max;

    if (value<min || value>max)
    {
        value = min;
    }
}

void MenuInt::update(uint8_t action, uint64_t ms)
{
    bool refreshValue = false;

    if (action==MENU_ACTION_ENTER)
    {
        if (_editState)
        {
            value = _curValue;
        }
        else
        {
           _curValue = value;
        }
        _editState = !_editState;

        refreshValue = true;
    }
    else if (action==MENU_ACTION_ESC)
    {
        if (_editState)
        {
            _editState =false;
            _curValue = value;
            refreshValue = true;
        }
        else
        {
            Menu::setCurrentMenu(parent);
            if (Menu::currentMenu)
            {
                Menu::currentMenu->update(MENU_ACTION_NONE, ms);
            }
            return;
        }
    }
    else {
        if (_editState)
        {
            uint16_t prevValue = _curValue;

            if (action==MENU_ACTION_DOWN)
            {
                if (_curValue<_maxValue)
                {
                    _curValue++;
                }
            }
            else if (action==MENU_ACTION_UP)
            {
                if (_curValue>_minValue)
                {
                    _curValue--;
                }
            }

            refreshValue = prevValue!=_curValue;
        }
        else{
            _curValue = value;
        }
    }

    if (redrawRequired)
    {
        Menu::display->clearLine(0);
        Menu::display->clearLine(1);
        Menu::display->print(Menu::display->getLines()-1, (uint8_t)0, _unit,DISPLAY_ALIGN_RIGHT);
        Menu::display->print(Menu::display->getLines()/2, (uint8_t)1, label,DISPLAY_ALIGN_CENTER);
        redrawRequired = false;
        refreshValue = true;
    }

    if (refreshValue)
    {
        itoa(_curValue, _template, 10);
        Menu::display->print(Menu::display->getLines()/2, (uint8_t)0, _template,DISPLAY_ALIGN_CENTER,8);
        return;
    }

    if (_editState)
    {
        uint64_t elapsed = ms-_lastBlink;

        if ((_blinkState && elapsed>700) || (!_blinkState && elapsed>200))
        {
            _blinkState=!_blinkState;
            _lastBlink = ms;

            if (_blinkState)
            {
                Menu::display->print(Menu::display->getLines()/2, (uint8_t)0, _template,DISPLAY_ALIGN_CENTER,8);
            }
            else
            {
                 Menu::display->print(Menu::display->getLines()/2, (uint8_t)0, "",DISPLAY_ALIGN_CENTER,8);
            }
        }
    }
}
