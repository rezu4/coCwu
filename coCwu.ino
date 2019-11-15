#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include "lib\menu\MenuItem.h"

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

uint8_t menu_action = MENU_ACTION_NONE;

void setup()
{
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
      Serial.println("UP");
    }
    else if (menu_action==MENU_ACTION_DOWN)
    {
      Serial.println("DOWN");
    }
    else if (menu_action==MENU_ACTION_ENTER)
    {
      Serial.println("ENTER");
    }
    else if (menu_action==MENU_ACTION_ESC)
    {
      Serial.println("ESC");
    }
  }

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
