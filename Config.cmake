#--------------------------------------------------------------------------------------------------
# \file  Config.cmake
# \brief Config for xLib
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# options
get_directory_property(IS_PARENT_SCOPE PARENT_DIRECTORY)

if (IS_PARENT_SCOPE)
    set(cmOPTION_PROJECT_HEADER_ONLY   ON  BOOL "Project: header only" PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_STATIC    OFF BOOL "Project: static library" PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_SHARE     OFF BOOL "Project: share library" PARENT_SCOPE)
    set(cmOPTION_PROJECT_LIB_MODULE    OFF BOOL "Project: dynamic-link library" PARENT_SCOPE)
    set(cmOPTION_BUILD_TESTS           ON  BOOL "Build tests" PARENT_SCOPE)

    set(CMAKE_CONFIGURATION_TYPES      "Debug;Release;RelWithDebInfo" STRING "" PARENT_SCOPE)
    set(CMAKE_BUILD_TYPE               "RelWithDebInfo" PARENT_SCOPE)

    set(OPTION_CPP11                   OFF  BOOL "Support C++11 language" PARENT_SCOPE)
    set(OPTION_UNICODE                 OFF BOOL "Support unicode" PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_MSGBOX     OFF BOOL "Debug mode: message box" PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_STDOUT     ON  BOOL "Debug mode: std::cout" PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_LOG        OFF BOOL "Debug mode: logging" PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_STDOUT_LOG OFF BOOL "Debug mode: std::cout and logging" PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_EXCEPTION  OFF BOOL "Debug mode: exception" PARENT_SCOPE)
    set(cmOPTION_DEBUG_MODE_NO         OFF BOOL "Debug mode: no debugging" PARENT_SCOPE)
    set(cmOPTION_BUILD_MSG             OFF BOOL "Build messages" PARENT_SCOPE)
    set(cmOPTION_TEST_PRIVATE          OFF BOOL "Test private data" PARENT_SCOPE)
    set(cmOPTION_TEST_TRACING          ON  BOOL "Use tracing in tests" PARENT_SCOPE)
else()
    set(cmOPTION_PROJECT_HEADER_ONLY   ON  BOOL "Project: header only")
    set(cmOPTION_PROJECT_LIB_STATIC    OFF BOOL "Project: static library")
    set(cmOPTION_PROJECT_LIB_SHARE     OFF BOOL "Project: share library")
    set(cmOPTION_PROJECT_LIB_MODULE    OFF BOOL "Project: dynamic-link library")
    set(cmOPTION_BUILD_TESTS           ON BOOL "Build tests")

    set(CMAKE_CONFIGURATION_TYPES      "Debug;Release;RelWithDebInfo" STRING "")
    set(CMAKE_BUILD_TYPE               "RelWithDebInfo")
        # None           (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
        # Debug          (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
        # Release        (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
        # RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
        # MinSizeRel     (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)

    set(OPTION_CPP11                   OFF  BOOL "Support C++11 language")
    set(OPTION_UNICODE                 OFF BOOL "Support unicode")
    set(cmOPTION_DEBUG_MODE_MSGBOX     OFF BOOL "Debug mode: message box")
    set(cmOPTION_DEBUG_MODE_STDOUT     ON  BOOL "Debug mode: std::cout")
    set(cmOPTION_DEBUG_MODE_LOG        OFF BOOL "Debug mode: logging")
    set(cmOPTION_DEBUG_MODE_STDOUT_LOG OFF BOOL "Debug mode: std::cout and logging")
    set(cmOPTION_DEBUG_MODE_EXCEPTION  OFF BOOL "Debug mode: exception")
    set(cmOPTION_DEBUG_MODE_NO         OFF BOOL "Debug mode: no debugging")
    set(cmOPTION_BUILD_MSG             OFF BOOL "Build messages")
    set(cmOPTION_TEST_PRIVATE          OFF BOOL "Test private data")
    set(cmOPTION_TEST_TRACING          ON  BOOL "Use tracing in tests")
endif()

message("")
message(STATUS "cmOPTION_PROJECT_HEADER_ONLY   : ${cmOPTION_PROJECT_HEADER_ONLY}")
message(STATUS "cmOPTION_PROJECT_LIB_STATIC    : ${cmOPTION_PROJECT_LIB_STATIC}")
message(STATUS "cmOPTION_PROJECT_LIB_SHARE     : ${cmOPTION_PROJECT_LIB_SHARE}")
message(STATUS "cmOPTION_PROJECT_LIB_MODULE    : ${cmOPTION_PROJECT_LIB_MODULE}")
message(STATUS "cmOPTION_BUILD_TESTS           : ${cmOPTION_BUILD_TESTS}")
message("")
message(STATUS "CMAKE_BUILD_TYPE               : ${CMAKE_BUILD_TYPE}")
message(STATUS "OPTION_CPP11                   : ${OPTION_CPP11}")
message(STATUS "OPTION_UNICODE                 : ${OPTION_UNICODE}")
message(STATUS "cmOPTION_DEBUG_MODE_MSGBOX     : ${cmOPTION_DEBUG_MODE_MSGBOX}")
message(STATUS "cmOPTION_DEBUG_MODE_STDOUT     : ${cmOPTION_DEBUG_MODE_STDOUT}")
message(STATUS "cmOPTION_DEBUG_MODE_LOG        : ${cmOPTION_DEBUG_MODE_LOG}")
message(STATUS "cmOPTION_DEBUG_MODE_STDOUT_LOG : ${cmOPTION_DEBUG_MODE_STDOUT_LOG}")
message(STATUS "cmOPTION_DEBUG_MODE_EXCEPTION  : ${cmOPTION_DEBUG_MODE_EXCEPTION}")
message(STATUS "cmOPTION_DEBUG_MODE_NO         : ${cmOPTION_DEBUG_MODE_NO}")
message(STATUS "cmOPTION_BUILD_MSG             : ${cmOPTION_BUILD_MSG}")
message(STATUS "cmOPTION_TEST_PRIVATE          : ${cmOPTION_TEST_PRIVATE}")
message(STATUS "cmOPTION_TEST_TRACING          : ${cmOPTION_TEST_TRACING}")
message("")
#--------------------------------------------------------------------------------------------------
