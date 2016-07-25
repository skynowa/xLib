#--------------------------------------------------------------------------------------------------
# \file  Config.cmake
# \brief Config for xLib
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# options
get_directory_property(IS_PARENT_SCOPE PARENT_DIRECTORY)

if (IS_PARENT_SCOPE)
    set(cmOPTION_PROJECT_HEADER_ONLY   OFF  CACHE BOOL "Project: header only" FORCE PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_STATIC    ON CACHE BOOL "Project: static library" FORCE PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library" FORCE PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library" FORCE PARENT_SCOPE)
    set(cmOPTION_BUILD_TESTS           ON  CACHE BOOL "Build tests" FORCE PARENT_SCOPE)

    set(OPTION_CPP11                   OFF  CACHE BOOL "Support C++11 language" FORCE PARENT_SCOPE)
    set(OPTION_UNICODE                 OFF CACHE BOOL "Support unicode" FORCE PARENT_SCOPE)
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
    set(cmOPTION_PROJECT_HEADER_ONLY   OFF  CACHE BOOL "Project: header only" FORCE)
    set(cmOPTION_PROJECT_LIB_STATIC    ON CACHE BOOL "Project: static library" FORCE)
    set(cmOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library" FORCE)
    set(cmOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library" FORCE)
    set(cmOPTION_BUILD_TESTS           ON CACHE BOOL "Build tests" FORCE)

    set(OPTION_CPP11                   OFF  CACHE BOOL "Support C++11 language" FORCE)
    set(OPTION_UNICODE                 OFF CACHE BOOL "Support unicode" FORCE)
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
message(STATUS "OPTION_CPP11                   : ${OPTION_CPP11}")
message(STATUS "OPTION_UNICODE                 : ${OPTION_UNICODE}")
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
