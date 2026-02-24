cmake_minimum_required(VERSION 3.10.0)
project(counter VERSION 0.1.0 LANGUAGES C CXX)

add_executable(counter
  main.cpp
  Reader/InputReader.cpp
  Parses/InputParse.cpp
  Parses/TypeParse.cpp
  Calculators/CommenCalculator.cpp
  Calculators/FunCalculator.cpp
  Calculators/VarCalculator.cpp
  Calculators/FoldFunctionCalls.cpp
  Tokens/Token.cpp
  Errors/Error.cpp
)

target_include_directories(counter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})