#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief Unit tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
include(CTest)
#--------------------------------------------------------------------------------------------------
if (EXISTS "${XLIB_LOCATION}/../conan_paths.cmake")
    include(${XLIB_LOCATION}/../conan_paths.cmake)
endif()
#--------------------------------------------------------------------------------------------------
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
set(MEMORYCHECK_SUPPRESSIONS_FILE     "${XLIB_LOCATION}/valgrind_suppress.txt")
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)
    message(STATUS ">>>>> TEST_NAME: ${TEST_NAME}")

    find_package(LibXml2 REQUIRED)
    message(STATUS ">>>>> LIBXML2_LIBRARIES: ${LIBXML2_LIBRARIES}")

    add_executable(${TEST_NAME}.exe ${IT_SOURCE})

    if (MSVC)
        # set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/Z7 /NODEFAULTLIB:library")
        # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")

        # https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-warning-lnk4099?redirectedfrom=MSDN&view=msvc-160
        set_target_properties(${TEST_NAME}.exe PROPERTIES LINK_FLAGS "/ignore:4099")
    endif()

    target_link_libraries(${TEST_NAME}.exe ${PROJECT_NAME}_static ${XLIB_LIBRARIES} ${LIBXML2_LIBRARIES})
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
#--------------------------------------------------------------------------------------------------
