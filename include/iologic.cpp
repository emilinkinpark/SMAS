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
#ifdef ENABLE_CALLINGBELL
    pinMode(16, INPUT); // Calling Bell Input
#endif
#ifdef ENABLE_MOTORCONTROL

    pinMode(20, OUTPUT); // Motor Control Output
#endif
}

bool motorControl(float DO, float doLow, float doHigh)
{
    float blowerStat = false;
    if (DO != 0)
    {
        if (DO <= doLow)
        {
            blowerStat = true;
#ifdef ENABLE_IOCONTROL_DEBUG
            

            Serial.print("Blower Stat: ");
            Serial.println(blowerStat);
#endif
        }
        else if (DO >= doLow && DO <= doHigh)
        {
            // DO Nothing
        }
        else if (DO >= doHigh)
        {
            blowerStat = false;
#ifdef ENABLE_IOCONTROL_DEBUG
            Serial.print("Blower Stat: ");
            Serial.println(blowerStat);
#endif
        }

        else
        {
#ifdef ENABLE_IOCONTROL_DEBUG
            Serial.print("Blower Stat: ");
            Serial.println("Nothing TO DO!");
#endif
        }
    }
    return blowerStat;
}