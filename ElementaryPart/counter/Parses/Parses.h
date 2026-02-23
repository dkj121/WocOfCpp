#ifndef PARSES_H
#define PARSES_H

#include <string>
#include <vector>
#include "../Tokens/Tokens.h"
#include "../Errors/Errors.h"

std::vector<std::pair<Token, std::string>> InputParse(std::string input);
Token TypeParse(std::vector<std::pair<Token, std::string>> input);

#endif
