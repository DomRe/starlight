set(GALAXY_COMPILE_FLAGS_DEBUG
    /QIntel-jcc-erratum
    /std:c++latest
    /WX-
    /MP
    /GF
    /EHsc
    /fp:except
    /fp:precise
    /bigobj
    /Y-
    /Wall
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
    /QIntel-jcc-erratum
    /std:c++latest
    /WX-
    /MP
    /GF
    /EHsc
    /fp:except
    /fp:precise
    /bigobj
    /Y-
    /w
    /O2
    /Oi
    /Ot
    /GL
    /MT
    /GS-
    /Gy
    /GR-
)