#include "MenuSelect.h"
#include "Menu.h"

MenuSelect::MenuSelect(char const * label, char const** options, uint8_t optionCount): MenuItem(label)
{
    _options = options;
    _optionCount = optionCount;
    value=0;
}

MenuSelect::MenuSelect(MenuItem* parent, char const * label, char const** options, uint8_t optionCount): MenuItem(parent, label)
{
    _options = options;
    _optionCount = optionCount;
    value=0;
}

uint8_t MenuSelect::_curValue=0;

void MenuSelect::update(uint8_t action, uint64_t ms)
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
                if (_curValue<_optionCount-1)
                {
                    _curValue++;
                }

            }
            else if (action==MENU_ACTION_UP)
            {
                if (_curValue>0)
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
        Menu::display->print(Menu::display->getCols()/2, (uint8_t)1, label,DISPLAY_ALIGN_CENTER);
        redrawRequired = false;
        refreshValue = true;
    }

    if (refreshValue)
    {
        Menu::display->print(Menu::display->getCols()/2, (uint8_t)0, *(_options+_curValue),DISPLAY_ALIGN_CENTER,8);
        return;
    }


    if (_editState)
    {
        uint64_t elapsed = ms-_lastBlink;

        if (_blinkState && elapsed>700 || !_blinkState && elapsed>200)
        {
            _blinkState=!_blinkState;
            _lastBlink = ms;

            if (_blinkState)
            {
                Menu::display->print(Menu::display->getCols()/2, (uint8_t)0, *(_options+_curValue),DISPLAY_ALIGN_CENTER,8);
            }
            else
            {
                 Menu::display->print(Menu::display->getCols()/2, (uint8_t)0, "",DISPLAY_ALIGN_CENTER,8);
            }
        }
    }
}
