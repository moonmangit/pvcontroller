#include "Routine.h"

void Routine::handle()
{
    if (millis() - stamp >= intervals)
    {
        stamp = millis();
        callback();
    }
}