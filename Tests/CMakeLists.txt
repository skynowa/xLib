#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
include(CTest)
#--------------------------------------------------------------------------------------------------
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

set(CTEST_MEMORYCHECK_COMMAND_OPTIONS, "--trace-children=yes --leak-check=full")
set(MEMORYCHECK_SUPPRESSIONS_FILE "${XLIB_LOCATION}/valgrind_suppress.txt")
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)

    add_executable(${TEST_NAME} ${IT_SOURCE})
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME}_static)
    install(TARGETS ${TEST_NAME} DESTINATION "bin")

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    add_custom_command(TARGET ${TEST_NAME} POST_BUILD COMMAND ${TEST_NAME})
endforeach()
#--------------------------------------------------------------------------------------------------
