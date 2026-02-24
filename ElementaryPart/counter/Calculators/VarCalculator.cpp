/*
Example : var(x) = 3 => x = 3
Use Example : 1 + x => 1 + 3 => 4
*/

#include "Calculators.h"

std::pair<std::string, double> DefineVariable(std::vector<std::pair<Token, std::string>> input,
                                             const std::map<std::string, double>& variables)
{
    // var ( x ) = <expr...>
    std::string name = input[2].second;

    if (input.size() >= 5) input.erase(input.begin(), input.begin() + 5);

    std::string valueStr = CommenCalculate(input, {}, variables);
    double value = getNum(valueStr);

    return {name, value};
}