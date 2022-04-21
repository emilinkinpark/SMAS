void espReset()
{
    if (reset == true)
    {
        esp_restart();
    }
    else
    {
        // Nothing
    }
}

void ioSetup() // Define IO Pins here
{

#ifdef ENABLE_MOTORCONTROL
    pinMode(14, INPUT_PULLDOWN);    // Read OverLoad Fault
    pinMode (27,INPUT_PULLDOWN);    // Read Blower Run Status
    pinMode(12, OUTPUT); // Motor Control Output
#endif
}

bool motorLogic(float DO, float doLow, float doHigh)
{
    
}