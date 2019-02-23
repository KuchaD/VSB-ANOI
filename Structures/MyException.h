//
// Created by davelinux on 23.2.19.
//

#ifndef VSB_ANOI_MYEXCEPTION_H
#define VSB_ANOI_MYEXCEPTION_H


#include <exception>
#include "iostream"
class MyException : public std::exception {
private:
    std::string Message;
public:
    MyException(std::string Message);
    const std::string what (){
        return Message;
    }
};


#endif //VSB_ANOI_MYEXCEPTION_H
