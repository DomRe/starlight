if (MSVC)
    set(GALAXY_COMPILE_FLAGS
        /QIntel-jcc-erratum
        /std:c++latest
        /W0
        /WX-
        /MP
        /GF
        /EHsc
        /fp:except
        /fp:precise
        /bigobj
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
        /sdl
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
        -fconcepts
        -fcoroutines
        -frtti
        -fvisibility-ms-compat
        -fexceptions
        -pthread
    )

    set(GALAXY_COMPILE_FLAGS_DEBUG
        ${GALAXY_COMPILE_FLAGS}
        -Wall
        -Wextra
        -fanalyzer
        -g3
        -Og
    )

    set(GALAXY_COMPILE_FLAGS_RELEASE
        ${GALAXY_COMPILE_FLAGS}
        -w
        -O3
    )
endif()