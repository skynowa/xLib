#--------------------------------------------------------------------------------------------------
# \file  FindxLib.cmake
# \brief Find xLib
#
# XLIB_LOCATION    - root diractory [in]
# XLIB_FOUND       - found or not
# XLIB_DEFINITIONS - definitions
# XLIB_INCLUDES    - include pathes
# XLIB_LIBRARIES   - libraries list
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib)
set(PROJECT_TYPE "CXX")

#--------------------------------------------------------------------------------------------------
# options
unset(xOPTION_PROJECT_HEADER_ONLY CACHE)
unset(xOPTION_PROJECT_STATIC      CACHE)
unset(xOPTION_PROJECT_SHARE       CACHE)
unset(xOPTION_PROJECT_MODULE      CACHE)
unset(xOPTION_PROJECT_TESTS       CACHE)

unset(xOPTION_CPP11               CACHE)
unset(xOPTION_NAMESPACE_XLIB      CACHE)
unset(xOPTION_DEBUG_DIALOG        CACHE)
unset(xOPTION_DEBUG_MODE_MSGBOX   CACHE)
unset(xOPTION_DEBUG_MODE_STDOUT   CACHE)
unset(xOPTION_DEBUG_MODE_LOG      CACHE)
unset(xOPTION_DEBUG_MODE_NO       CACHE)
unset(xOPTION_BUILD_MSG           CACHE)

option(xOPTION_PROJECT_HEADER_ONLY "Project: header only"                     0)
option(xOPTION_PROJECT_STATIC      "Project: static library"                  1)
option(xOPTION_PROJECT_SHARE       "Project: share library"                   1)
option(xOPTION_PROJECT_MODULE      "Project: dynamic-link library"            1)
option(xOPTION_PROJECT_TESTS       "Project: tests"                           0)

option(xOPTION_CPP11               "Support C++11 language"                   0)
option(xOPTION_NAMESPACE_XLIB      "Automatically include the xlib namespace" 1)
option(xOPTION_DEBUG_DIALOG        "Debug prompt dialog"                      1)
option(xOPTION_DEBUG_MODE_MSGBOX   "Debug mode: message box with plain text"  0)
option(xOPTION_DEBUG_MODE_STDOUT   "Debug mode: std::out with plain text"     1)
option(xOPTION_DEBUG_MODE_LOG      "Debug mode: logging with plain text"      0)
option(xOPTION_DEBUG_MODE_NO       "Debug mode: no debugging"                 0)

option(xOPTION_BUILD_MSG           "Build messages"                           0)

# trace options
# message("")
# message("******************** Options *********************")
# message("* xOPTION_PROJECT_HEADER_ONLY: ${xOPTION_PROJECT_HEADER_ONLY}")
# message("* xOPTION_PROJECT_STATIC:      ${xOPTION_PROJECT_STATIC}")
# message("* xOPTION_PROJECT_SHARE:       ${xOPTION_PROJECT_SHARE}")
# message("* xOPTION_PROJECT_MODULE:      ${xOPTION_PROJECT_MODULE}")
# message("* xOPTION_PROJECT_TESTS:       ${xOPTION_PROJECT_TESTS}")

# message("* xOPTION_CPP11:               ${xOPTION_CPP11}")
# message("* xOPTION_NAMESPACE_XLIB:      ${xOPTION_NAMESPACE_XLIB}")
# message("* xOPTION_DEBUG_DIALOG:        ${xOPTION_DEBUG_DIALOG}")
# message("* xOPTION_DEBUG_MODE_MSGBOX:   ${xOPTION_DEBUG_MODE_MSGBOX}")
# message("* xOPTION_DEBUG_MODE_STDOUT:   ${xOPTION_DEBUG_MODE_STDOUT}")
# message("* xOPTION_DEBUG_MODE_LOG:      ${xOPTION_DEBUG_MODE_LOG}")
# message("* xOPTION_DEBUG_MODE_NO:       ${xOPTION_DEBUG_MODE_NO}")
# message("* xOPTION_BUILD_MSG:           ${xOPTION_BUILD_MSG}")
# message("**************************************************")
# message("")

#--------------------------------------------------------------------------------------------------
# vars
unset(XLIB_FOUND       CACHE)
unset(XLIB_DEFINITIONS CACHE)
unset(XLIB_INCLUDES    CACHE)
unset(XLIB_LIBRARIES   CACHE)

unset(XLIB_LOCATION    CACHE)

if (NOT XLIB_LOCATION)
    set(XLIB_LOCATION ${CMAKE_SOURCE_DIR})
endif()

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH ${XLIB_LOCATION}/CMake)
include(Configure)

#--------------------------------------------------------------------------------------------------
# includes, libs
set(XLIB_INCLUDES ${XLIB_INCLUDES} ${XLIB_LOCATION}/Include)
file(GLOB_RECURSE XLIB_SOURCES ${XLIB_LOCATION}/Include/*.cpp)

if (OPENSSL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${OPENSSL_INCLUDE_DIR})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${OPENSSL_LIBRARIES})
endif()

if (MYSQL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${MYSQL_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${MYSQL_LIBRARIES})
endif()

if (ENV_UNIX)
    if (XCB_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${XCB_INCLUDE_DIR})
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${XCB_LIBRARIES})
    endif()

    if (EXECINFO_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${EXECINFO_INCLUDES})
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${EXECINFO_LIBRARIES})
    endif()

    if (OS_ANDROID)
        # set(ANDROID_NDK "/opt/Libs/Android/NDK")
        # set(XLIB_INCLUDES ${XLIB_INCLUDES} "${ANDROID_NDK}/platforms/android-9/arch-arm/usr/include")
        # set(XLIB_LIBRARIES ${XLIB_LIBRARIES})
    endif()
endif()

#--------------------------------------------------------------------------------------------------
# definitions, libs, flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XLIB_DEFINITIONS}")

#--------------------------------------------------------------------------------------------------
# includes, libs
include_directories(${XLIB_INCLUDES})
link_libraries(${XLIB_LIBRARIES})

#--------------------------------------------------------------------------------------------------
# vars
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGCC 1)
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

set(XLIB_INSTALL_DIR  include/xLib)
set(XLIB_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/${XLIB_INSTALL_DIR})

#--------------------------------------------------------------------------------------------------
# flags
include(CxxFlags)
# include(CMakeVariables)

#--------------------------------------------------------------------------------------------------
# definitions
if (xOPTION_CPP11)
    set(CXX_STANDARD "c++11")
    # add_definitions(-std=c++11)
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} "-std=c++11")
endif()

#--------------------------------------------------------------------------------------------------
# libraries
set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

if     (MSVC)

elseif (MINGW)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} pthread rt m z)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} pthread rt m z)
else()
    message("xLib: unknown compiler")
endif()

if (OS_ANDROID)
    unset(XLIB_DEFINITIONS CACHE)
    unset(XLIB_LIBRARIES   CACHE)

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} gnustl_static m z log)
endif()

if (NOT (XLIB_INCLUDES AND XLIB_LIBRARIES))
    set(XLIB_FOUND 0)
    set(XLIB_DEFINITIONS "")
    set(XLIB_INCLUDES "")
    set(XLIB_LIBRARIES "")
else()
    set(XLIB_FOUND 1)
endif()

#--------------------------------------------------------------------------------------------------
# targets
if (xOPTION_PROJECT_HEADER_ONLY)

endif()

if (xOPTION_PROJECT_STATIC)
    add_library(${PROJECT_NAME}_static STATIC ${XLIB_SOURCES})
endif()

if (xOPTION_PROJECT_SHARE)
    add_library(${PROJECT_NAME}_shared SHARED ${XLIB_SOURCES})
endif()

if (xOPTION_PROJECT_MODULE)
    add_library(${PROJECT_NAME}_module MODULE ${XLIB_SOURCES})
endif()

if (xOPTION_PROJECT_TESTS)
    # TODO:
endif()

#--------------------------------------------------------------------------------------------------
# install
# install(
#     DIRECTORY ${XLIB_LOCATION}/Include/xLib/
#     DESTINATION ${XLIB_INSTALL_PATH}
#     FILES_MATCHING PATTERN "*" PATTERN "*.h.in" EXCLUDE)

#--------------------------------------------------------------------------------------------------
# uninstall
configure_file(
    ${XLIB_LOCATION}/CMake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

#--------------------------------------------------------------------------------------------------
# fix warning "Manually-specified variables were not used by the project"
unset(CMAKE_TOOLCHAIN_FILE)

#--------------------------------------------------------------------------------------------------
# trace
if (NOT XLIB_FOUND AND XLIB_FIND_REQUIRED)
    message(FATAL_ERROR "XLIB_FOUND: ${XLIB_FOUND}")
else()
    message(STATUS "XLIB_FOUND: ${XLIB_FOUND}")
    # message("    XLIB_LOCATION: ${XLIB_LOCATION}")
    # message("    XLIB_DEFINITIONS: ${XLIB_DEFINITIONS}")
    # message("    XLIB_INCLUDES: ${XLIB_INCLUDES}")
    # message("    XLIB_LIBRARIES: ${XLIB_LIBRARIES}")
endif()
