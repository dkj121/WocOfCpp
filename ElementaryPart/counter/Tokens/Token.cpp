#include "Tokens.h"

double getNum(std::string s)
{
    if (s == "pi")
    {
        return pi;
    }
    else if (s == "e")
    {
        return e;
    }
    else
    {
        return std::stod(s);
    }
}
