/*
Get the type of the input, which can be a number, a variable, a function or a
function call.
*/
#include "Parses.h"

static bool isFunCall(const std::vector<std::pair<Token, std::string>>& input) {
  // fun ( <expr...> )
  if (input.size() < 4) return false;
  if (input[0].first != FUN) return false;
  if (input[1].first != LPARE) return false;

  int depth = 0;
  bool found = false;
  for (size_t i = 1; i < input.size(); ++i) {
    if (input[i].first == LPARE)
      depth++;
    else if (input[i].first == RPARE) {
      depth--;
      if (depth == 0) {
        found = true;
        break;
      }
    }
  }
  return found;
}

std::pair<Token, std::string> TypeParse(
    const std::vector<std::pair<Token, std::string>> input,
    const std::map<std::string, double>& variables) {
  if (input.empty()) {
    return {UNKNOWN, GetErrorMessage(ERROR_EMPTY_INPUT)};
  } else if (input.size() == 1) {
    if (input[0].first == NUM) {
      return {NUM, GetErrorMessage(NO_ERROR)};
    } else if (input[0].first == NUL) {
      return {NUL, GetErrorMessage(NO_ERROR)};
    } else {
      return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
    }
  } else if (input.size() == 2) {
    if ((input[0].first == PLUS || input[0].first == MINU) &&
        input[1].first == NUM) {
      return {input[0].first, GetErrorMessage(NO_ERROR)};
    } else {
      return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
    }
  } else if (input.size() >= 4) {
    // FUNDEF: fun(x)=...
    if (input.size() >= 5 && input[0].first == FUN && input[1].first == LPARE &&
        input[2].first == PARAM && input[3].first == RPARE &&
        input[4].first == EQUAL) {
      return {FUNDEF, GetErrorMessage(NO_ERROR)};
    }
    // VARDEF: var(x)=...
    else if (input.size() >= 5 && input[0].first == VAR &&
             input[1].first == LPARE && input[2].first == PARAM &&
             input[3].first == RPARE && input[4].first == EQUAL) {
      if (variables.find(input[2].second) != variables.end()) {
        return {VAR, GetErrorMessage(NO_ERROR)};
      }
      return {VARDEF, GetErrorMessage(NO_ERROR)};
    }
    // FUNCALL: fun(<expr...>)
    else if (isFunCall(input)) {
      return {FUN, GetErrorMessage(NO_ERROR)};
    } else {
      return {UNKNOWN, GetErrorMessage(NO_ERROR)};
    }
  } else {
    return {UNKNOWN, GetErrorMessage(ERROR_SYNTAX_ERROR)};
  }
}