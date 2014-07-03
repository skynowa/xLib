#--------------------------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib_test)

set(PROJECT_TYPE "CXX")
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    # None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
    # Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
    # Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
    # RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
    # MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)

#--------------------------------------------------------------------------------------------------
# options
unset(xOPTION_PROJECT_EXE       CACHE)
unset(xOPTION_PROJECT_LIB       CACHE)
unset(xOPTION_PROJECT_DLL       CACHE)
unset(xOPTION_CPP11             CACHE)
unset(xOPTION_NAMESPACE_XLIB    CACHE)
unset(xOPTION_DEBUG_DIALOG      CACHE)
unset(xOPTION_DEBUG_MODE_MSGBOX CACHE)
unset(xOPTION_DEBUG_MODE_STDOUT CACHE)
unset(xOPTION_DEBUG_MODE_LOG    CACHE)
unset(xOPTION_DEBUG_MODE_NO     CACHE)
unset(xOPTION_TEST_PRIVATE      CACHE)
unset(xOPTION_TEST_TRACING      CACHE)
unset(xOPTION_TESTS             CACHE)
unset(xOPTION_BUILD_MSG         CACHE)

option(xOPTION_PROJECT_EXE       "Project: executable binary"               1)
option(xOPTION_PROJECT_LIB       "Project: static library"                  0)
option(xOPTION_PROJECT_DLL       "Project: share (dynamic-link) library"    0)
option(xOPTION_CPP11             "Support C++11 language"                   0)
option(xOPTION_NAMESPACE_XLIB    "Automatically include the xlib namespace" 1)
option(xOPTION_DEBUG_DIALOG      "Debug prompt dialog"                      1)
option(xOPTION_DEBUG_MODE_MSGBOX "Debug mode: message box with plain text"  0)
option(xOPTION_DEBUG_MODE_STDOUT "Debug mode: std::out with plain text"     1)
option(xOPTION_DEBUG_MODE_LOG    "Debug mode: logging with plain text"      0)
option(xOPTION_DEBUG_MODE_NO     "Debug mode: no debugging"                 0)
option(xOPTION_TEST_PRIVATE      "Tests private data"                       0)
option(xOPTION_TEST_TRACING      "Use tracing in tests"                     1)
option(xOPTION_TESTS             "Use xLib tests"                           0)
option(xOPTION_BUILD_MSG         "Build messages"                           0)

# trace options
# message("")
# message("******************** Options *********************")
# message("* xOPTION_PROJECT_EXE:       ${xOPTION_PROJECT_EXE}")
# message("* xOPTION_PROJECT_LIB:       ${xOPTION_PROJECT_LIB}")
# message("* xOPTION_PROJECT_DLL:       ${xOPTION_PROJECT_DLL}")
# message("* xOPTION_CPP11:             ${xOPTION_CPP11}")
# message("* xOPTION_NAMESPACE_XLIB:    ${xOPTION_NAMESPACE_XLIB}")
# message("* xOPTION_DEBUG_DIALOG:      ${xOPTION_DEBUG_DIALOG}")
# message("* xOPTION_DEBUG_MODE_MSGBOX: ${xOPTION_DEBUG_MODE_MSGBOX}")
# message("* xOPTION_DEBUG_MODE_STDOUT: ${xOPTION_DEBUG_MODE_STDOUT}")
# message("* xOPTION_DEBUG_MODE_LOG:    ${xOPTION_DEBUG_MODE_LOG}")
# message("* xOPTION_DEBUG_MODE_NO:     ${xOPTION_DEBUG_MODE_NO}")
# message("* xOPTION_TEST_PRIVATE:      ${xOPTION_TEST_PRIVATE}")
# message("* xOPTION_TEST_TRACING:      ${xOPTION_TEST_TRACING}")
# message("* xOPTION_TESTS:             ${xOPTION_TESTS}")
# message("* xOPTION_BUILD_MSG:         ${xOPTION_BUILD_MSG}")
# message("**************************************************")
# message("")

#--------------------------------------------------------------------------------------------------
# internal vars
unset(XLIB_LIBS        CACHE)
unset(XLIB_DEFINITIONS CACHE)

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(CMake/Configure.cmake)

#--------------------------------------------------------------------------------------------------
# includes, libs
include_directories("${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")

if (OPENSSL_FOUND)
    include_directories("${OPENSSL_INCLUDE_DIR}")
    link_libraries(${OPENSSL_LIBRARIES})
endif()

if (MYSQL_FOUND)
    include_directories("${MYSQL_INCLUDES}")
    link_libraries(${MYSQL_LIBRARIES})
endif()

if (ENV_UNIX)
    if (XCB_FOUND)
        include_directories("${XCB_INCLUDE_DIR}")
        link_libraries(${XCB_LIBRARIES})
    endif()

    if (EXECINFO_FOUND)
        include_directories(${EXECINFO_INCLUDES})
        link_libraries(${EXECINFO_LIBRARIES})
    endif()

    if (OS_ANDROID)
        # set(ANDROID_NDK "/opt/Libs/Android/NDK")
        # include_directories("${ANDROID_NDK}/platforms/android-9/arch-arm/usr/include")
        # link_libraries()
    endif()
endif()

#--------------------------------------------------------------------------------------------------
# vars
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGCC 1)
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

set(XLIB_INSTALL_DIR  include/xLib)
set(XLIB_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${XLIB_INSTALL_DIR}")

#--------------------------------------------------------------------------------------------------
# sources
if (xOPTION_TESTS)
    file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")
else()
    file(GLOB_RECURSE xLib_tests_SOURCES "Tests/Test.cpp")
endif()

#--------------------------------------------------------------------------------------------------
# target
add_executable(${PROJECT_NAME} ${xLib_tests_SOURCES})

#--------------------------------------------------------------------------------------------------
# definitions
if (xOPTION_CPP11)
    set(CXX_STANDARD "c++11")
    add_definitions(-std=c++11)
endif()

#--------------------------------------------------------------------------------------------------
# libs, flags
include(CMake/CxxFlags.cmake)
include(CMake/CMakeVariables.cmake)

if     (MSVC)
    set(XLIB_DEFINITIONS "")
elseif (MINGW)
    set(XLIB_LIBS ${XLIB_LIBS} ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
    set(XLIB_DEFINITIONS "")
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(XLIB_LIBS ${XLIB_LIBS} pthread rt m z)
    set(XLIB_DEFINITIONS "")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(XLIB_LIBS ${XLIB_LIBS} pthread rt m z)
    set(XLIB_DEFINITIONS "")
else()
    message("xLib: unknown compiler")
endif()

if (OS_ANDROID)
    unset(XLIB_LIBS        CACHE)
    unset(XLIB_DEFINITIONS CACHE)

    set(XLIB_LIBS gnustl_static m z log)
    set(XLIB_DEFINITIONS "")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XLIB_DEFINITIONS}")

target_link_libraries(${PROJECT_NAME} ${XLIB_LIBS} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

#--------------------------------------------------------------------------------------------------
# install
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/Include/xLib/
    DESTINATION ${XLIB_INSTALL_PATH}
    FILES_MATCHING PATTERN "*" PATTERN "*.h.in" EXCLUDE)

#--------------------------------------------------------------------------------------------------
# uninstall
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

#--------------------------------------------------------------------------------------------------
# fix warning "Manually-specified variables were not used by the project"
unset(CMAKE_TOOLCHAIN_FILE)
