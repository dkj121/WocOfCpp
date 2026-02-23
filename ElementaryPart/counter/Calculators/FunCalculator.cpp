/*
Define Example :fun(x) = x ^ 2 + 3
Use Example :fun(5) => 5 ^ 2 + 3 => 28
*/
#include "Calculators.h"

std::string FunctionCalculate(std::vector<std::pair<Token, std::string>> function)
{
    // TODO: Implement the logic to calculate the value of a function based on the provided tokens and parameters.
    return "Function calculation result";
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
