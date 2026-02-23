/*
Get the type of the input, which can be a number, a variable, a function or a function call.
*/
#include "Parses.h"

Token TypeParse(std::vector<std::pair<Token, std::string>> input)
{
    if (input.empty())
    {
        throw ERROR_EMPTY_INPUT;
        return UNKNOWN;
    }
    else if (input.size() == 1)
    {
        if (input[0].first == NUM)
        {
            return NUM;
        }
        else if (input[0].first == NUL)
        {
            return NUL;
        }
        else
        {
            throw ERROR_SYNTAX_ERROR;
            return UNKNOWN;
        }
    }
    else if (input.size() == 2)
    {
        if ((input[0].first == PLUS || input[0].first == MINU) && input[1].first == NUM)
        {
            return input[0].first;
        }
        else
        {
            throw ERROR_SYNTAX_ERROR;
            return UNKNOWN;
        }
    } 
    else if (input.size() == 3)
    {
        if (input[0].first == PARAM && input[1].first == RPARE && input[2].first == EQUAL)
        {
            return PARAM;
        }
        else
        {
            return UNKNOWN;
        }
    }
    else if (input.size() >= 3)
    {
        if (input[0].first == FUN && input[1].first == PARAM && input[2].first == RPARE && input[3].first == EQUAL)
        {
            return FUN;
        }
        else if (input[0].first == VAR && input[1].first == PARAM && input[2].first == RPARE && input[3].first == EQUAL)
        {
            return VAR;
        }
        else
        {
            return UNKNOWN;
        }
    }
    else
    {
        throw ERROR_SYNTAX_ERROR;
        return UNKNOWN;
    }
}