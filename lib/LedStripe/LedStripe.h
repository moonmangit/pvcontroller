#ifndef __LED_STRIPE_H__
#define __LED_STRIPE_H__

#include <Arduino.h>

class LedStripe
{
private:
    typedef unsigned int pin_t;
    pin_t *pins;
    unsigned int amount;

public:
    LedStripe(unsigned int amount, ...)
    {
        va_list vl;
        va_start(vl, amount);
        pin_t *pins = new pin_t[amount];
        for (size_t i = 0; i < amount; i++)
        {
            pins[i] = (pin_t)va_arg(vl, pin_t);
        }
        this->amount = amount;
        this->pins = pins;
    }
    ~LedStripe()
    {
        delete[] pins;
    }
    void startup(void);
    void writesOnly(unsigned int index, unsigned int logic);
    void writes(unsigned int logic, unsigned int amount);
    void flashs(unsigned int times, unsigned long highHeld = 250, unsigned long lowHeld = 250);
};

#endif