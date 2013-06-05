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
file(GLOB_RECURSE xLib_SOURCES "Project/*.cpp")

foreach(_headerFile ${xLib_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
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
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")
include_directories(${XLib_TESTS_INCLUDE_DIRS})
include_directories(${XLib_PROJECT_INCLUDE_DIRS})

#-------------------------------------------------------------------------------
# targets
add_library   (xLib_static STATIC ${xLib_SOURCES})
add_library   (xLib_shared SHARED ${xLib_SOURCES})
add_executable(xLib_test ${xLib_SOURCES} ${xLib_tests_SOURCES})

#-------------------------------------------------------------------------------
# flags
if (MSVC)
    set_target_properties(
        xLib_test
        PROPERTIES
            # COMPILE_DEFINITIONS
            COMPILE_FLAGS "/W3"
    )

    target_link_libraries(
        xLib_test
        mysqlclient ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS}
    )
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(
        xLib_test
        PROPERTIES
            # COMPILE_DEFINITIONS
            COMPILE_FLAGS "-Wall -pipe"
    )

    target_link_libraries(
        xLib_test
        rt m z crypto ssl mysqlclient ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS}
    )
else()
    message("xLib: unknown compiler")
endif()
