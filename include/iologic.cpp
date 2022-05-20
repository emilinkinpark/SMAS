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

void ioSetup() // Define IO Pins here
{

#ifdef ENABLE_MOTORCONTROL
  pinMode(FAULTPIN, INPUT_PULLDOWN);   // Read OverLoad Fault
  //pinMode(RUNSTATPIN, INPUT_PULLDOWN); // Read Blower Run Status
  pinMode(MOTORPIN, OUTPUT);           // Motor Control Output
#endif
}

int *motorControl(bool CTRL, bool runstatpin, bool faultpin, bool ctrlpin)  // Needs Rigorous Testing
{
  int stat[2]; // 0 = modemc, 1 = fault, 2= runstat;
  bool fault;
  bool motorstat;
  int timestart = millis();
  if (CTRL == true)
  {
    digitalWrite(ctrlpin, HIGH);
    while (digitalRead(faultpin) != 1) // Fault Conditions Loop
    {
      stat[3] = digitalRead(faultpin);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      int timefinal = millis();
      int prestime = timefinal - timestart;
      if (prestime >= 10000)
      {
        digitalWrite(ctrlpin, LOW);
        stat[0] = 10;
        stat[1] = true;
        // Algo: Alarm Set then data sent to Node Red and Motor On Req Off and Set Alarm
        break;
      }
    }
  }
  stat[3] = digitalRead(faultpin);
  // Checks Fault Conditions

  if (CTRL == false)
  {
    digitalWrite(ctrlpin, LOW);
  }
  return stat;
}

bool motorLogic(float DO, float doLow, float doHigh)
{
  if (DO <= doLow)
  {
    digitalWrite(MOTORPIN, HIGH);
    return true;
  }
  else if (DO > doLow && DO <= doHigh)
  {
    // Do Nothing
  }
  else
  {
    digitalWrite(MOTORPIN, LOW);
    return false;
  }
}

#endif