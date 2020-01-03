#!/bin/bash

echo "Building client..."
g++ -Wall -std=c++11 src/main.cpp src/keyboard_controller.cpp -o bin/client.o -lwiringPi -lSDL2
echo "...Done."
