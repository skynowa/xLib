#--------------------------------------------------------------------------------------------------
# \file  FindxLibData.cmake
# \brief Find xLib-data
#
# cmXLIB_DATA_FOUND - true if system has library
# cmXLIB_DATA_DIR   - directory path
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
unset(cmXLIB_DATA_FOUND CACHE)
unset(cmXLIB_DATA_DIR   CACHE)

if (NOT XLIB_LOCATION)
    set(cmXLIB_DATA_FOUND 0)

    message(FATAL_ERROR "XLIB_LOCATION: ${XLIB_LOCATION}")
endif()

find_path(cmXLIB_DATA_DIR
    NAMES
        "xLib-data"
    PATHS
        "${XLIB_LOCATION}/.."
        "/home/runner/work/xLib/xLib"	# Github CI
    PATH_SUFFIXES
        "")

if (NOT cmXLIB_DATA_DIR)
    set(cmXLIB_DATA_FOUND 0)
else()
    set(cmXLIB_DATA_DIR "${cmXLIB_DATA_DIR}/xLib-data")
    set(cmXLIB_DATA_FOUND 1)
endif()
#--------------------------------------------------------------------------------------------------
# trace
if (NOT cmXLIB_DATA_FOUND AND xLibData_FIND_REQUIRED)
    message(FATAL_ERROR "cmXLIB_DATA_FOUND: ${cmXLIB_DATA_FOUND}")
else()
    message(STATUS "cmXLIB_DATA_FOUND: ${cmXLIB_DATA_FOUND}")
    message("   cmXLIB_DATA_DIR: ${cmXLIB_DATA_DIR}")
endif()
#--------------------------------------------------------------------------------------------------
