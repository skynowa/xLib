#--------------------------------------------------------------------------------------------------
# \file  Config.cmake
# \brief Config for xLib
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# options (system)
set(PROJECT_TYPE                  CXX)

# C++
set(CMAKE_CXX_STANDARD            20)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS          OFF)

# C
set(CMAKE_C_STANDARD              17)
set(CMAKE_C_STANDARD_REQUIRED     ON)
set(CMAKE_C_EXTENSIONS            OFF)

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
	# set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Release - default build type" FORCE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Release - default build type" FORCE)
endif()

set(cmCMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})

string(TIMESTAMP cmBUILD_TS "%Y-%m-%d %H:%M:%S")
#--------------------------------------------------------------------------------------------------
# options
set(cmOPTION_PROJECT_LIB_TYPE STATIC) # STATIC/SHARED/MODULE
set(OPTION_UNICODE            0)
set(cmOPTION_BUILD_MSG        0)
# set(cmXLIB_DATA_DIR           "/home/runner/work/xLib/xLib/xLib/Data")   # Github CI
get_filename_component(cmXLIB_DATA_DIR "./Data" ABSOLUTE)
#--------------------------------------------------------------------------------------------------
# Trace
message("-------------------------------------------------")
message(STATUS "CMAKE_PROJECT_NAME             : ${CMAKE_PROJECT_NAME}")
message(STATUS "PROJECT_NAME                   : ${PROJECT_NAME}")
message("CMake")
message(STATUS "CMAKE_VERSION                  : ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR                : ${CMAKE_GENERATOR}")
message(STATUS "CMAKE_GENERATOR_PLATFORM       : ${CMAKE_GENERATOR_PLATFORM}")
message(STATUS "CMAKE_ECLIPSE_VERSION          : ${CMAKE_ECLIPSE_VERSION}")
message(STATUS "CMAKE_MAKE_PROGRAM             : ${CMAKE_MAKE_PROGRAM}")
message(STATUS "CMAKE_SYSTEM_NAME              : ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PREFIX_PATH       : ${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "CMAKE_CXX_COMPILER_ID          : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION     : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_CXX_STANDARD             : ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_C_STANDARD               : ${CMAKE_C_STANDARD}")
message(STATUS "CMAKE_CONFIGURATION_TYPES      : ${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "cmCMAKE_BUILD_TYPE             : ${cmCMAKE_BUILD_TYPE}")
message(STATUS "cmBUILD_TS                     : ${cmBUILD_TS}")
message(STATUS "CMAKE_BUILD_PARALLEL_LEVEL     : ${CMAKE_BUILD_PARALLEL_LEVEL}")
message(STATUS "CMAKE_ROOT                     : ${CMAKE_ROOT}")
message(STATUS "CMAKE_INSTALL_PREFIX           : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_SOURCE_DIR               : ${CMAKE_SOURCE_DIR}")
# message(STATUS "CMAKE_CXX_COMPILE_FEATURES     : ${CMAKE_CXX_COMPILE_FEATURES}")
message("")
message("Options")
message(STATUS "cmOPTION_PROJECT_LIB_TYPE      : ${cmOPTION_PROJECT_LIB_TYPE}")
message(STATUS "OPTION_UNICODE                 : ${OPTION_UNICODE}")
message(STATUS "cmOPTION_BUILD_MSG             : ${cmOPTION_BUILD_MSG}")
message(STATUS "cmXLIB_DATA_DIR                : ${cmXLIB_DATA_DIR}")
message("-------------------------------------------------")
message("")
#--------------------------------------------------------------------------------------------------
