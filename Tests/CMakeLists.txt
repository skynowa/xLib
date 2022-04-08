#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief xLib unit tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.5.0)
#--------------------------------------------------------------------------------------------------
project(
    xLib_tests
    DESCRIPTION "xLib library tests")
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: Config :::::")

include(../Config.cmake)

if (NOT cmOPTION_BUILD_TESTS)
    message(STATUS "Tests - skip")
    return()
endif()
#--------------------------------------------------------------------------------------------------
# Modules
message(STATUS "\n::::: Modules :::::")

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_ROOT}/Modules/CMakeLib
    # ../CMake
    ${CMAKE_SOURCE_DIR})
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: Conan :::::")

set(XLIB_TESTS_LOCATION ${CMAKE_SOURCE_DIR})
message(STATUS "XLIB_TESTS_LOCATION: ${XLIB_TESTS_LOCATION}")

# CONAN_PATHS
set(CONAN_PATHS "${XLIB_TESTS_LOCATION}/../../conan_paths.cmake")

if (EXISTS ${CONAN_PATHS})
    include(${CONAN_PATHS})
else()
    message(FATAL_ERROR "CONAN_PATHS: ${CONAN_PATHS} - not exists")
endif()

message(STATUS "CONAN_PATHS: ${CONAN_PATHS}")
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: Configure :::::")

find_package(xLib QUIET REQUIRED)

include(../CMake/Configure)

if (CURL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${CURL_INCLUDE_DIRS})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CURL_LIBRARIES})
endif()

if (OPENSSL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${OPENSSL_INCLUDE_DIR})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${OPENSSL_LIBRARIES})
endif()

if (cmMYSQL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmMYSQL_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmMYSQL_LIBRARIES})
endif()

if (cmSSH2_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmSSH2_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmSSH2_LIBRARIES})
endif()

if (LIBXML2_FOUND)
    set(XLIB_INCLUDES    ${XLIB_INCLUDES}    ${LIBXML2_INCLUDE_DIRS})
    set(XLIB_LIBRARIES   ${XLIB_LIBRARIES}   ${LIBXML2_LIBRARIES})
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} ${LIBXML2_DEFINITIONS})
endif()

if (cmEVENT2_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmEVENT2_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmEVENT2_LIBRARIES})
endif()

if (cmICONV_FOUND)
    set(XLIB_INCLUDES ${XLIB_INCLUDES} ${cmICONV_INCLUDES})

    if (cmICONV_LIBRARIES)
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmICONV_LIBRARIES})
    endif()
endif()

if (ENV_UNIX)
    if (cmXCB_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmXCB_INCLUDE_DIR})
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmXCB_LIBRARIES})
    endif()

    if (cmEXECINFO_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmEXECINFO_INCLUDES})
        ## set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmEXECINFO_LIBRARIES})
    endif()

    if (OS_ANDROID)
        # set(ANDROID_NDK "/opt/Libs/Android/NDK")
        # set(XLIB_INCLUDES ${XLIB_INCLUDES} "${ANDROID_NDK}/platforms/android-9/arch-arm/usr/include")
        # set(XLIB_LIBRARIES ${XLIB_LIBRARIES})
    endif()
endif()
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: CTest :::::")

### include(CTest)
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)

    # TODO: temp test
    if (NOT "${TEST_NAME}" MATCHES "Test_Xml")
        continue()
    endif()

    # [Debug]
    message(STATUS "\n::::: Unit test :::::")

    if (1)
        message(STATUS "")
        message(STATUS "::::: Project :::::")
        message(STATUS "IT_SOURCE: ${IT_SOURCE}")
        message(STATUS "TEST_NAME: ${TEST_NAME}")
        message(STATUS "")
        message(STATUS "::::: LIBXML2 :::::")
        message(STATUS "LIBXML2_FOUND:              ${LIBXML2_FOUND}")
        message(STATUS "LIBXML2_INCLUDE_DIR:        ${LIBXML2_INCLUDE_DIR}")
        message(STATUS "LIBXML2_INCLUDE_DIRS:       ${LIBXML2_INCLUDE_DIRS}")
        message(STATUS "LIBXML2_LIBRARIES:          ${LIBXML2_LIBRARIES}")
        message(STATUS "LIBXML2_DEFINITIONS:        ${LIBXML2_DEFINITIONS}")
        message(STATUS "LIBXML2_XMLLINT_EXECUTABLE: ${LIBXML2_XMLLINT_EXECUTABLE}")
        message(STATUS "LIBXML2_VERSION_STRING:     ${LIBXML2_VERSION_STRING}")
        message(STATUS "")
        message(STATUS "::::: xLib :::::")
        message(STATUS "cmXLIB_INCLUDES:  ${cmXLIB_INCLUDES}")
        message(STATUS "XLIB_INCLUDES:    ${XLIB_INCLUDES}")
        message(STATUS "")
        message(STATUS "cmXLIB_LIBRARIES: ${cmXLIB_LIBRARIES}")
        message(STATUS "XLIB_LIBRARIES:   ${XLIB_LIBRARIES}")
        message(STATUS "")
    endif()

    add_executable(${TEST_NAME}
        ${IT_SOURCE})

    if (0)
    # if (MSVC)
        # There are 4 versions of the CRT link libraries present in vclib:
        #
        # libcmt.lib:  static CRT link library for a release build (/MT)
        # libcmtd.lib: static CRT link library for a debug build (/MTd)
        # msvcrt.lib:  import library for the release DLL version of the CRT (/MD)
        # msvcrtd.lib: import library for the debug DLL version of the CRT (/MDd)
        ### set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")

        # For CMAKE_CONFIGURATION_TYPES=Debug:
        # https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-warning-lnk4099
        set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4098")
        set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")
    endif()

    target_include_directories(${TEST_NAME} PUBLIC
        ${cmXLIB_INCLUDES}
        ${XLIB_INCLUDES})

    # TODO:
    link_directories(${CONAN_LIBXML2_ROOT}/lib)

    target_link_libraries(${TEST_NAME} PUBLIC
        ${cmXLIB_LIBRARIES}
        ${cmXLIB_SYS_LIBRARIES}
        ${XLIB_LIBRARIES}   # TODO: ${cmXLIB_EXTRA_LIBRARIES}
        ${LIBXML2_LIBRARIES} LibXml2::LibXml2)

    ### enable_testing()
    ### add_test(NAME ${TEST_NAME} COMMAND "${TEST_NAME}")
endforeach()
#--------------------------------------------------------------------------------------------------
