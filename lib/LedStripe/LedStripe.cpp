#include "LedStripe.h"

void LedStripe::startup(void)
{
    for (size_t i = 0; i < amount; i++)
    {
        pinMode(pins[i], OUTPUT);
    }
}

void LedStripe::writesOnly(unsigned int index, unsigned int logic)
{
    digitalWrite(pins[index], logic);
}

void LedStripe::writes(unsigned int logic, unsigned int amount)
{
    amount = min(amount, this->amount);
    for (size_t i = 0; i < amount; i++)
    {
        digitalWrite(pins[i], logic);
    }
}

void LedStripe::flashs(unsigned int times, unsigned long highHeld, unsigned long lowHeld)
{
    for (size_t i = 0; i < times; i++)
    {
        writes(HIGH, this->amount);
        delay(highHeld);
        writes(LOW, this->amount);
        delay(lowHeld);
    }
}