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
# dir "Tests"
set(XLib_TESTS_INCLUDE_DIRS "")

file(GLOB_RECURSE xLib_tests_HEADERS "Tests/*.h")
file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")

foreach (_headerFile ${xLib_tests_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND XLib_TESTS_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES XLib_TESTS_INCLUDE_DIRS)

#-------------------------------------------------------------------------------
# source directories
include_directories("${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")
include_directories(${XLib_TESTS_INCLUDE_DIRS})

#-------------------------------------------------------------------------------
# targets
add_executable(xLib_test ${xLib_tests_SOURCES})

#-------------------------------------------------------------------------------
# flags
if (MSVC)
    #set(LIBS mysqlclient)
    set(FLAGS "/W3")
elseif (MINGW)
    set(LIBS ws2_32 psapi uuid ole32 mpr)
    set(FLAGS "-Wall -pipe")
elseif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    set(LIBS pthread rt m z )
    set(FLAGS "-Wall -pipe")
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
