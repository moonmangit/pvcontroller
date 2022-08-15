#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <Arduino.h>

class Motor
{
private:
    typedef unsigned int pin_t;

    pin_t pinA;
    pin_t pinB;

public:
    Motor(pin_t pinA, pin_t pinB)
    {
        this->pinA = pinA;
        this->pinB = pinB;
    }
    ~Motor() {}
    void startup(void);
    void stop(void);
    void forward(void);
    void backward(void);
    // with delay
    void block(unsigned long duration);
    void forward(unsigned long duration);
    void backward(unsigned long duration);
};

#define TIME2MS(h, m, s) ((h * 3600000UL) + (m * 60000UL) + (s * 1000UL))

enum MOTORDIR
{
    backward = -1,
    stop,
    forward
};

typedef struct MotorTask
{
    int direction;
    unsigned long duration;
} mtask_t;

#endif