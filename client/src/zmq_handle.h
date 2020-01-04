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
#include <zmqpp/reactor.hpp>

class ZMQ_Handle {
public:
    ZMQ_Handle(const std::string &ip_address) : interrupted_(false), sub_thread_(&ZMQ_Handle::subStatus, this),
        socket_(zmq_context_, zmqpp::socket_type::pull) {
        socket_.connect("tcp://" + ip_address + ":4099");

        reactor_.add(socket_, std::bind(&ZMQ_Handle::onMsgReceived, this));
    }
    ~ZMQ_Handle() {
        stopZMQ();
    }
    void stopZMQ() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            interrupted_ = true;
        }
        sub_thread_.join();
    }
    std::string getState() {
        std::unique_lock<std::mutex> lock(mutex_);
        std::string ret = buffer_;
        buffer_.clear();
        return ret;
    }
    void onQPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'q'; }
    void onQRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'Q'; }
    void onWPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'w'; }
    void onWRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'W'; }
    void onAPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'a'; }
    void onARelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'A'; }
    void onSPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 's'; }
    void onSRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'S'; }
    void onDPress() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'd'; }
    void onDRelease() { std::unique_lock<std::mutex> lock(mutex_); buffer_ += 'D'; }
private:
    void subStatus() {
        try {
            // bool is_interrupted = false;
            // std::string buffer_copy;
            // while (!is_interrupted) {
            //     std::this_thread::sleep_for(std::chrono::milliseconds(10));

            //     if (!buffer_copy.empty()) {
            //         zmqpp::message request;
            //         request << buffer_copy;
            //         socket_.send(request, true);
            //     }

            //     {
            //         std::unique_lock<std::mutex> lock(mutex_);
            //         is_interrupted = interrupted_;
            //         buffer_copy = buffer_;
            //         buffer_.clear();
            //     }
            // }
            // Must begin with sleep... constructor race condition shhh...
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            while(!interrupted_){
                reactor_.poll(1000);
            }
        }
        catch (zmqpp::zmq_internal_exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
        catch (...) {
            std::cerr << "Unknown Exception: \n";
        }
    }

    void onMsgReceived() {
        zmqpp::message response;
        socket_.receive(response, true);
        {
            std::unique_lock<std::mutex> lock(mutex_);
            buffer_ += response.get(0);
        }
    }

    std::mutex mutex_;
    bool interrupted_;
    std::thread sub_thread_;

    zmqpp::context zmq_context_;
    zmqpp::socket socket_;    
    zmqpp::reactor reactor_;
    std::string buffer_;
};

#endif
