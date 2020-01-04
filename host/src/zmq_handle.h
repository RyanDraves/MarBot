#ifndef ZMQ_HANDLE_H
#define ZMQ_HANDLE_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>
#include <zmqpp/message.hpp>

class ZMQ_Handle {
public:
    ZMQ_Handle() : interrupted_(false), pub_thread_(&ZMQ_Handle::pubStatus, this),
        socket_(zmq_context_, zmqpp::socket_type::push) {
        socket_.bind("tcp://*:4099");
    }
    ~ZMQ_Handle() {
        stopZMQ();
    }
    void stopZMQ() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            zmqpp::message request;
            request << "q";
            socket_.send(request, true);
            interrupted_ = true;
        }
        pub_thread_.join();
    }
    void onQPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'q'; }
    void onWPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'w'; }
    void onWRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'W'; }
    void onAPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'a'; }
    void onARelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'A'; }
    void onSPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 's'; }
    void onSRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'S'; }
    void onDPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'd'; }
    void onDRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'D'; }
private:
    void pubStatus() {
        try {
            bool is_interrupted = false;
            std::string buffer_copy;
            while (!is_interrupted) {
                // Must begin with sleep... constructor race condition shhh...
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                if (!buffer_copy.empty()) {
                    zmqpp::message request;
                    request << buffer_copy;
                    socket_.send(request, true);
                }

                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    is_interrupted = interrupted_;
                    buffer_copy = buffer_;
                    buffer_.clear();
                }
            }
        }
        catch (zmqpp::zmq_internal_exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
        catch (...) {
            std::cerr << "Unknown Exception: \n";
        }
    }

    std::mutex mutex_;
    bool interrupted_;
    std::thread pub_thread_;

    zmqpp::context zmq_context_;
    zmqpp::socket socket_;
    std::string buffer_;
};

#endif