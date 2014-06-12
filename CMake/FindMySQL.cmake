#--------------------------------------------------------------------------------------------------
# \file  FindMySQL.cmake
# \brief Find the native MySQL includes and library
#
# MYSQL_FOUND     - true if MySQL found
# MYSQL_INCLUDES  - where to find mysql.h, etc
# MYSQL_LIBRARIES - list of libraries when using MySQL
#--------------------------------------------------------------------------------------------------


find_path(MYSQL_INCLUDES
    NAMES "mysql.h"
    PATH_SUFFIXES "mysql"
)

set(MYSQL_NAMES mysqlclient mysqlclient_r)
find_library(MYSQL_LIBRARY
    NAMES ${MYSQL_NAMES}
    PATHS "/usr/lib" "/usr/local/lib"
    PATH_SUFFIXES mysql
)

if (MYSQL_INCLUDES AND MYSQL_LIBRARY)
    set(MYSQL_FOUND TRUE)
    set(MYSQL_LIBRARIES ${MYSQL_LIBRARY})
else()
    set(MYSQL_FOUND FALSE)
    set(MYSQL_LIBRARIES "")
endif()

#--------------------------------------------------------------------------------------------------
# trace
if (NOT MYSQL_FOUND AND MYSQL_FIND_REQUIRED)
    message(FATAL_ERROR "MYSQL_FOUND: ${MYSQL_FOUND}")
else()
    message(STATUS "MYSQL_FOUND: ${MYSQL_FOUND}")
endif()

MARK_AS_ADVANCED(MYSQL_INCLUDES MYSQL_LIBRARY)
