#--------------------------------------------------------------------------------------------------
# \file  FindExecInfo.cmake
# brief  Find libexecinfo
#
# EXECINFO_INCLUDES  - where to find libexecinfo includes
# EXECINFO_LIBRARIES - list of libraries when using libexecinfo
# EXECINFO_FOUND     - true if libexecinfo found
#--------------------------------------------------------------------------------------------------


find_path(EXECINFO_INCLUDES "execinfo.h")

if (EXECINFO_INCLUDES STREQUAL "EXECINFO_INCLUDES-NOTFOUND")
    set(EXECINFO_INCLUDES "")
else()
    # Now determine if it's built-in or not, by searching the library file.
    find_library(EXECINFO_LIBRARIES "execinfo")

    if (EXECINFO_LIBRARIES STREQUAL "EXECINFO_LIBRARIES-NOTFOUND")
        # Built-in, no further action is needed
        set(EXECINFO_LIBRARIES "")
        message(STATUS "Found execinfo: (built-in)")
    else()
        # It's an external library.
        message(STATUS "Found execinfo: ${EXECINFO_LIBRARIES}")
    endif()

    set(EXECINFO_FOUND TRUE)
endif()
