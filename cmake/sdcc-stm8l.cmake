set(STM8_CHIP_TYPES
        10X
        15X_LD
        15X_MD
        15X_MDP
        15X_HD
        05X_LD_VL
        05X_MD_VL
        05X_HD_VL)


set(STM8_CODES
        101[FGK][23]
        151[CFGK][23]
        15[12][CGK][46]
        15[12][R][6]
        1[56][12][CMR][8]
        051[F][3]
        052[C][6]
        052[R][8]
    )

macro(STM8_GET_CHIP_TYPE CHIP CHIP_TYPE)
    string(TOUPPER ${CHIP} CHIP_UPPER)
    string(REGEX REPLACE "^[sS][tT][mM]8[lL]( ([01][056][12][CFGKMR]) )+$" "\\1" STM8_CODE ${CHIP_UPPER})
    set(INDEX 0)
    foreach(TYPE ${STM8_CHIP_TYPES})
        list(GET STM8_CODES ${INDEX} CHIP_TYPE_REGEX)
        if(STM8_CODE MATCHES ${CHIP_TYPE_REGEX})
            set(RESULT_TYPE ${TYPE})
        endif()
        MATH(EXPR INDEX "${INDEX}+1")
    endforeach()
    set(${CHIP_TYPE} ${RESULT_TYPE})
endmacro()


function(STM8_SET_CHIP_DEFINITIONS TARGET CHIP_TYPE)
    list(FIND STM8_CHIP_TYPES ${CHIP_TYPE} TYPE_INDEX)
    if(TYPE_INDEX EQUAL -1)
        message(FATAL_ERROR "Invalid/unsupported STM8L chip type: ${CHIP_TYPE}")
    endif()
    get_target_property(TARGET_DEFS ${TARGET} COMPILE_DEFINITIONS)
    if(TARGET_DEFS)
        set(TARGET_DEFS "STM8L${CHIP_TYPE};${TARGET_DEFS}")
    else()
        set(TARGET_DEFS "STM8L${CHIP_TYPE}")
    endif()
    set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${TARGET_DEFS}")
endfunction()