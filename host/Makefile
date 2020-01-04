CXX=g++
CXXFLAGS=-std=c++11 -Wall

host: src/main.cpp src/keyboard_controller.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/keyboard_controller.cpp -o bin/host.o -lSDL2 -lzmqpp -lzmq -pthread

example_zmq: example/zmq_handle.cpp
	$(CXX) $(CXXFLAGS) example/zmq_handle.cpp -o bin/example_zmq.o -lpthread -lzmq -lzmqpp