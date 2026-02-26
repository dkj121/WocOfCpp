#include "Errors.h"

std::string GetErrorMessage(Error error) {
  switch (error) {
    case NO_ERROR:
      return std::string();  // Return an empty string for no error
    case ERROR_EMPTY_INPUT:
      return "Error: No input provided.";
    case ERROR_SYNTAX_ERROR:
      return "Error: Syntax error in the input.";
    case ERROR_DIVISION_BY_ZERO:
      return "Error: Division by zero is not allowed.";
    case ERROR_MODULO_BY_ZERO:
      return "Error: Modulo by zero is not allowed.";
    case ERROR_UNDEFINED_VARIABLE:
      return "Error: Use of an undefined variable.";
    case ERROR_INVALID_ARGUMENT:
      return "Error: Invalid argument passed to a function.";
    case ERROR_VARIABLE_ALREADY_DEFINED:
      return "Error: Variable already defined.";
    case ERROR_MISSING_PARENTHESIS:
      return "Error: Missing closing parenthesis.";
    default:
      return "Error: An unknown error occurred.";
  }
}