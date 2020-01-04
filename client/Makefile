CXX=g++
CXXFLAGS=-std=c++11 -Wall

client: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o bin/client.o -lwiringPi -lzmqpp -lzmq -pthread

example_zmq: example/zmq_handle.cpp
	$(CXX) $(CXXFLAGS) example/zmq_handle.cpp -o bin/example_zmq.o -lzmqpp -lzmq -pthread

example_tins: example/ip_sniffer.cpp
	$(CXX) $(CXXFLAGS) example/ip_sniffer.cpp -o bin/example_tins.o -ltins