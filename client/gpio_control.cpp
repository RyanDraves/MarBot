#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

class Robot
{
    int lpin1;
    int lpin2;
    int rpin1;
    int rpin2;
    Robot()
    {
        lpin1 = 7;
        lpin2 = 8;
        rpin1 = 9;
        rpin2 = 10;
    };
    void update_controls(int input)
    {
        switch (input)
        {
            case 'w':
                forward();
                break;
            case 'a':
                left();
                break;
            case 's':
                backward();
                break;
            case 'd':
                right();
                break;
            default:
                break;
        }
    };
    void forward()
    {
        digitialWrite(lpin_1, HIGH);
        digitialWrite(lpin_2, HIGH);
        digitialWrite(rpin_1, HIGH);
        digitialWrite(rpin_2, HIGH);
    };
    void left()
    {
        digitialWrite(lpin_1, LOW);
        digitialWrite(lpin_2, LOW);
        digitialWrite(rpin_1, HIGH);
        digitialWrite(rpin_2, HIGH);
    };
    void backward()
    {
        digitialWrite(lpin_1, LOW);
        digitialWrite(lpin_2, LOW);
        digitialWrite(rpin_1, LOW);
        digitialWrite(rpin_2, LOW);
    };
    void right()
    {
        digitialWrite(lpin_1, HIGH);
        digitialWrite(lpin_2, HIGH);
        digitialWrite(rpin_1, LOW);
        digitialWrite(rpin_2, LOW);
    };
};

int main(int argc, char **argv)
{
    Robot robot;

    int input;
    cout << "Use WASD to control. Press q to quit." << endl;
    do
    {
        input = getchar();
        robot.update_controls(input);
    }
    while (c != 'q');

    return 0;
}