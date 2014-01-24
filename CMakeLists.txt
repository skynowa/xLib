#--------------------------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib_test)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    # None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
    # Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
    # Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
    # RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
    # MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)

#--------------------------------------------------------------------------------------------------
# options
unset(xUSING_NAMESPACE_XLIB    CACHE)
unset(xDEBUG_USE_PROMPT_DIALOG CACHE)
unset(xDEBUG_MODE_MSGBOX       CACHE)
unset(xDEBUG_MODE_STDOUT       CACHE)
unset(xDEBUG_MODE_LOG          CACHE)
unset(xDEBUG_MODE_NO           CACHE)
unset(xCOMPILE_TRACING         CACHE)
unset(xNEW_NO_STD_THROW        CACHE)
unset(xTEST_PRIVATE_DATA       CACHE)
unset(xTEST_TRACING            CACHE)

option(xUSING_NAMESPACE_XLIB   "automatically include the xlib namespace"  ON)
option(xDEBUG_USE_PROMPT_DIALOG "debug prompt dialog"                      ON)
option(xDEBUG_MODE_MSGBOX       "debug mode 'message box with plain text'" OFF)
option(xDEBUG_MODE_STDOUT       "debug mode 'std::out with plain text'"    ON)
option(xDEBUG_MODE_LOG          "debug mode 'logging with plain text'"     OFF)
option(xDEBUG_MODE_NO           "debug mode 'no debugging'"                OFF)
option(xCOMPILE_TRACING         "is compile time tracing"                  OFF)
option(xNEW_NO_STD_THROW        "new with std::notrow"                     OFF)
option(xTEST_PRIVATE_DATA       "tests private data"                       OFF)
option(xTEST_TRACING            "use tracing in tests"                     ON)

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(Configure)

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
    if (X11_FOUND)
        include_directories("${X11_INCLUDE_DIR}")
        link_libraries(${X11_LIBRARIES})
    endif()

    if (EXECINFO_FOUND)
        include_directories(${EXECINFO_INCLUDES})
        link_libraries(${EXECINFO_LIBRARIES})
    endif()
endif()

#--------------------------------------------------------------------------------------------------
# vars
if (CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

set(XLIB_INSTALL_DIR  include/xLib)
set(XLIB_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${XLIB_INSTALL_DIR}")

#--------------------------------------------------------------------------------------------------
# sources
file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")

#--------------------------------------------------------------------------------------------------
# target
add_executable(xLib_test ${xLib_tests_SOURCES})

#--------------------------------------------------------------------------------------------------
# flags
if     (MSVC)
    set(FLAGS ${FLAGS} "/W3")
elseif (MINGW)
    set(LIBS ${LIBS} ws2_32 psapi uuid ole32 mpr)
    set(FLAGS ${FLAGS} "-Wall -pipe")
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(LIBS ${LIBS} pthread rt m z)
    set(FLAGS ${FLAGS} "-pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror -fcolor-diagnostics -Qunused-arguments ")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(LIBS ${LIBS} pthread rt m z)
    set(FLAGS ${FLAGS} "-pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror")
else()
    message("xLib: unknown compiler")
endif()

set_target_properties(
    xLib_test PROPERTIES
        # COMPILE_DEFINITIONS ${DEFINITIONS}
        COMPILE_FLAGS ${FLAGS}
)

target_link_libraries(xLib_test ${LIBS} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

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
