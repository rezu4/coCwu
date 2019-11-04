#include <iostream>
#include "rlutil.h"

#include "WindowsDisplay.h"
#include "Menu.h"
#include "MenuInt.h"
#include "MenuSelect.h"

#include "arduino_pollyfils.h"
using namespace std;


WindowsDisplay windows_lcd_display(2,16);
BaseDisplay& menu_display = windows_lcd_display;

bool getInput(char *c)
{
    if (kbhit())
    {
         *c = getch();
         return true; // Key Was Hit
    }
	return false; // No keys were pressed
}

int main()
{

    char keyPress;
    uint8_t specialChar=0;
    uint8_t action=0;
    //Sleep(5000);
    Menu main("main");

    MenuInt mi(&main, "int example",10,50,"[C]");
    char const * selectOptions[] = {"select1", "s2", "select3"};

    MenuSelect ms(&main,9"select ex",selectOptions, 3);

    Menu::currentMenu = &main;
    //Menu::currentMenu = &ms;

    Menu::display = &windows_lcd_display;

    Menu o1(&main,"option1");
    Menu o11(&main,"option11");
    Menu o12(&main,"option12");
    Menu o13(&main,"option13");
    MenuItem* o1tems[] = {&o11, &o12, &o13};
    o1.setItems(o1tems, sizeof(o1tems)/sizeof(MenuItem*));

    Menu o2(&main,"option2");
    Menu o3(&main,"option3");
    Menu o4(&main,"option4");
    MenuItem* mainItems[] = {&o1, &mi, &ms, &o2, &o3, &o4};


    main.setItems(mainItems, sizeof(mainItems)/sizeof(MenuItem*));
    do{
        action=0;
        if (getInput(&keyPress))
        {
            uint8_t key = (uint8_t)keyPress;
            if (key==224)
            {
                specialChar = 1;
                continue;
            }

            if (specialChar)
            {
                specialChar=0;

                if (key==80)
                {
                   action= MENU_ACTION_DOWN;
                }
                else if (key==72)
                {
                    action= MENU_ACTION_UP;
                }
            }
            else {
                if (key==27)
                {
                    action= MENU_ACTION_ESC;
                }
                else if (key==13)
                {
                    action= MENU_ACTION_ENTER;
                }
            }

        }
        Menu::currentMenu->update(action, millis());
        Sleep(100);

    } while (keyPress!='9');


    //menu_display.print(0,0,"sdfsdf");

    //display.print(1,2,"sdsdf");

   // display.print(0,0,"sdfsdf");
gotoxy(20,20);
//millis();


    return 0;
}


