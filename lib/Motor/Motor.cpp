#include "Motor.h"

void Motor::startup(void)
{
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    stop();
}
void Motor::stop(void)
{
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}
void Motor::forward(void)
{
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
}
void Motor::backward(void)
{
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
}
// with delay
void Motor::block(unsigned long duration)
{
    stop();
    delay(duration);
}
void Motor::forward(unsigned long duration)
{
    forward();
    delay(duration);
    stop();
}
void Motor::backward(unsigned long duration)
{
    backward();
    delay(duration);
    stop();
}