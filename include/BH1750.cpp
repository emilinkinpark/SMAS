#include <BH1750.h>
#include "enabler.h"
#include "globalvar.h"

BH1750 lightMeter(0x23);

void bh1750Init()
{

#ifdef ENABLE_BH1750
    bool status = lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

#endif
#ifdef ENABLE_BH1750_DEBUG
    if (status)
    {
        Serial.println(F("BH1750 Advanced begin"));
    }
    else
    {
        Serial.println(F("Error initialising BH1750"));
    }
#endif
}

void bh1750Loop()
{
#ifdef ENABLE_BH1750
    if (lightMeter.measurementReady())
    {
        lux = lightMeter.readLightLevel();
       //lux = map(lightMeter.readLightLevel(), 0, 65535, 0, 100); // Provides output in %;
    }
#endif

#ifdef ENABLE_BH1750_DEBUG
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
#endif
}