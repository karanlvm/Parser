cmake_minimum_required(VERSION 3.22)
project(Parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(Parser main.cpp Tokenizer.cpp Tokenizer.hpp Parser.cpp Parser.hpp)
