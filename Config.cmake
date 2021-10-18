#--------------------------------------------------------------------------------------------------
# \file  Config.cmake
# \brief Config for xLib
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
set(PROJECT_TYPE                  CXX)
set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS          OFF)
set(CMAKE_COLOR_MAKEFILE          ON)
set(CMAKE_VERBOSE_MAKEFILE        OFF)
set(CMAKE_REQUIRED_QUIET          ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	# "clangd.arguments": ['-compile-commands-dir="../xLib_eclipse"' ]
# message("CMAKE_CXX_COMPILE_FEATURES: ${CMAKE_CXX_COMPILE_FEATURES}")
#--------------------------------------------------------------------------------------------------
# options
set(cmOPTION_PROJECT_LIB_STATIC 1)
set(cmOPTION_PROJECT_LIB_SHARE  0) # TODO: build - fix
set(cmOPTION_PROJECT_LIB_MODULE 0) # TODO: build - fix
set(cmOPTION_BUILD_TESTS        1)

if (cmOPTION_PROJECT_LIB_STATIC)
	set(CMAKE_STATIC_LINKER_FLAGS_STRING machine:X64)
endif()

if (cmOPTION_PROJECT_LIB_SHARE)
	set(CMAKE_SHARED_LINKER_FLAGS_STRING machine:X64)
endif()

if (cmOPTION_PROJECT_LIB_MODULE)
	set(CMAKE_MODULE_LINKER_FLAGS_STRING machine:X64)
endif()

if (cmOPTION_BUILD_TESTS)
	set(CMAKE_EXE_LINKER_FLAGS_STRING machine:X64)
endif()

# Local host - No tests
cmake_host_system_information(RESULT cmHOST_NAME QUERY HOSTNAME)
if (${cmHOST_NAME} STREQUAL "skynowa-pc")
	set(cmOPTION_BUILD_TESTS 1)
endif()

# CMAKE_CONFIGURATION_TYPES:
# - None
# - Debug
# - Release
# - RelWithDebInfo
# - MinSizeRel
set(CMAKE_CONFIGURATION_TYPES      "Debug;Release;RelWithDebInfo" STRING "")
set(CMAKE_BUILD_TYPE               "RelWithDebInfo")

set(OPTION_UNICODE                 0)
set(cmOPTION_DEBUG_MODE_MSGBOX     0)
set(cmOPTION_DEBUG_MODE_STDOUT     1)
set(cmOPTION_DEBUG_MODE_LOG        0)
set(cmOPTION_DEBUG_MODE_STDOUT_LOG 0)
set(cmOPTION_DEBUG_MODE_EXCEPTION  0)
set(cmOPTION_DEBUG_MODE_NO         0)
set(cmOPTION_BUILD_MSG             0)

message("-------------------------------------------------")
message("CMake")
message(STATUS "CMAKE_VERSION                  : ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR                : ${CMAKE_GENERATOR}")
message(STATUS "CMAKE_SYSTEM_NAME              : ${CMAKE_SYSTEM_NAME}")
message(STATUS "Complier                       : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_CXX_STANDARD             : ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CONFIGURATION_TYPES      : ${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "CMAKE_BUILD_TYPE               : ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_ROOT                     : ${CMAKE_ROOT}")
message("")
message("Options")
message(STATUS "cmOPTION_PROJECT_LIB_STATIC    : ${cmOPTION_PROJECT_LIB_STATIC}")
message(STATUS "cmOPTION_PROJECT_LIB_SHARE     : ${cmOPTION_PROJECT_LIB_SHARE}")
message(STATUS "cmOPTION_PROJECT_LIB_MODULE    : ${cmOPTION_PROJECT_LIB_MODULE}")
message(STATUS "cmOPTION_BUILD_TESTS           : ${cmOPTION_BUILD_TESTS}")
message("")
message(STATUS "OPTION_UNICODE                 : ${OPTION_UNICODE}")
message(STATUS "cmOPTION_DEBUG_MODE_MSGBOX     : ${cmOPTION_DEBUG_MODE_MSGBOX}")
message(STATUS "cmOPTION_DEBUG_MODE_STDOUT     : ${cmOPTION_DEBUG_MODE_STDOUT}")
message(STATUS "cmOPTION_DEBUG_MODE_LOG        : ${cmOPTION_DEBUG_MODE_LOG}")
message(STATUS "cmOPTION_DEBUG_MODE_STDOUT_LOG : ${cmOPTION_DEBUG_MODE_STDOUT_LOG}")
message(STATUS "cmOPTION_DEBUG_MODE_EXCEPTION  : ${cmOPTION_DEBUG_MODE_EXCEPTION}")
message(STATUS "cmOPTION_DEBUG_MODE_NO         : ${cmOPTION_DEBUG_MODE_NO}")
message(STATUS "cmOPTION_BUILD_MSG             : ${cmOPTION_BUILD_MSG}")
message("-------------------------------------------------")
message("")
#--------------------------------------------------------------------------------------------------
