#!/bin/bash

g++ -Wall -std=c++11 main.cpp keyboard_controller.cpp -o bin/gpio_control.o -lwiringPi -lSDL2
