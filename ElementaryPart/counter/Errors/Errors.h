#ifndef ERRORS_H
#define ERRORS_H

#include <string>

enum Error
{
    NO_ERROR,                       // No error occurred
    ERROR_EMPTY_INPUT,              // Input is empty
    ERROR_SYNTAX_ERROR,             // General syntax error
    ERROR_DIVISION_BY_ZERO,         // Attempt to divide by zero
    ERROR_MODULO_BY_ZERO,           // Attempt to perform modulo by zero
    ERROR_UNDEFINED_VARIABLE,       // Use of a variable that has not been defined
    ERROR_INVALID_ARGUMENT,         // Invalid argument passed to a function
    ERROR_VARIABLE_ALREADY_DEFINED, // Attempt to redefine an already defined variable
    ERROR_MISSING_PARENTHESIS,      // Missing closing parenthesis
    ERROR_UNKNOWN_ERROR             // Catch-all for any other errors
};

std::string GetErrorMessage(Error error);   // Function to get a human-readable error message for a given error code

#endif