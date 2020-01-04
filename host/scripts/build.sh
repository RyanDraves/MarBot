#!/bin/bash

echo "Building host..."
g++ -Wall -std=c++11 src/main.cpp src/keyboard_controller.cpp -o bin/host.o -lSDL2 -lzmqpp -lzmq -pthread
echo "...Done."
