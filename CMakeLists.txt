#-------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib
#-------------------------------------------------------------------------------


cmake_minimum_required (VERSION 2.6)

project (xLib)

#-------------------------------------------------------------------------------
# dir "Project"
set(XLib_PROJECT_INCLUDE_DIRS "")

file(GLOB_RECURSE xLib_HEADERS "Project/*.h")
foreach(_headerFile ${xLib_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND XLib_PROJECT_INCLUDE_DIRS ${_dir})
endforeach()

file(GLOB_RECURSE xLib_SOURCES "Project/*.cpp")
foreach(_sourceFile ${xLib_SOURCES})
    get_filename_component(_dir ${_sourceFile} PATH)
    list (APPEND XLib_PROJECT_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES XLib_PROJECT_INCLUDE_DIRS)

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
include_directories("${CMAKE_SOURCE_DIR}/Project/Include")
include_directories("${CMAKE_SOURCE_DIR}/Project/Source")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")
include_directories(${XLib_TESTS_INCLUDE_DIRS})
include_directories(${XLib_PROJECT_INCLUDE_DIRS})

#-------------------------------------------------------------------------------
# targets
add_executable(xLib_test ${xLib_tests_SOURCES})

#-------------------------------------------------------------------------------
# flags
if (MSVC)
    # set(LIBS mysqlclient)
    set(FLAGS "/W3")
elseif (MINGW)
    set(LIBS ws2_32 psapi uuid ole32 mpr)
    set(FLAGS "-Wall -pipe")
elseif (CMAKE_COMPILER_IS_GNUCXX)
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

#-------------------------------------------------------------------------------
# add the install targets
install (DIRECTORY ${XLib_PROJECT_INCLUDE_DIRS} DESTINATION "include/xLib")
