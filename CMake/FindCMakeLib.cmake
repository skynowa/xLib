#--------------------------------------------------------------------------------------------------
# \file  FindCMakeLib.cmake
# \brief Find CMakeLib
#
# CMAKELIB_FOUND    - true if system has library
# CMAKELIB_INCLUDES - includes path
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
unset(CMAKELIB_FOUND    CACHE)
unset(CMAKELIB_INCLUDES CACHE)

if (NOT XLIB_LOCATION)
    set(CMAKELIB_FOUND 0)
    set(CMAKELIB_INCLUDES "")

    message(FATAL_ERROR "XLIB_LOCATION: ${XLIB_LOCATION}")
endif()

find_path(CMAKELIB_INCLUDES
    NAMES
        "Find[BIN_NAME].cmake.template"
    PATHS
        "${XLIB_LOCATION}/../CMakeLib"
    PATH_SUFFIXES
        "CMakeLib")

if (NOT CMAKELIB_INCLUDES)
    set(CMAKELIB_FOUND 0)
    set(CMAKELIB_INCLUDES "")
else()
    set(CMAKELIB_FOUND 1)
endif()
#--------------------------------------------------------------------------------------------------
# trace
if (NOT CMAKELIB_FOUND AND CMakeLib_FIND_REQUIRED)
    message(FATAL_ERROR "CMAKELIB_FOUND: ${CMAKELIB_FOUND}")
else()
    message(STATUS "CMAKELIB_FOUND: ${CMAKELIB_FOUND}")
    # message("     CMAKELIB_INCLUDES: ${CMAKELIB_INCLUDES}")
endif()
#--------------------------------------------------------------------------------------------------
