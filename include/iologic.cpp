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

void ioSetup() // Define IO Pins here
{
#ifdef ENABLE_CALLINGBELL
  pinMode(CALLPIN, INPUT_PULLDOWN); // Reads CALLING BELL INPUT PIN
#endif
}

void callbellRead(bool *state, uint8_t pin)
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