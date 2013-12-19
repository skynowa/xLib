#--------------------------------------------------------------------------------------------------
# \file  FindMySQL.cmake
# \brief Find the native MySQL includes and library
#
# MYSQL_INCLUDES  - where to find mysql.h, etc
# MYSQL_LIBRARIES - list of libraries when using MySQL
# MYSQL_FOUND     - true if MySQL found
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

if (MYSQL_FOUND)
    message(STATUS "Found MySQL: ${MYSQL_LIBRARY}")
else()
    if (MYSQL_FIND_REQUIRED)
        message(STATUS "Looked for MySQL libraries named ${MYSQL_NAMES}.")
        message(FATAL_ERROR "Could not find MySQL library")
    endif()
endif()

MARK_AS_ADVANCED(MYSQL_INCLUDES MYSQL_LIBRARY)
