#--------------------------------------------------------------------------------------------------
# \file  FindxLib.cmake
# \brief Find xLib
#
# XLIB_LOCATION    - root diractory [in]
# XLIB_FOUND       - found or not
# XLIB_DEFINITIONS - definitions
# XLIB_INCLUDES    - include pathes
# XLIB_SOURCES     - source pathes
# XLIB_LIBRARIES   - libraries list
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# options
unset(xOPTION_PROJECT_HEADER_ONLY   CACHE)
unset(xOPTION_PROJECT_LIB_STATIC    CACHE)
unset(xOPTION_PROJECT_LIB_SHARE     CACHE)
unset(xOPTION_PROJECT_LIB_MODULE    CACHE)
unset(xOPTION_PROJECT_TESTS         CACHE)
unset(xOPTION_CPP11                 CACHE)
unset(xOPTION_DEBUG_DIALOG          CACHE)
unset(xOPTION_DEBUG_MODE_MSGBOX     CACHE)
unset(xOPTION_DEBUG_MODE_STDOUT     CACHE)
unset(xOPTION_DEBUG_MODE_LOG        CACHE)
unset(xOPTION_DEBUG_MODE_STDOUT_LOG CACHE)
unset(xOPTION_DEBUG_MODE_NO         CACHE)
unset(xOPTION_BUILD_MSG             CACHE)
unset(xOPTION_TESTS                 CACHE)
unset(xOPTION_TEST_PRIVATE          CACHE)
unset(xOPTION_TEST_TRACING          CACHE)

option(xOPTION_PROJECT_HEADER_ONLY   "Project: header only"              0)
option(xOPTION_PROJECT_LIB_STATIC    "Project: static library"           0)
option(xOPTION_PROJECT_LIB_SHARE     "Project: share library"            0)
option(xOPTION_PROJECT_LIB_MODULE    "Project: dynamic-link library"     0)
option(xOPTION_PROJECT_TESTS         "Project: tests"                    1)

option(xOPTION_CPP11                 "Support C++11 language"            0)
option(xOPTION_DEBUG_DIALOG          "Debug prompt dialog"               0)
option(xOPTION_DEBUG_MODE_MSGBOX     "Debug mode: message box"           0)
option(xOPTION_DEBUG_MODE_STDOUT     "Debug mode: std::cout"             0)
option(xOPTION_DEBUG_MODE_LOG        "Debug mode: logging"               0)
option(xOPTION_DEBUG_MODE_STDOUT_LOG "Debug mode: std::cout and logging" 1)
option(xOPTION_DEBUG_MODE_NO         "Debug mode: no debugging"          0)
option(xOPTION_BUILD_MSG             "Build messages"                    0)
option(xOPTION_TESTS                 "Use tests"                         1)
option(xOPTION_TEST_PRIVATE          "Test private data"                 0)
option(xOPTION_TEST_TRACING          "Use tracing in tests"              1)

message("")
message(STATUS "xOPTION_PROJECT_HEADER_ONLY   : ${xOPTION_PROJECT_HEADER_ONLY}")
message(STATUS "xOPTION_PROJECT_LIB_STATIC    : ${xOPTION_PROJECT_LIB_STATIC}")
message(STATUS "xOPTION_PROJECT_LIB_SHARE     : ${xOPTION_PROJECT_LIB_SHARE}")
message(STATUS "xOPTION_PROJECT_LIB_MODULE    : ${xOPTION_PROJECT_LIB_MODULE}")
message(STATUS "xOPTION_PROJECT_TESTS         : ${xOPTION_PROJECT_TESTS}")
message("")
# message(STATUS "xOPTION_CPP11                 : ${xOPTION_CPP11}")
# message(STATUS "xOPTION_DEBUG_DIALOG          : ${xOPTION_DEBUG_DIALOG}")
# message(STATUS "xOPTION_DEBUG_MODE_MSGBOX     : ${xOPTION_DEBUG_MODE_MSGBOX}")
# message(STATUS "xOPTION_DEBUG_MODE_STDOUT     : ${xOPTION_DEBUG_MODE_STDOUT}")
# message(STATUS "xOPTION_DEBUG_MODE_LOG        : ${xOPTION_DEBUG_MODE_LOG}")
# message(STATUS "xOPTION_DEBUG_MODE_STDOUT_LOG : ${xOPTION_DEBUG_MODE_STDOUT_LOG}")
# message(STATUS "xOPTION_DEBUG_MODE_NO         : ${xOPTION_DEBUG_MODE_NO}")
# message(STATUS "xOPTION_BUILD_MSG             : ${xOPTION_BUILD_MSG}")
# message(STATUS "xOPTION_TESTS                 : ${xOPTION_TESTS}")
# message(STATUS "xOPTION_TEST_PRIVATE          : ${xOPTION_TEST_PRIVATE}")
# message(STATUS "xOPTION_TEST_TRACING          : ${xOPTION_TEST_TRACING}")
# message("")
#--------------------------------------------------------------------------------------------------
