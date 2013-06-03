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
# flags
include_directories("${CMAKE_SOURCE_DIR}/Project/Include")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")
include_directories(${XLib_TESTS_INCLUDE_DIRS})
include_directories(${XLib_PROJECT_INCLUDE_DIRS})

add_definitions(-Wall -pipe)

# Libs Linux: "-lrt -lmysqlclient -lm -lcrypto -lz -lssl -pthread"
## link_libraries(rt m z crypto ssl mysqlclient ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

# Libs Windows: "-lmysqlclient -lm -lcrypto -lz -lssl -pthread"
link_libraries(mysqlclient ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

#-------------------------------------------------------------------------------
# targets
add_library   (xLib_static STATIC ${xLib_SOURCES})
add_library   (xLib_shared SHARED ${xLib_SOURCES})
add_executable(xLib_test ${xLib_SOURCES} ${xLib_tests_SOURCES})
