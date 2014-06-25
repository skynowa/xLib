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
unset(xHAVE_CPP11             CACHE)
unset(xHAVE_NAMESPACE_XLIB    CACHE)
unset(xHAVE_DEBUG_DIALOG      CACHE)
unset(xHAVE_DEBUG_MODE_MSGBOX CACHE)
unset(xHAVE_DEBUG_MODE_STDOUT CACHE)
unset(xHAVE_DEBUG_MODE_LOG    CACHE)
unset(xHAVE_DEBUG_MODE_NO     CACHE)
unset(xHAVE_TEST_PRIVATE      CACHE)
unset(xHAVE_TEST_TRACING      CACHE)
unset(xHAVE_TESTS             CACHE)

option(xHAVE_CPP11             "support C++11 language"                   0)
option(xHAVE_NAMESPACE_XLIB    "automatically include the xlib namespace" 1)
option(xHAVE_DEBUG_DIALOG      "debug prompt dialog"                      1)
option(xHAVE_DEBUG_MODE_MSGBOX "debug mode 'message box with plain text'" 0)
option(xHAVE_DEBUG_MODE_STDOUT "debug mode 'std::out with plain text'"    1)
option(xHAVE_DEBUG_MODE_LOG    "debug mode 'logging with plain text'"     0)
option(xHAVE_DEBUG_MODE_NO     "debug mode 'no debugging'"                0)
option(xHAVE_TEST_PRIVATE      "tests private data"                       0)
option(xHAVE_TEST_TRACING      "use tracing in tests"                     1)
option(xHAVE_TESTS             "use xLib tests"                           0)

# trace options
# message("")
# message("******************** Options *********************")
# message("* xHAVE_CPP11:             ${xHAVE_CPP11}")
# message("* xHAVE_NAMESPACE_XLIB:    ${xHAVE_NAMESPACE_XLIB}")
# message("* xHAVE_DEBUG_DIALOG:      ${xHAVE_DEBUG_DIALOG}")
# message("* xHAVE_DEBUG_MODE_MSGBOX: ${xHAVE_DEBUG_MODE_MSGBOX}")
# message("* xHAVE_DEBUG_MODE_STDOUT: ${xHAVE_DEBUG_MODE_STDOUT}")
# message("* xHAVE_DEBUG_MODE_LOG:    ${xHAVE_DEBUG_MODE_LOG}")
# message("* xHAVE_DEBUG_MODE_NO:     ${xHAVE_DEBUG_MODE_NO}")
# message("* xHAVE_TEST_PRIVATE:      ${xHAVE_TEST_PRIVATE}")
# message("* xHAVE_TEST_TRACING:      ${xHAVE_TEST_TRACING}")
# message("* xHAVE_TESTS:             ${xHAVE_TESTS}")
# message("**************************************************")
# message("")

#--------------------------------------------------------------------------------------------------
# internal vars
unset(XLIB_LIBS        CACHE)
unset(XLIB_FLAGS       CACHE)
unset(XLIB_DEFINITIONS CACHE)

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(CMake/Configure.cmake)
# include(CMake/CMakeVariables.cmake)

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
if (xHAVE_TESTS)
    file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")
else()
    file(GLOB_RECURSE xLib_tests_SOURCES "Tests/Test.cpp")
endif()

#--------------------------------------------------------------------------------------------------
# target
add_executable(${PROJECT_NAME} ${xLib_tests_SOURCES})

#--------------------------------------------------------------------------------------------------
# definitions
if (xHAVE_CPP11)
    set(CXX_STANDARD "c++11")
    add_definitions(-std=c++11)
endif()

#--------------------------------------------------------------------------------------------------
# libs, flags
if     (MSVC)
    set(XLIB_FLAGS "${XLIB_FLAGS} /W3")
elseif (MINGW)
    set(XLIB_LIBS ${XLIB_LIBS} ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
    set(XLIB_FLAGS "${XLIB_FLAGS} -pipe -Wall")
        # -pedantic
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(XLIB_LIBS ${XLIB_LIBS} pthread rt m z)
    set(XLIB_FLAGS "${XLIB_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror "
        "-fcolor-diagnostics -Qunused-arguments")
        # -pedantic
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(XLIB_LIBS ${XLIB_LIBS} pthread rt m z)
    set(XLIB_FLAGS "${XLIB_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror")
        # -pedantic
else()
    message("xLib: unknown compiler")
endif()

if (OS_ANDROID)
    unset(XLIB_LIBS        CACHE)
    unset(XLIB_FLAGS       CACHE)
    unset(XLIB_DEFINITIONS CACHE)

    set(XLIB_LIBS gnustl_static m z log)
    set(XLIB_FLAGS "${XLIB_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow")
    set(XLIB_FLAGS "${XLIB_FLAGS} -Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas")
    set(XLIB_FLAGS "${XLIB_FLAGS} -frtti -fexceptions")
    set(XLIB_DEFINITIONS "")
endif()

if (XLIB_DEFINITIONS)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS ${XLIB_DEFINITIONS})
    message("XLIB_DEFINITIONS: ${XLIB_DEFINITIONS}")
endif()

if (XLIB_FLAGS)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${XLIB_FLAGS})
    message("XLIB_FLAGS: ${XLIB_FLAGS}")
endif()

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
