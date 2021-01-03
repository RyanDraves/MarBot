#!/usr/bin/env python

import RPi.GPIO as GPIO
from gpiozero import Button, Robot
import time

my_path = "/home/pi/src/marBot/"

#GPIO.setmode(GPIO.BCM)

#GPIO.setup(4, GPIO.OUT)
#motor = GPIO.PWM(4, 100)

class _Getch:
    """Gets a single character from standard input.  Does not echo to the
screen."""
    def __init__(self):
        self.impl = _GetchUnix()
    def __call__(self):
        return self.impl()

class _GetchUnix:
    def __init__(self):
        import tty, sys
    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

getch = _Getch()

def loop():
    robby = Robot(left=(9,10), right=(7,8))
    while True:
        input = getch()
        if input == "w":
            robby.forward(1.0)
        elif input == "a":
            robby.left(1.0)
        elif input == "s":
            robby.backward(1.0)
        elif input == "d":
            robby.right(1.0)
        elif input == "q":
            break
        else:
            robby.forward(0.0)
        #motor.start(10)
        #motor.stop()

if __name__ == '__main__': # Program start from here
    print("Press q to quit")
    try:
        loop()
    except KeyboardInterrupt: # When 'Ctrl+C' is pressed, the child program destroy() will be executed.
        print("Stopping program")
