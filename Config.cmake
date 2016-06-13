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
    set(cmOPTION_PROJECT_HEADER_ONLY   ON  CACHE BOOL "Project: header only" FORCE PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_STATIC    OFF CACHE BOOL "Project: static library" FORCE PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library" FORCE PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library" FORCE PARENT_SCOPE)
    set(cmOPTION_BUILD_TESTS           ON  CACHE BOOL "Build tests" FORCE PARENT_SCOPE)

    set(cmOPTION_CPP11                 OFF CACHE BOOL "Support C++11 language" FORCE PARENT_SCOPE)
    set(cmOPTION_UNICODE               OFF  CACHE BOOL "Support unicode" FORCE PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_MSGBOX     OFF CACHE BOOL "Debug mode: message box" FORCE PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_STDOUT     ON  CACHE BOOL "Debug mode: std::cout" FORCE PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_LOG        OFF CACHE BOOL "Debug mode: logging" FORCE PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_STDOUT_LOG OFF CACHE BOOL "Debug mode: std::cout and logging" FORCE PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_EXCEPTION  OFF CACHE BOOL "Debug mode: exception" FORCE PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_NO         OFF CACHE BOOL "Debug mode: no debugging" FORCE PARENT_SCOPE)
    set(cmOPTION_BUILD_MSG             OFF CACHE BOOL "Build messages" FORCE PARENT_SCOPE)
    set(cmOPTION_TEST_PRIVATE          OFF CACHE BOOL "Test private data" FORCE PARENT_SCOPE)
    set(cmOPTION_TEST_TRACING          ON  CACHE BOOL "Use tracing in tests" FORCE PARENT_SCOPE)
else()
    set(cmOPTION_PROJECT_HEADER_ONLY   ON  CACHE BOOL "Project: header only" FORCE)
    set(cmOPTION_PROJECT_LIB_STATIC    OFF CACHE BOOL "Project: static library" FORCE)
    set(cmOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library" FORCE)
    set(cmOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library" FORCE)
    set(cmOPTION_BUILD_TESTS           ON  CACHE BOOL "Build tests" FORCE)

    set(cmOPTION_CPP11                 OFF CACHE BOOL "Support C++11 language" FORCE)
    set(cmOPTION_UNICODE               OFF  CACHE BOOL "Support unicode" FORCE)
    set(cmOPTION_DEBUG_MODE_MSGBOX     OFF CACHE BOOL "Debug mode: message box" FORCE)
    set(cmOPTION_DEBUG_MODE_STDOUT     ON  CACHE BOOL "Debug mode: std::cout" FORCE)
    set(cmOPTION_DEBUG_MODE_LOG        OFF CACHE BOOL "Debug mode: logging" FORCE)
    set(cmOPTION_DEBUG_MODE_STDOUT_LOG OFF CACHE BOOL "Debug mode: std::cout and logging" FORCE)
    set(cmOPTION_DEBUG_MODE_EXCEPTION  OFF CACHE BOOL "Debug mode: exception" FORCE)
    set(cmOPTION_DEBUG_MODE_NO         OFF CACHE BOOL "Debug mode: no debugging" FORCE)
    set(cmOPTION_BUILD_MSG             OFF CACHE BOOL "Build messages" FORCE)
    set(cmOPTION_TEST_PRIVATE          OFF CACHE BOOL "Test private data" FORCE)
    set(cmOPTION_TEST_TRACING          ON  CACHE BOOL "Use tracing in tests" FORCE)
endif()

message("")
message(STATUS "cmOPTION_PROJECT_HEADER_ONLY   : ${cmOPTION_PROJECT_HEADER_ONLY}")
message(STATUS "cmOPTION_PROJECT_LIB_STATIC    : ${cmOPTION_PROJECT_LIB_STATIC}")
message(STATUS "cmOPTION_PROJECT_LIB_SHARE     : ${cmOPTION_PROJECT_LIB_SHARE}")
message(STATUS "cmOPTION_PROJECT_LIB_MODULE    : ${cmOPTION_PROJECT_LIB_MODULE}")
message(STATUS "cmOPTION_BUILD_TESTS           : ${cmOPTION_BUILD_TESTS}")
message("")
message(STATUS "cmOPTION_CPP11                 : ${cmOPTION_CPP11}")
message(STATUS "cmOPTION_UNICODE               : ${cmOPTION_UNICODE}")
# message(STATUS "cmOPTION_DEBUG_MODE_MSGBOX     : ${cmOPTION_DEBUG_MODE_MSGBOX}")
# message(STATUS "cmOPTION_DEBUG_MODE_STDOUT     : ${cmOPTION_DEBUG_MODE_STDOUT}")
# message(STATUS "cmOPTION_DEBUG_MODE_LOG        : ${cmOPTION_DEBUG_MODE_LOG}")
# message(STATUS "cmOPTION_DEBUG_MODE_STDOUT_LOG : ${cmOPTION_DEBUG_MODE_STDOUT_LOG}")
# message(STATUS "cmOPTION_DEBUG_MODE_EXCEPTION  : ${cmOPTION_DEBUG_MODE_EXCEPTION}")
# message(STATUS "cmOPTION_DEBUG_MODE_NO         : ${cmOPTION_DEBUG_MODE_NO}")
# message(STATUS "cmOPTION_BUILD_MSG             : ${cmOPTION_BUILD_MSG}")
# message(STATUS "cmOPTION_TEST_PRIVATE          : ${cmOPTION_TEST_PRIVATE}")
# message(STATUS "cmOPTION_TEST_TRACING          : ${cmOPTION_TEST_TRACING}")
# message("")
#--------------------------------------------------------------------------------------------------
