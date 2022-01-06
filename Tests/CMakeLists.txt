#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief Unit tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "::::: CTest :::::")

include(CTest)
#--------------------------------------------------------------------------------------------------
message(STATUS "::::: Conan :::::")

if (EXISTS "${XLIB_LOCATION}/../conan_paths.cmake")
    message(STATUS "conan_paths: TRUE")

    include(${XLIB_LOCATION}/../conan_paths.cmake)
else()
    message(STATUS "conan_paths: FALSE")
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

    # [Debug]
    if (1)
        message(STATUS "")
        message(STATUS "::::: Project :::::")
        message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
        message(STATUS "PROJECT_LIB_STATIC: ${PROJECT_LIB_STATIC}")
        message(STATUS "TEST_NAME: ${TEST_NAME}")
        message(STATUS "IT_SOURCE: ${IT_SOURCE}")
        message(STATUS "")
        message(STATUS "::::: LIBXML2 :::::")
        message(STATUS "LIBXML2_INCLUDE_DIRS: ${LIBXML2_INCLUDE_DIRS}")
        message(STATUS "LIBXML2_LIBRARIES: ${LIBXML2_LIBRARIES}")
        message(STATUS "")
        message(STATUS "::::: xLib :::::")
        message(STATUS "XLIB_LIBRARIES: ${XLIB_LIBRARIES}")
        message(STATUS "")
    endif()

    # [Debug]
    if (0)
        # add_executable(xmlTest.exe xmlTest.cpp)
        #
        # target_compile_definitions(xmlTest.exe PUBLIC ${LIBXML2_DEFINITIONS})
        # target_include_directories(xmlTest.exe PUBLIC ${LIBXML2_INCLUDE_DIRS})
        # target_link_libraries(xmlTest.exe ${LIBXML2_LIBRARIES})

        link_directories(${TEST_NAME} ${CONAN_LIBXML2_ROOT}/lib)

        # target_link_libraries(${PROJECT_LIB_STATIC} ${LIBXML2_LIBRARIES})
        # target_link_libraries(${PROJECT_LIB_STATIC} ${CONAN_LIBXML2_ROOT}/lib)
    endif()

    add_executable(${TEST_NAME} ${IT_SOURCE})

    target_link_libraries(${TEST_NAME} PUBLIC ${PROJECT_LIB_STATIC} "${XLIB_LIBRARIES}" ${LIBXML2_LIBRARIES})

    if (MSVC)
        if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
            # There are 4 versions of the CRT link libraries present in vclib:
            #
            # libcmt.lib:  static CRT link library for a release build (/MT)
            # libcmtd.lib: static CRT link library for a debug build (/MTd)
            # msvcrt.lib:  import library for the release DLL version of the CRT (/MD)
            # msvcrtd.lib: import library for the debug DLL version of the CRT (/MDd)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")

            # For CMAKE_CONFIGURATION_TYPES=Debug:
            # https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-warning-lnk4099
            set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4098")
            set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")
        endif()
    endif()

    add_test(NAME ${TEST_NAME} COMMAND "${TEST_NAME}")
endforeach()
#--------------------------------------------------------------------------------------------------
