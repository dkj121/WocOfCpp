#ifndef CALCULATORS_H
#define CALCULATORS_H

#include <string>
#include <vector>
#include <map>
#include "../Tokens/Tokens.h"
#include "../Errors/Errors.h"

// Calculates the result of a mathematical expression represented as a vector of tokens and their corresponding string values.
std::string CommenCalculate(const std::vector<std::pair<Token, std::string>> input,
                            const std::vector<std::pair<Token, std::string>> function,
                            const std::map<std::string, double> variables);
// Calculates the result of a function call given the function definition and the current variable values.
double CalculateFunction(const std::vector<std::pair<Token, std::string>> function,
                         const std::map<std::string, double>& variables,
                         Error& err);
// Defines a new variable based on the input tokens and the current variable values. Returns a pair of the variable name and its value.
std::pair<std::string, double> DefineVariable(std::vector<std::pair<Token, std::string>> input,
                                             const std::map<std::string, double>& variables);
// Defines a new function based on the input tokens. Returns a vector of tokens representing the function definition.
std::vector<std::pair<Token, std::string>> DefineFunction(std::vector<std::pair<Token, std::string>> input);
// Folds function calls in the input tokens by replacing them with their calculated values. Returns a new vector of tokens with function calls folded.
std::vector<std::pair<Token, std::string>> FoldFunctionCalls(
    const std::vector<std::pair<Token, std::string>>& input,
    const std::vector<std::pair<Token, std::string>>& function,
    const std::map<std::string, double>& variables,
    Error& err);

#endif