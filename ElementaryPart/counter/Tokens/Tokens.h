#ifndef TOKENS_H
#define TOKENS_H

#include <string>

// define some constants
const double e = 2.71828182845904523536;
const double pi = 3.14159265358979323846;
// define the token types
enum Token {
  OR,
  AND,

  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  EQUAL_EQUAL = 11,
  BANG_EQUAL,

  PLUS,
  MINU,

  MULT = 20,
  DIVI,
  MOD,

  SQUA,

  SIN,
  COS,
  TAN,
  SQRT,
  ABS,
  LOG,
  LN,
  EXP,
  LPARE,
  RPARE,

  NUL,
  NUM,

  EQUAL,
  BANG,

  FUN,
  VAR,
  VARDEF,
  PARAM,
  FUNDEF,

  UNKNOWN,
  END
};
// get the value of a number token
double getNum(std::string s);

#endif
