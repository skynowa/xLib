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
unset(xOPTION_PROJECT_HEADER_ONLY CACHE)
unset(xOPTION_PROJECT_LIB_STATIC  CACHE)
unset(xOPTION_PROJECT_LIB_SHARE   CACHE)
unset(xOPTION_PROJECT_LIB_MODULE  CACHE)
unset(xOPTION_PROJECT_EXE         CACHE)
unset(xOPTION_CPP11               CACHE)
unset(xOPTION_NAMESPACE_XLIB      CACHE)
unset(xOPTION_DEBUG_DIALOG        CACHE)
unset(xOPTION_DEBUG_MODE_MSGBOX   CACHE)
unset(xOPTION_DEBUG_MODE_STDOUT   CACHE)
unset(xOPTION_DEBUG_MODE_LOG      CACHE)
unset(xOPTION_DEBUG_MODE_NO       CACHE)
unset(xOPTION_BUILD_MSG           CACHE)
unset(xOPTION_TESTS               CACHE)
unset(xOPTION_TEST_PRIVATE        CACHE)
unset(xOPTION_TEST_TRACING        CACHE)

option(xOPTION_PROJECT_HEADER_ONLY "Project: header only"                     0)
option(xOPTION_PROJECT_LIB_STATIC  "Project: static library"                  0)
option(xOPTION_PROJECT_LIB_SHARE   "Project: share library"                   0)
option(xOPTION_PROJECT_LIB_MODULE  "Project: dynamic-link library"            0)
option(xOPTION_PROJECT_EXE         "Project: tests"                           1)
option(xOPTION_CPP11               "Support C++11 language"                   0)
option(xOPTION_NAMESPACE_XLIB      "Automatically include the xlib namespace" 0)
option(xOPTION_DEBUG_DIALOG        "Debug prompt dialog"                      1)
option(xOPTION_DEBUG_MODE_MSGBOX   "Debug mode: message box with plain text"  0)
option(xOPTION_DEBUG_MODE_STDOUT   "Debug mode: std::out with plain text"     1)
option(xOPTION_DEBUG_MODE_LOG      "Debug mode: logging with plain text"      0)
option(xOPTION_DEBUG_MODE_NO       "Debug mode: no debugging"                 0)
option(xOPTION_BUILD_MSG           "Build messages"                           0)
option(xOPTION_TESTS               "Use tests"                                1)
option(xOPTION_TEST_PRIVATE        "Test private data"                        0)
option(xOPTION_TEST_TRACING        "Use tracing in tests"                     1)

#--------------------------------------------------------------------------------------------------
