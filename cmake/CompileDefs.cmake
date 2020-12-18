if (MSVC)
    set(GALAXY_COMPILE_FLAGS
        /QIntel-jcc-erratum
        /std:c++latest
        /sdl
        /W0
        /WX-
        /MP
        /GF
        /EHsc
        /fp:except
        /fp:precise
        /bigobj
        /Zc:preprocessor
        /Y-
        /experimental:external
        /external:anglebrackets
        /external:W0
    )

    set(GALAXY_COMPILE_FLAGS_DEBUG
        ${GALAXY_COMPILE_FLAGS}
        /JMC
        /ZI
        /Od
        /RTC1
        /MTd
        /GS
        /GR
    )

    set(GALAXY_COMPILE_FLAGS_RELEASE
        ${GALAXY_COMPILE_FLAGS}
        /O2
        /Oi
        /Ot
        /GL
        /MT
        /GS-
        /Gy
        /GR-
    )
else()
    set(GALAXY_COMPILE_FLAGS
        -stdlib=libc++
        -flto
        -fcxx-exceptions
        -fexceptions
        -fseh-exceptions
        -pthread
        -fchar8_t
        -fcoroutines-ts
        -frtti
        -fvirtual-function-elimination
    )

    set(GALAXY_COMPILE_FLAGS_DEBUG
        ${GALAXY_COMPILE_FLAGS}
        --analyze
        -Wall
        -Og
        -g3
    )

    set(GALAXY_COMPILE_FLAGS_RELEASE
        ${GALAXY_COMPILE_FLAGS}
        -O3
        -w
    )
endif()