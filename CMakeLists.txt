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

option(xHAVE_CPP11             "support C++11 language"                   OFF)
option(xHAVE_NAMESPACE_XLIB    "automatically include the xlib namespace" ON)
option(xHAVE_DEBUG_DIALOG      "debug prompt dialog"                      ON)
option(xHAVE_DEBUG_MODE_MSGBOX "debug mode 'message box with plain text'" OFF)
option(xHAVE_DEBUG_MODE_STDOUT "debug mode 'std::out with plain text'"    ON)
option(xHAVE_DEBUG_MODE_LOG    "debug mode 'logging with plain text'"     OFF)
option(xHAVE_DEBUG_MODE_NO     "debug mode 'no debugging'"                OFF)
option(xHAVE_TEST_PRIVATE      "tests private data"                       OFF)
option(xHAVE_TEST_TRACING      "use tracing in tests"                     ON)
option(xHAVE_TESTS             "use xLib tests"                           ON)

# trace options
message("")
message("******************** Options *********************")
message("* xHAVE_CPP11:             ${xHAVE_CPP11}")
message("* xHAVE_NAMESPACE_XLIB:    ${xHAVE_NAMESPACE_XLIB}")
message("* xHAVE_DEBUG_DIALOG:      ${xHAVE_DEBUG_DIALOG}")
message("* xHAVE_DEBUG_MODE_MSGBOX: ${xHAVE_DEBUG_MODE_MSGBOX}")
message("* xHAVE_DEBUG_MODE_STDOUT: ${xHAVE_DEBUG_MODE_STDOUT}")
message("* xHAVE_DEBUG_MODE_LOG:    ${xHAVE_DEBUG_MODE_LOG}")
message("* xHAVE_DEBUG_MODE_NO:     ${xHAVE_DEBUG_MODE_NO}")
message("* xHAVE_TEST_PRIVATE:      ${xHAVE_TEST_PRIVATE}")
message("* xHAVE_TEST_TRACING:      ${xHAVE_TEST_TRACING}")
message("* xHAVE_TESTS:             ${xHAVE_TESTS}")
message("**************************************************")
message("")

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(Configure)
include(CMake/CMakeVars.cmake)

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

if (UNIX)
    if (XCB_FOUND)
        include_directories("${XCB_INCLUDE_DIR}")
        link_libraries(${XCB_LIBRARIES})
    endif()

    if (EXECINFO_FOUND)
        include_directories(${EXECINFO_INCLUDES})
        link_libraries(${EXECINFO_LIBRARIES})
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
# flags
if     (MSVC)
    set(FLAGS ${FLAGS} "/W3")
elseif (MINGW)
    set(LIBS ${LIBS} ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
    set(FLAGS ${FLAGS} "-pipe -Wall")
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(LIBS ${LIBS} pthread rt m z)
    set(FLAGS ${FLAGS} "-pipe -Wall -pedantic -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror "
        "-fcolor-diagnostics -Qunused-arguments")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(LIBS ${LIBS} pthread rt m z)
    set(FLAGS ${FLAGS} "-pipe -Wall -pedantic -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror "
        "")
else()
    message("xLib: unknown compiler")
endif()

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
        # COMPILE_DEFINITIONS ${DEFINITIONS}
        COMPILE_FLAGS ${FLAGS}
)

target_link_libraries(${PROJECT_NAME} ${LIBS} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

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
