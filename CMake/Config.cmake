#--------------------------------------------------------------------------------------------------
# \file  Config.cmake
# \brief Config for xLib
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# options (system)
set(PROJECT_TYPE                  CXX)
set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS          OFF)
set(CMAKE_COLOR_MAKEFILE          ON)
set(CMAKE_VERBOSE_MAKEFILE        OFF)
set(CMAKE_REQUIRED_QUIET          ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMAKE_CONFIGURATION_TYPES:
# - None
# - Debug
# - Release
# - RelWithDebInfo
# - MinSizeRel
#
# Sample: "Debug;Release;RelWithDebInfo"
# FAQ: https://stackoverflow.com/a/59724462/911398
#
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Release - default build type" FORCE)
endif()

set(cmCMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
#--------------------------------------------------------------------------------------------------
# options
set(cmOPTION_PROJECT_LIB_TYPE      STATIC) # STATIC/SHARED/MODULE
set(OPTION_UNICODE                 0)
set(cmOPTION_DEBUG_MODE_MSGBOX     0)
set(cmOPTION_DEBUG_MODE_STDOUT     1)
set(cmOPTION_DEBUG_MODE_LOG        0)
set(cmOPTION_DEBUG_MODE_STDOUT_LOG 0)
set(cmOPTION_DEBUG_MODE_EXCEPTION  0)
set(cmOPTION_DEBUG_MODE_NO         0)
set(cmOPTION_BUILD_MSG             0)
set(cmXLIB_DATA_DIR                "/home/runner/work/xLib/xLib/xLib/Data")   # Github CI
#--------------------------------------------------------------------------------------------------
# Trace
message("-------------------------------------------------")
message(STATUS "PROJECT_NAME                   : ${PROJECT_NAME}")
message("CMake")
message(STATUS "CMAKE_VERSION                  : ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR                : ${CMAKE_GENERATOR}")
message(STATUS "CMAKE_GENERATOR_PLATFORM       : ${CMAKE_GENERATOR_PLATFORM}")
message(STATUS "CMAKE_ECLIPSE_VERSION          : ${CMAKE_ECLIPSE_VERSION}")
message(STATUS "CMAKE_MAKE_PROGRAM             : ${CMAKE_MAKE_PROGRAM}")
message(STATUS "CMAKE_SYSTEM_NAME              : ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PREFIX_PATH       : ${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "Complier                       : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_CXX_STANDARD             : ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CONFIGURATION_TYPES      : ${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "cmCMAKE_BUILD_TYPE             : ${cmCMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_BUILD_PARALLEL_LEVEL     : ${CMAKE_BUILD_PARALLEL_LEVEL}")
message(STATUS "CMAKE_ROOT                     : ${CMAKE_ROOT}")
message(STATUS "CMAKE_INSTALL_PREFIX           : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_SOURCE_DIR               : ${CMAKE_SOURCE_DIR}")
# message(STATUS "CMAKE_CXX_COMPILE_FEATURES     : ${CMAKE_CXX_COMPILE_FEATURES}")
message("")
message("Options")
message(STATUS "cmOPTION_PROJECT_LIB_TYPE      : ${cmOPTION_PROJECT_LIB_TYPE}")
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
