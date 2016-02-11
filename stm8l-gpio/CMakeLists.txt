cmake_minimum_required(VERSION 2.8)
set(PROJECT stm8l-gpio)
project(${PROJECT} C)

include(sdcc-stm8)

find_package(STM8_StdPeriph COMPONENTS gpio REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/StdPeriph
        ${STM8_StdPeriph_INCLUDE_DIR}
)

set(C_FILES main.c)

add_executable(${PROJECT} ${C_FILES} ${STM8_StdPeriph_SOURCES})
STM8_SET_TARGET_PROPERTIES(${PROJECT})