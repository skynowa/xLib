#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief Unit tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
include(CTest)
#--------------------------------------------------------------------------------------------------
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
set(MEMORYCHECK_SUPPRESSIONS_FILE     "${XLIB_LOCATION}/valgrind_suppress.txt")
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)

    if (MSVC)
        # https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-warning-lnk4099?redirectedfrom=MSDN&view=msvc-160
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Z7")
    endif()

    add_executable(${TEST_NAME} ${IT_SOURCE})
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME}_static ${CMAKE_CXX_FLAGS})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
#--------------------------------------------------------------------------------------------------
