/*
Get the type of the input, which can be a number, a variable, a function or a function call.
*/
#include "Parses.h"

std::pair<Token, std::string> TypeParse(const std::vector<std::pair<Token, std::string>> input, const std::map<std::string, double>& variables)
{
    if (input.empty())
    {
        return {UNKNOWN, GetErrorMessage(ERROR_EMPTY_INPUT)};
    }
    else if (input.size() == 1)
    {
        if (input[0].first == NUM)
        {
            return {NUM, GetErrorMessage(NO_ERROR)};
        }
        else if (input[0].first == NUL)
        {
            return {NUL, GetErrorMessage(NO_ERROR)};
        }
        else
        {
            return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
        }
    }
    else if (input.size() == 2)
    {
        if ((input[0].first == PLUS || input[0].first == MINU) && input[1].first == NUM)
        {
            return {input[0].first, GetErrorMessage(NO_ERROR)};
        }
        else
        {
            return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
        }
    } 
    else if (input.size() == 3)
    {
        if (input[0].first == FUN && input[1].first == NUM && input[2].first == RPARE)
        {
            return {FUN, GetErrorMessage(NO_ERROR)};
        }
        else
        {
            return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
        }
    }
    else if (input.size() >= 4)
    {
        if (input[0].first == FUN && input[1].first == LPARE && input[2].first == PARAM && input[3].first == RPARE && input[4].first == EQUAL)
        {
            return {FUNDEF, GetErrorMessage(NO_ERROR)};
        }
        else if (input[0].first == VAR && input[1].first == LPARE && input[2].first == PARAM && input[3].first == RPARE && input[4].first == EQUAL)
        {
            if (variables.find(input[2].second) != variables.end())
            {
                return {VAR, GetErrorMessage(NO_ERROR)};
            }
            return {VARDEF, GetErrorMessage(NO_ERROR)};
        }
        else
        {
            return {UNKNOWN, GetErrorMessage(NO_ERROR)};
        }
    }
    else
    {
        return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
    }
}