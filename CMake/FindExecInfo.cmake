#--------------------------------------------------------------------------------------------------
# \file  FindExecInfo.cmake
# \brief Find libexecinfo
#
# EXECINFO_INCLUDES  - where to find libexecinfo includes
# EXECINFO_LIBRARIES - list of libraries when using libexecinfo
# EXECINFO_FOUND     - true if libexecinfo found
#--------------------------------------------------------------------------------------------------


find_path(EXECINFO_INCLUDES "execinfo.h")
find_library(EXECINFO_LIBRARIES NAMES "execinfo")

if (EXECINFO_INCLUDES STREQUAL "EXECINFO_INCLUDES-NOTFOUND")
    set(EXECINFO_FOUND FALSE)
    set(EXECINFO_INCLUDES "")
    set(EXECINFO_LIBRARIES "")
else()
    set(EXECINFO_FOUND TRUE)

    if (EXECINFO_LIBRARIES STREQUAL "EXECINFO_LIBRARIES-NOTFOUND")
        # Built-in, no further action is needed
        set(EXECINFO_LIBRARIES "")
        message(STATUS "Found execinfo: (built-in)")
    else()
        # It's an external library.
        message(STATUS "Found execinfo: ${EXECINFO_LIBRARIES}")
    endif()
endif()

if (NOT EXECINFO_FOUND)
    if (EXECINFO_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find execinfo library")
    endif()
endif()
