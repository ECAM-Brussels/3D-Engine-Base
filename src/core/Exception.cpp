#include "Exception.h"

Exception::Exception(string msg): msg(msg) {}

string Exception::getMessage()
{
    return msg;
}