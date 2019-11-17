#include "MenuCheck.h"
#include "Menu.h"
#include <cstring>

char const *  MenuCheckSelected = "*";

MenuCheck::MenuCheck(char const * label): MenuItem(label)
{
    value=false;
}

MenuCheck::MenuCheck(MenuItem* parent, char const * label): MenuItem(parent, label)
{
    value=false;
}

bool MenuCheck::_curValue=false;

void MenuCheck::update(uint8_t action, uint64_t ms)
{
    value = !value;
    Menu::setCurrentMenu(parent);

    if (Menu::currentMenu)
    {
        Menu::currentMenu->update(MENU_ACTION_NONE, ms);
    }
}

const char* MenuCheck::getLabelExt()
{
 if (value)
 {
     return MenuCheckSelected;
 }

 return NULL;
}
