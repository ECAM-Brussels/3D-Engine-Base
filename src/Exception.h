#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class Exception: public exception
{
private:
    string msg;

public:
    Exception(string msg);
    string getMessage();
};

#endif