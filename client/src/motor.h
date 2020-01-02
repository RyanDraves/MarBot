#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include "custom_exceptions.h"

class Motor
{
private:
    int f_pin_;
    int b_pin_;
public:
    Motor(int f, int b) :
        f_pin_(f), b_pin_(b)
    {
        pinMode(f_pin_, OUTPUT);
        pinMode(b_pin_, OUTPUT);
    }
    void set(double val)
    {
        check_invariants(val);
        if (val >= 0)
        {
            digitalWrite(f_pin_, val);
            digitalWrite(b_pin_, LOW);
        }
        else
        {
            digitalWrite(f_pin_, LOW);
            digitalWrite(b_pin_, -val);
        }
    }
private:
    void check_invariants(double val)
    {
        if (val > 1 || val < -1)
            throw MotorException("Motor values are between -1 and 1");
    }
    ~Motor()
    {
        digitalWrite(f_pin_, LOW);
        digitalWrite(b_pin_, LOW);
    }
};

#endif  // MOTOR_H
