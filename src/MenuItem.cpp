#include "MenuItem.h"

MenuItem::MenuItem(MenuItem* parent, char const* label)
{
    this->parent = parent;
    this->label = label;
}

MenuItem::MenuItem(char const* label)
{
    this->label = label;
}

const char* MenuItem::getLabel()
{
    return label;
}

