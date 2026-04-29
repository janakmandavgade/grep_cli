#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>
using namespace std;

class ExceptionInFunction: public exception{
    private:   
        string message;
    public:
        explicit ExceptionInFunction(const string &function, const string& error){
            message = "Error in " + function + " : " + error;
        }

        const char* what() const noexcept override{
            return message.c_str();
        }
};

#endif