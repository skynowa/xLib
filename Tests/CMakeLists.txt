#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief Unit tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
include(CTest)

message(STATUS "")
message(STATUS ">>>>> CTest <<<<<<")
#--------------------------------------------------------------------------------------------------
if (EXISTS "${XLIB_LOCATION}/../conan_paths.cmake")
    message(STATUS ">>>>> conan_paths: TRUE")

    include(${XLIB_LOCATION}/../conan_paths.cmake)
else()
    message(STATUS ">>>>> conan_paths: FALSE")
endif()
#--------------------------------------------------------------------------------------------------
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
set(MEMORYCHECK_SUPPRESSIONS_FILE     "${XLIB_LOCATION}/valgrind_suppress.txt")
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)

    # TODO: temp test
    if (NOT "${TEST_NAME}" MATCHES "Test_Xml")
        continue()
    endif()

    find_package(LibXml2 REQUIRED)

    message(STATUS "")
    message(STATUS ">>>>> PROJECT_NAME: ${PROJECT_NAME}")
    message(STATUS ">>>>> PROJECT_LIB_STATIC: ${PROJECT_LIB_STATIC}")
    message(STATUS ">>>>> TEST_NAME: ${TEST_NAME}")
    message(STATUS ">>>>> LIBXML2_LIBRARIES: ${LIBXML2_LIBRARIES}")
    message(STATUS ">>>>> IT_SOURCE: ${IT_SOURCE}")
    message(STATUS ">>>>> XLIB_LIBRARIES: ${XLIB_LIBRARIES}")

    add_executable(${TEST_NAME} ${IT_SOURCE})
    target_include_directories(${TEST_NAME} PUBLIC ${CONAN_LIBXML2_ROOT}/lib)
    target_link_libraries(${TEST_NAME} ${PROJECT_LIB_STATIC} ${XLIB_LIBRARIES})

    if (MSVC)
        # There are 4 versions of the CRT link libraries present in vclib:
        #
        # libcmt.lib:  static CRT link library for a release build (/MT)
        # libcmtd.lib: static CRT link library for a debug build (/MTd)
        # msvcrt.lib:  import library for the release DLL version of the CRT (/MD)
        # msvcrtd.lib: import library for the debug DLL version of the CRT (/MDd)

        # set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/MTd /NODEFAULTLIB /Z7")
        set(CMAKE_EXE_LINKER_FLAGS "/MTd")
        set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:MSVCRT")

        # https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-warning-lnk4099
        set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4098")
        set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")
    endif()

    add_test(NAME ${TEST_NAME} COMMAND "${TEST_NAME}")
endforeach()
#--------------------------------------------------------------------------------------------------
