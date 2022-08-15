#ifndef __ROUTINE_H__
#define __ROUTINE_H__

#include <Arduino.h>

class Routine
{
private:
    unsigned long intervals;
    unsigned long stamp;
    void (*callback)();

public:
    Routine(unsigned long intervals, void (*callback)())
    {
        this->intervals = intervals;
        this->callback = callback;
    }
    ~Routine() {}
    void handle(void);
};

#endif