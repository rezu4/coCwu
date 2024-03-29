#include "MenuItem.h"
#include <cstddef>

MenuItem::MenuItem(MenuItem* parent, char const* label)
{
    this->parent = parent;
    this->label = label;
    this->labelExt = NULL;
}

uint8_t MenuItem::_blinkState=1;
uint64_t MenuItem::_lastBlink=0;
char MenuItem::_template[24];
bool MenuItem::_editState = false;

MenuItem::MenuItem(char const* label)
{
    this->label = label;
}

const char* MenuItem::getLabel()
{
    return label;
}

const char* MenuItem::getLabelExt()
{
    return labelExt;
}

bool  MenuItem::isEnabled()
{
    return true;
}


