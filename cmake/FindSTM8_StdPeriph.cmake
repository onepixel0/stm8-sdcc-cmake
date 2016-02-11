#STM8_StdPeriph

STM8_GET_CHIP_TYPE(${STM8_CHIP} STM8_CHIP_TYPE)

if(STM8_CHIP_TYPE MATCHES "10X")

    set(STM8_STD_COMPONENTS
            awu beep clk comp exti
            flash gpio i2c irtim
            itc iwdg rst spi tim2
            tim3 tim4 usart wfe
            )
    set(STM8_STD_PREFIX "stm8l10x")
    set(STM8_STD_HEADERS ${STM8_STD_PREFIX}.h)
    set(STM8_STD_SOURCES "")
    set(STM8_FIND_PREFIX "L10x")

elseif(STM8_CHIP_TYPE MATCHES "05X|15X")

    set(STM8_STD_COMPONENTS
            adc aes beep clk comp
            dac dma exti flash gpio
            i2c irtim itc iwdg lcd
            pwr rst rtc spi syscfg
            tim1 tim2 tim3 tim4
            tim5 usart wfe wwdg
            )

    set(STM8_STD_PREFIX "stm8l15x")
    set(STM8_STD_HEADERS ${STM8_STD_PREFIX}.h)
    set(STM8_STD_SOURCES "")
    set(STM8_FIND_PREFIX "L15x")

elseif(STM8_CHIP_TYPE MATCHES "[012]0[3578]")

    set(STM8_STD_COMPONENTS
            adc1 adc2 awu beep can
            clk exti flash gpio i2c
            itc iwdg rst spi tim1 tim2
            tim3 tim4 tim5 tim6 uart1
            uart2 uart3 uart4 wwdg
            )
    set(STM8_STD_PREFIX "stm8s")
    set(STM8_STD_HEADERS ${STM8_STD_PREFIX}.h)
    set(STM8_STD_SOURCES "")
    set(STM8_FIND_PREFIX "S")

endif()

if(NOT STM8_StdPeriph_FIND_COMPONENTS)
    set(STM8_StdPeriph_FIND_COMPONENTS ${STM8_STD_COMPONENTS})
    message(STATUS "No STM8_StdPeriph components selected, using all available for current series: ${STM8_StdPeriph_FIND_COMPONENTS}")
endif()

foreach(COMP ${STM8_StdPeriph_FIND_COMPONENTS})
    list(FIND STM8_STD_COMPONENTS ${COMP} INDEX)
    if(${INDEX} LESS 0)
        message(FATAL_ERROR "Unknown STM8 component: ${COMP}.")
    else()
        list(APPEND STM8_STD_HEADERS ${STM8_STD_PREFIX}_${COMP}.h)
        list(APPEND STM8_STD_SOURCES ${STM8_STD_PREFIX}_${COMP}.c)
    endif()
endforeach()

list(REMOVE_DUPLICATES STM8_STD_HEADERS)

find_path(STM8_StdPeriph_INCLUDE_DIR ${STM8_STD_HEADERS}
        PATHS ${STM8_StdPeriph_DIR}/Libraries/STM8${STM8_FIND_PREFIX}_StdPeriph_Driver/inc/
        CMAKE_FIND_ROOT_PATH_BOTH
)


foreach(STD_SRC ${STM8_STD_SOURCES})
    set(STD_${STD_SRC}_FILE STD_SRC_FILE-NOTFOUND)
    find_file(STD_${STD_SRC}_FILE ${STD_SRC}
            PATHS ${STM8_StdPeriph_DIR}/Libraries/STM8${STM8_FIND_PREFIX}_StdPeriph_Driver/src
            CMAKE_FIND_ROOT_PATH_BOTH
    )
    list(APPEND STM8_StdPeriph_SOURCES ${STD_${STD_SRC}_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(STM8_StdPeriph DEFAULT_MSG STM8_StdPeriph_INCLUDE_DIR STM8_StdPeriph_SOURCES)