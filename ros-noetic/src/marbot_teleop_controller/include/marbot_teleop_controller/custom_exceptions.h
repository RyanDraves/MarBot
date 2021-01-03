#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <stdexcept>
#include <string>

using std::string;

class CustomException : public std::exception
{
public:
    CustomException(const string errorMsg = "Custom Exception")
    {
        msg_ = errorMsg;
    }
    const char* what()
    {
        return msg_.c_str();
    }
private:
    string msg_;
};

// class MotorException : public CustomException
// {
// public:
//     MotorException(const string error_msg = "Motor Exception") : CustomException(error_msg) {}
// };

#endif
