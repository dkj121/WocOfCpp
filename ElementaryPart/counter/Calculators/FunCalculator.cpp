/*
Define Example :fun(x) = x ^ 2 + 3
Use Example :fun(5) => 5 ^ 2 + 3 => 28
*/
#include "Calculators.h"

double CalculateFunction(const std::vector<std::pair<Token, std::string>> function, const std::map<std::string, double>& variables, Error& err)
{
    std::vector<std::pair<Token, std::string>> substitutedFunction = function;
    for (auto& token : substitutedFunction)
    {
        if (token.first == PARAM)
        {
            auto it = variables.find(token.second);
            if (it == variables.end())
            {
                err = ERROR_UNDEFINED_VARIABLE;
                return 0.0; // Return value won't be used when there's an error
            }
            token.first = NUM;
            token.second = std::to_string(it->second);
        }
    }
    return getNum(CommenCalculate(substitutedFunction, {}, variables));
}

std::vector<std::pair<Token, std::string>> DefineFunction(std::vector<std::pair<Token, std::string>> input)
{
    std::vector<std::pair<Token, std::string>> result;
    std::string param = input[1].second; // Assuming the parameter is always at index 1

    for (size_t i = 4; i < input.size(); ++i)
    {
        if (input[i].first == PARAM && input[i].second != param)
        {
            throw ERROR_VARIABLE_ALREADY_DEFINED;
        }
        else
        {
            result.push_back(input[i]);
        }
    }

    return result;
}
