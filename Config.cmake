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
get_directory_property(IS_PARENT_SCOPE PARENT_DIRECTORY)

if (IS_PARENT_SCOPE)
    set(xOPTION_PROJECT_HEADER_ONLY   ON  CACHE BOOL "Project: header only" FORCE PARENT_SCOPE)
    set(xOPTION_PROJECT_LIB_STATIC    OFF CACHE BOOL "Project: static library" FORCE PARENT_SCOPE)
    set(xOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library" FORCE PARENT_SCOPE)
    set(xOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library" FORCE PARENT_SCOPE)
    set(xOPTION_BUILD_TESTS           ON  CACHE BOOL "Build tests" FORCE PARENT_SCOPE)

    set(xOPTION_CPP11                 OFF CACHE BOOL "Support C++11 language" FORCE PARENT_SCOPE)
    set(xOPTION_UNICODE               ON  CACHE BOOL "Support unicode" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_DIALOG          OFF CACHE BOOL "Debug prompt dialog" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_MODE_MSGBOX     OFF CACHE BOOL "Debug mode: message box" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_MODE_STDOUT     ON  CACHE BOOL "Debug mode: std::cout" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_MODE_LOG        OFF CACHE BOOL "Debug mode: logging" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_MODE_STDOUT_LOG OFF CACHE BOOL "Debug mode: std::cout and logging" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_MODE_EXCEPTION  OFF CACHE BOOL "Debug mode: exception" FORCE PARENT_SCOPE)
    set(xOPTION_DEBUG_MODE_NO         OFF CACHE BOOL "Debug mode: no debugging" FORCE PARENT_SCOPE)
    set(xOPTION_BUILD_MSG             OFF CACHE BOOL "Build messages" FORCE PARENT_SCOPE)
    set(xOPTION_TEST_PRIVATE          OFF CACHE BOOL "Test private data" FORCE PARENT_SCOPE)
    set(xOPTION_TEST_TRACING          ON  CACHE BOOL "Use tracing in tests" FORCE PARENT_SCOPE)
else()
    set(xOPTION_PROJECT_HEADER_ONLY   ON  CACHE BOOL "Project: header only" FORCE)
    set(xOPTION_PROJECT_LIB_STATIC    OFF CACHE BOOL "Project: static library" FORCE)
    set(xOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library" FORCE)
    set(xOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library" FORCE)
    set(xOPTION_BUILD_TESTS           ON  CACHE BOOL "Build tests" FORCE)

    set(xOPTION_CPP11                 OFF CACHE BOOL "Support C++11 language" FORCE)
    set(xOPTION_UNICODE               OFF  CACHE BOOL "Support unicode" FORCE)
    set(xOPTION_DEBUG_DIALOG          OFF CACHE BOOL "Debug prompt dialog" FORCE)
    set(xOPTION_DEBUG_MODE_MSGBOX     OFF CACHE BOOL "Debug mode: message box" FORCE)
    set(xOPTION_DEBUG_MODE_STDOUT     ON  CACHE BOOL "Debug mode: std::cout" FORCE)
    set(xOPTION_DEBUG_MODE_LOG        OFF CACHE BOOL "Debug mode: logging" FORCE)
    set(xOPTION_DEBUG_MODE_STDOUT_LOG OFF CACHE BOOL "Debug mode: std::cout and logging" FORCE)
    set(xOPTION_DEBUG_MODE_EXCEPTION  OFF CACHE BOOL "Debug mode: exception" FORCE)
    set(xOPTION_DEBUG_MODE_NO         OFF CACHE BOOL "Debug mode: no debugging" FORCE)
    set(xOPTION_BUILD_MSG             OFF CACHE BOOL "Build messages" FORCE)
    set(xOPTION_TEST_PRIVATE          OFF CACHE BOOL "Test private data" FORCE)
    set(xOPTION_TEST_TRACING          ON  CACHE BOOL "Use tracing in tests" FORCE)
endif()

message("")
message(STATUS "xOPTION_PROJECT_HEADER_ONLY   : ${xOPTION_PROJECT_HEADER_ONLY}")
message(STATUS "xOPTION_PROJECT_LIB_STATIC    : ${xOPTION_PROJECT_LIB_STATIC}")
message(STATUS "xOPTION_PROJECT_LIB_SHARE     : ${xOPTION_PROJECT_LIB_SHARE}")
message(STATUS "xOPTION_PROJECT_LIB_MODULE    : ${xOPTION_PROJECT_LIB_MODULE}")
message(STATUS "xOPTION_BUILD_TESTS           : ${xOPTION_BUILD_TESTS}")
message("")
message(STATUS "xOPTION_CPP11                 : ${xOPTION_CPP11}")
message(STATUS "xOPTION_UNICODE               : ${xOPTION_UNICODE}")
# message(STATUS "xOPTION_DEBUG_DIALOG          : ${xOPTION_DEBUG_DIALOG}")
# message(STATUS "xOPTION_DEBUG_MODE_MSGBOX     : ${xOPTION_DEBUG_MODE_MSGBOX}")
# message(STATUS "xOPTION_DEBUG_MODE_STDOUT     : ${xOPTION_DEBUG_MODE_STDOUT}")
# message(STATUS "xOPTION_DEBUG_MODE_LOG        : ${xOPTION_DEBUG_MODE_LOG}")
# message(STATUS "xOPTION_DEBUG_MODE_STDOUT_LOG : ${xOPTION_DEBUG_MODE_STDOUT_LOG}")
# message(STATUS "xOPTION_DEBUG_MODE_EXCEPTION  : ${xOPTION_DEBUG_MODE_EXCEPTION}")
# message(STATUS "xOPTION_DEBUG_MODE_NO         : ${xOPTION_DEBUG_MODE_NO}")
# message(STATUS "xOPTION_BUILD_MSG             : ${xOPTION_BUILD_MSG}")
# message(STATUS "xOPTION_TEST_PRIVATE          : ${xOPTION_TEST_PRIVATE}")
# message(STATUS "xOPTION_TEST_TRACING          : ${xOPTION_TEST_TRACING}")
# message("")
#--------------------------------------------------------------------------------------------------
