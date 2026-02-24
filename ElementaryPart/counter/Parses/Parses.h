#ifndef PARSES_H
#define PARSES_H

#include <string>
#include <vector>
#include <map>
#include "../Tokens/Tokens.h"
#include "../Errors/Errors.h"

// Parses the input string into tokens and values, and then determines the type of the expression (number, variable, operator, etc.).
std::vector<std::pair<Token, std::string>> InputParse(std::string input);
// Parses the tokens and values to determine the type of the expression, such as whether it is a number, variable, operator, function, etc..
std::pair<Token, std::string> TypeParse(const std::vector<std::pair<Token, std::string>> input, 
                                        const std::map<std::string, double>& variables);

#endif
