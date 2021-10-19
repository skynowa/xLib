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

    add_executable(${TEST_NAME} ${IT_SOURCE})

    if (MSVC)
        # set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/Z7")
        # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /Z7")
        # set_target_properties(${TEST_NAME} PROPERTIES COMPILE_FLAGS "/Z7")

        set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")
    endif()

    target_link_libraries(${TEST_NAME} ${XLIB_LIBRARIES} ${PROJECT_NAME}_static "${cmXLIB_LIBRARIES}")
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
#--------------------------------------------------------------------------------------------------
