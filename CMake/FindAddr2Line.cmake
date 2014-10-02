#--------------------------------------------------------------------------------------------------
# \file  FindAddr2Line.cmake
# \brief Find addr2Line
#
# ADDR2LINE_FOUND     - true if found
# ADDR2LINE_FILE_PATH - where to find includes
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
find_file(ADDR2LINE_FILE_PATH "addr2line")

if (ADDR2LINE_FILE_PATH STREQUAL "ADDR2LINE_FILE_PATH-NOTFOUND")
    set(ADDR2LINE_FOUND 0)
    set(ADDR2LINE_FILE_PATH "")
else()
    set(ADDR2LINE_FOUND 1)
endif()

#--------------------------------------------------------------------------------------------------
# trace
if (NOT ADDR2LINE_FOUND AND ADDR2LINE_FIND_REQUIRED)
    message(FATAL_ERROR "ADDR2LINE_FOUND: ${ADDR2LINE_FOUND}")
else()
    message(STATUS "ADDR2LINE_FOUND: ${ADDR2LINE_FOUND}")
    # message("     ADDR2LINE_FILE_PATH: ${ADDR2LINE_FILE_PATH}")
endif()
