#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

class Robot
{
public:
    int lpin_1;
    int lpin_2;
    int rpin_1;
    int rpin_2;
    Robot()
    {
        lpin_1 = 7;
        lpin_2 = 8;
        rpin_1 = 9;
        rpin_2 = 10;
	pinMode(lpin_1, OUTPUT);
	pinMode(lpin_2, OUTPUT);
	pinMode(rpin_1, OUTPUT);
	pinMode(rpin_2, OUTPUT);
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
	cout << "going foward" << endl;
        digitalWrite(lpin_1, HIGH);
        digitalWrite(lpin_2, LOW);
        digitalWrite(rpin_1, HIGH);
        digitalWrite(rpin_2, LOW);
    };
    void left()
    {
	cout << "going left" << endl;
        digitalWrite(lpin_1, LOW);
        digitalWrite(lpin_2, HIGH);
        digitalWrite(rpin_1, HIGH);
        digitalWrite(rpin_2, LOW);
    };
    void backward()
    {
	cout << "going backward" << endl;
        digitalWrite(lpin_1, LOW);
        digitalWrite(lpin_2, HIGH);
        digitalWrite(rpin_1, LOW);
        digitalWrite(rpin_2, HIGH);
    };
    void right()
    {
	cout << "going right" << endl;
        digitalWrite(lpin_1, HIGH);
        digitalWrite(lpin_2, LOW);
        digitalWrite(rpin_1, LOW);
        digitalWrite(rpin_2, HIGH);
    };
};

int main(int argc, char **argv)
{
    wiringPiSetup();
    Robot robot;

    int input;
    cout << "Use WASD to control. Press q to quit." << endl;
    cout << HIGH << " " << LOW << endl;
    do
    {
        input = getchar();
        robot.update_controls(input);
    }
    while (input != 'q');

    return 0;
}
