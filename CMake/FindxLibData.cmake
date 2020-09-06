#--------------------------------------------------------------------------------------------------
# \file  FindxLibData.cmake
# \brief Find xLib-data
#
# XLIB_DATA_FOUND - true if system has library
# cmXLIB_DATA_DIR - directory path
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
unset(XLIB_DATA_FOUND CACHE)
unset(cmXLIB_DATA_DIR CACHE)

if (NOT XLIB_LOCATION)
    set(XLIB_DATA_FOUND 0)

    message(FATAL_ERROR "XLIB_LOCATION: ${XLIB_LOCATION}")
endif()

find_path(cmXLIB_DATA_DIR
    NAMES
        "xLib-data"
    PATHS
        "${XLIB_LOCATION}/.."
		"~/work/xLib"
    PATH_SUFFIXES
        "")

if (NOT cmXLIB_DATA_DIR)
    set(XLIB_DATA_FOUND 0)
else()
    set(cmXLIB_DATA_DIR "${cmXLIB_DATA_DIR}/xLib-data")
    set(XLIB_DATA_FOUND 1)
endif()
#--------------------------------------------------------------------------------------------------
# trace
if (NOT XLIB_DATA_FOUND AND xLibData_FIND_REQUIRED)
    message(FATAL_ERROR "XLIB_DATA_FOUND: ${XLIB_DATA_FOUND}")
else()
    message(STATUS "XLIB_DATA_FOUND: ${XLIB_DATA_FOUND}")
    message("   cmXLIB_DATA_DIR: ${cmXLIB_DATA_DIR}")
endif()
#--------------------------------------------------------------------------------------------------
