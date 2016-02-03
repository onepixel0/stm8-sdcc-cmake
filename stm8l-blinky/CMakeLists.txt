cmake_minimum_required(VERSION 2.8)
include(sdcc-stm8)
project(stm8 C)

set(C_FILES blinky.c)

add_executable(stm8 ${C_FILES})
STM8_SET_TARGET_PROPERTIES(stm8)