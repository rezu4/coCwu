#ifndef MENUCHECK_H
#define MENUCHECK_H

#include "MenuItem.h"


class MenuCheck : public MenuItem
{
    public:
        MenuCheck(char const * label);
        MenuCheck(MenuItem* parent, char const * label);
        bool value;
        virtual void update(uint8_t action, uint64_t ms);
        virtual const char* getLabelExt();

    protected:

    private:
        static bool _curValue;
};

#endif // MENUCHECK_H
