set(STM8_SUPPORTED_SERIES S L CACHE INTERNAL "supported stm8 series")

if(NOT STM8_SERIES)
    message(STATUS "No STM8_SERIES specified, trying to get it from STM8_CHIP")
    if(NOT STM8_CHIP)
        set(STM8_SERIES "S" CACHE INTERNAL "stm8 series")
        message(STATUS "Neither STM8_SERIES nor STM8_CHIP specified, using default STM8_SERIES: ${STM8_SERIES}")
    else()
        string(REGEX REPLACE "^[sS][tT][mM]8([sS]|[lL]).+$" "\\1" STM8_SERIES ${STM8_CHIP})
        string(TOUPPER ${STM8_SERIES} STM8_SERIES)
        message(STATUS "Selected STM8_SERIES: ${STM8_SERIES}")
    endif()
endif()

string(TOUPPER ${STM8_SERIES} STM8_SERIES)
list(FIND STM8_SUPPORTED_SERIES ${STM8_SERIES} SER_INDEX)
if(SER_INDEX EQUAL -1)
    message(FATAL_ERROR "Invalid/unsupported STM8_SERIES: ${STM8_SERIES}")
endif()



string(TOLOWER ${STM8_SERIES} STM8_SERIES_LOWER)
include(sdcc-stm8${STM8_SERIES_LOWER})

function(STM8_SET_TARGET_PROPERTIES TARGET)
    if(NOT STM8_CHIP_TYPE)
        STM8_GET_CHIP_TYPE(${STM8_CHIP} STM8_CHIP_TYPE)
    endif()
    STM8_SET_CHIP_DEFINITIONS(${TARGET} ${STM8_CHIP_TYPE})
endfunction()


#TODO: add hex target