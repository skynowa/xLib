#--------------------------------------------------------------------------------------------------
# \file  FindCMakeLib.cmake
# \brief Find CMakeLib
#
# CMAKELIB_FOUND - true if system has library
# CMAKELIB_PATH  - lobrary path
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
unset(CMAKELIB_FOUND CACHE)
unset(CMAKELIB_PATH  CACHE)

find_path(CMAKELIB_PATH
    NAMES
        "Find[BIN_NAME].cmake.template"
    PATHS
        "${XLIB_LOCATION}/../CMakeLib"
    PATH_SUFFIXES
        "CMakeLib")

if (NOT CMAKELIB_PATH)
    set(CMAKELIB_FOUND 0)
    set(CMAKELIB_PATH  "")
else()
    set(CMAKELIB_FOUND 1)
endif()
#--------------------------------------------------------------------------------------------------
# trace
if (NOT CMAKELIB_FOUND AND CMakeLib_FIND_REQUIRED)
    message(FATAL_ERROR "CMAKELIB_FOUND: ${CMAKELIB_FOUND}")
else()
    message(STATUS "CMAKELIB_FOUND: ${CMAKELIB_FOUND}")
    # message("     CMAKELIB_PATH: ${CMAKELIB_PATH}")
endif()
#--------------------------------------------------------------------------------------------------
