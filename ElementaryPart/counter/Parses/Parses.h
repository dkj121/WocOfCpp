#ifndef PARSES_H
#define PARSES_H

#include <string>
#include <vector>
#include <map>
#include "../Tokens/Tokens.h"
#include "../Errors/Errors.h"

std::vector<std::pair<Token, std::string>> InputParse(std::string input);
std::pair<Token, std::string> TypeParse(const std::vector<std::pair<Token, std::string>> input, const std::map<std::string, double>& variables);

#endif
