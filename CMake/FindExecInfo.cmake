#--------------------------------------------------------------------------------------------------
# \file  FindExecInfo.cmake
# \brief Find libexecinfo
#
# EXECINFO_FOUND     - true if libexecinfo found
# EXECINFO_INCLUDES  - where to find libexecinfo includes
# EXECINFO_LIBRARIES - list of libraries when using libexecinfo
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
find_path(EXECINFO_INCLUDES "execinfo.h")
find_library(EXECINFO_LIBRARIES NAMES "execinfo")

if (EXECINFO_INCLUDES STREQUAL "EXECINFO_INCLUDES-NOTFOUND")
    set(EXECINFO_FOUND 0)
    set(EXECINFO_INCLUDES "")
    set(EXECINFO_LIBRARIES "")
else()
    set(EXECINFO_FOUND 1)

    if (EXECINFO_LIBRARIES STREQUAL "EXECINFO_LIBRARIES-NOTFOUND")
        # Built-in, no further action is needed
        set(EXECINFO_LIBRARIES "")
    endif()
endif()

#--------------------------------------------------------------------------------------------------
# trace
if (NOT EXECINFO_FOUND AND EXECINFO_FIND_REQUIRED)
    message(FATAL_ERROR "EXECINFO_FOUND: ${EXECINFO_FOUND}")
else()
    message(STATUS "EXECINFO_FOUND: ${EXECINFO_FOUND}")
    # message("     EXECINFO_INCLUDES: ${EXECINFO_INCLUDES}")
    # message("     EXECINFO_LIBRARIES: ${EXECINFO_LIBRARIES}")
endif()
