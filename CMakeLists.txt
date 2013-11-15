#-------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib
#-------------------------------------------------------------------------------


cmake_minimum_required (VERSION 2.6)


project (xLib)

#-------------------------------------------------------------------------------
# prepare
if (CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

#-------------------------------------------------------------------------------
# includes
include_directories("${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")

#-------------------------------------------------------------------------------
# sources
file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")

#-------------------------------------------------------------------------------
# target
add_executable(xLib_test ${xLib_tests_SOURCES})

#-------------------------------------------------------------------------------
# flags
if (MSVC)
    #set(LIBS mysqlclient)
    set(FLAGS "/W3")
elseif (MINGW)
    set(LIBS ws2_32 psapi uuid ole32 mpr)
    set(FLAGS "-Wall -pipe")
elseif (CMAKE_COMPILER_IS_CLANGXX OR CMAKE_COMPILER_IS_GNUCXX)
    set(LIBS pthread rt m z )
    set(FLAGS "-pipe -Wall")
    #set(CMAKE_FLAGS "${CMAKE_FLAGS} -Wno-deprecated -Wextra -Wconversion -Wshadow -Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas -Wno-return-type-c-linkage -Werror")
    #set(CMAKE_FLAGS "${CMAKE_FLAGS} -fcolor-diagnostics -U__STRICT_ANSI__ -D__STDC_FORMAT_MACROS -Qunused-arguments")
else()
    message("xLib: unknown compiler")
endif()

set_target_properties(
    xLib_test
    PROPERTIES
        # COMPILE_DEFINITIONS
        COMPILE_FLAGS ${FLAGS}
)

target_link_libraries(
    xLib_test
    ${LIBS} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS}
)
