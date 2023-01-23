#ifndef IOLOGIC_H
#define IOLOGIC_H

bool isInteger(float number)
{
  if (number == ((int)number))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool length(int lengthAllowed, int number)
{
  int a = 0;
  while (number > 0)
  {
    number /= 10;
    a++;
  }
  if (lengthAllowed == a)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#define FAULTPIN 14
#define SPAREPIN 27
#define MOTORPIN 12
#define CALLPIN 18

int lastState = LOW; // the previous state from the input pin
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;
#define SHORT_PRESS_TIME 500 // 500 milliseconds

void ioSetup() // Define IO Pins here
{
#ifdef ENABLE_CALLINGBELL
  pinMode(CALLPIN, INPUT_PULLDOWN); // Reads CALLING BELL INPUT PIN
#endif
}

void callbellRead(bool *state, uint8_t pin)   // Example of variable output from a function in C
{
#ifdef ENABLE_CALLINGBELL

  bool currentState = digitalRead(pin);

  if (currentState == true)
  {
    *state = true;
  }
  else if (currentState == false)
  {
    *state = false;
  }

#endif
}

#endif