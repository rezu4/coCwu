#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include "MenuItem.h"
#include "Menu.h"
#include "MenuInt.h"
#include "MenuSelect.h"
#include "MenuCheck.h"
#include "LcdDisplay.h"
#include <LiquidCrystal_I2C.h>

Adafruit_MCP23017 mcp;

byte arduinoIntPin = D7;

void ICACHE_RAM_ATTR intCallBack();
byte mcpPinA = 9;  // PORT-A
byte mcpPinB = 10;
byte mcpPinRotary1 = 11;
byte mcpPinRotary2 = 12;

byte mcpLed1 = 0; // PORT-B
byte mcpLed2 = 1;
byte mcpLed3 = 2;
byte mcpLed4 = 3;
bool ledState2 = LOW;

// ISR
volatile boolean isrHandled = true;



// rotary
uint8_t rotaryEncodeLineAPrev = HIGH;
uint8_t rotaryEncoderPos = 0;

// buttons
uint8_t buttonEnterPrev = HIGH;
uint8_t buttonEscPrev = HIGH;

LiquidCrystal_I2C lcd(0x27,16,2); // Check I2C address of LCD, normally 0x27 or 0x3F
LcdDisplay lcdDisplay(&lcd, 16,2);

// current menu action
uint8_t menu_action = MENU_ACTION_NONE;

Menu main("main");
MenuInt mi(&main, "int example",10,50,"[C]");

char const * selectOptions[] = {"select1", "s2", "select3"};
MenuSelect ms(&main,"select ex",selectOptions, 3);

Menu o1(&main,"option1");
Menu o11(&main,"option11");
Menu o12(&main,"option12");
Menu o13(&main,"option13");
MenuItem* o1tems[] = {&o11, &o12, &o13};

MenuCheck mc1(&main,"check1 ex");

MenuItem* mainItems[] = { &mi, &mc1, &o1, &ms};


void setup()
{ 
   lcdDisplay.begin();
   main.setItems(mainItems, sizeof(mainItems)/sizeof(MenuItem*));
   o1.setItems(o1tems, sizeof(o1tems)/sizeof(MenuItem*));
Menu::currentMenu = &main;
Menu::display = &lcdDisplay;

//lcd.begin(D2, D1);
//lcd.backlight();
  
 
  Serial.begin(115200); // to view on Serial monitor
  Serial.println("MCP23007 Interrupt Test with RE");

  

  pinMode(arduinoIntPin, INPUT);

  mcp.begin();  // use default address 0
  mcp.setupInterrupts(false, false, LOW); // The mcp output interrupt pin.

  mcp.pinMode(mcpPinA, INPUT);
  mcp.pullUp(mcpPinA, HIGH);  // turn on a 100K pullup internally
  mcp.setupInterruptPin(mcpPinA, CHANGE);

  mcp.pinMode(mcpPinB, INPUT);
  mcp.pullUp(mcpPinB, HIGH);  // turn on a 100K pullup internally
  mcp.setupInterruptPin(mcpPinB, CHANGE);

  mcp.pinMode(mcpPinRotary1, INPUT);
  mcp.pullUp(mcpPinRotary1, HIGH);  // turn on a 100K pullup internally
  mcp.setupInterruptPin(mcpPinRotary1, CHANGE);

  mcp.pinMode(mcpPinRotary2, INPUT);
  mcp.pullUp(mcpPinRotary2, HIGH);  // turn on a 100K pullup internally
  //mcp.setupInterruptPin(mcpPinRotary2, CHANGE);

  mcp.pinMode(mcpLed1, OUTPUT); // on the other port to avoid echoing
  mcp.pinMode(mcpLed2, OUTPUT);
  mcp.pinMode(mcpLed3, OUTPUT);
  mcp.pinMode(mcpLed4, OUTPUT);
  mcp.readGPIOAB(); // Initialise for interrupts.
  attachInterrupt(digitalPinToInterrupt(arduinoIntPin), intCallBack, CHANGE);
}

void loop()
{
  char str[20];
  if (!isrHandled)
  {
    handleInterrupt();
  }

  if (menu_action != MENU_ACTION_NONE)
  {
    if (menu_action==MENU_ACTION_UP)
    {
     //  lcd.setCursor(0,0); lcd.print("UP            ");
      Serial.println("UP");
    }
    else if (menu_action==MENU_ACTION_DOWN)
    {
      //lcd.setCursor(0,0); lcd.print("DOWN          ");
     // lcdDisplay.print(8,0,"DOWN", DISPLAY_ALIGN_CENTER, 16);
      Serial.println("DOWN");
    }
    else if (menu_action==MENU_ACTION_ENTER)
    {
      //lcd.setCursor(0,0); lcd.print("ENTER         ");
      Serial.println("ENTER");
    }
    else if (menu_action==MENU_ACTION_ESC)
    {
      //lcd.setCursor(0,0); lcd.print("ESC          ");
      Serial.println("ESC");
    }
  }

 Menu::currentMenu->update(menu_action, millis());

  menu_action = MENU_ACTION_NONE;

  //readINTCAPAB
  //sprintf(str, "pin=%d val=%d", pin, val);
  //Serial.println(str);
  // char str[20];
  //mcp.digitalWrite(mcpLed1,ledState2);
}

void intCallBack()
{
  isrHandled = false;
}

void handleInterrupt()
{
  isrHandled = true;
  uint8_t pin = mcp.getLastInterruptPin();
  uint16_t gpioAB = mcp.readGPIOAB();

  if (pin == mcpPinRotary1 || pin == mcpPinRotary2)
  {
    handleRotaryEncoder(gpioAB);
  }
  else
  {
    if (pin == mcpPinA)
    {
      int btnPinVal = bitRead(gpioAB, mcpPinA);
      if (buttonEnterPrev != btnPinVal && btnPinVal == 0)
      {
        menu_action = MENU_ACTION_ENTER;
      }

      buttonEnterPrev = btnPinVal;
    }
    else if (pin == mcpPinB)
    {
      int btnPinVal = bitRead(gpioAB, mcpPinB);
      if (buttonEscPrev != btnPinVal && btnPinVal == 0)
      {
        menu_action = MENU_ACTION_ESC;
      }

      buttonEscPrev = btnPinVal;
    }
  }
}

void handleRotaryEncoder(uint16_t gpioAB)
{
  char str[20];
  int a = bitRead(gpioAB, mcpPinRotary1);
  int b = bitRead(gpioAB, mcpPinRotary2);

  if (a != rotaryEncodeLineAPrev && a == 0)
  {
    if (a != b)
    {
      menu_action = MENU_ACTION_DOWN;      
    }
    else
    {
      menu_action = MENU_ACTION_UP;
    }    
  }

  rotaryEncodeLineAPrev = a;
}
