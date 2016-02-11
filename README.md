# STM8-SDCC-CMAKE

## About

This is project for developing applications for STM8 microcontrollers using SDCC compiler.

Project based on `https://github.com/ObKo/stm32-cmake`

There is support for STM8S and STM8L series now.

ST StdPeriph Library doesn't support SDCC Compiler out of the box. StdPeriphLib in this project was edited for SDCC.

Required software:

* SDCC compiler - `http://sdcc.sourceforge.net/`
* CMake 2.8 or higher - `https://cmake.org/`


## Usage

For successful build you need to define some variables.

* `CMAKE_TOOLCHAIN_FILE` - path to sdcc-generic.cmake toolchain file.
* `CMAKE_MODULE_PATH` - path to cmake files directory.
* `STM8_StdPeriph_DIR` - path to StdPeriph directory.
* `STM8_CHIP` - stm8 chip name, e.g. stm8l152c6 or stm8s105k4

Example for makefiles:
	
	cmake -DCMAKE_TOOLCHAIN_FILE=<path_to_sdcc-generic.cmake> -DCMAKE_MODULE_PATH=<path_to_project_cmake_dir> -DSTM8_CHIP=<chip name> -DSTM8_StdPeriph_DIR=<path to std periph> -G"MinGW Makefiles" <path_to_source_dir>


It builds sdcc's *.ihx file. If you need you can convert it to *.hex or *.bin file.
