#!/bin/bash

echo "Building client..."
g++ -Wall -std=c++11 src/main.cpp -o bin/client.o -lwiringPi -lzmqpp -lzmq -pthread
echo "...Done."
