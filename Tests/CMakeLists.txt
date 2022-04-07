#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief xLib unit tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.5.0)
#--------------------------------------------------------------------------------------------------
project(
    xLib_tests
    DESCRIPTION  "xLib library tests")
#--------------------------------------------------------------------------------------------------
include(../Config.cmake)

if (NOT cmOPTION_BUILD_TESTS)
    message(STATUS "Tests - skip")
    return()
endif()
#--------------------------------------------------------------------------------------------------
# Modules
if     (WIN32)
    set(CMAKE_DATA_DIR_ROOT "/usr")
elseif (UNIX)
    set(CMAKE_DATA_DIR_ROOT "C:/Program Files/CMake")
else()

set(CMAKE_VER              "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")
set(CMAKE_DATA_DIR_DEFAULT "${CMAKE_DATA_DIR_ROOT}/share/cmake-${CMAKE_VER}/Modules")
set(CMAKE_MODULE_PATH
    "${CMAKE_DATA_DIR_DEFAULT}/CMakeLib;"
    "../CMake;"
    "${CMAKE_SOURCE_DIR}")
#--------------------------------------------------------------------------------------------------
message(STATUS "::::: Conan :::::")

set(XLIB_TESTS_LOCATION ${CMAKE_SOURCE_DIR})
message(STATUS "XLIB_TESTS_LOCATION: ${XLIB_TESTS_LOCATION}")
message(STATUS "conan_paths:         ${XLIB_TESTS_LOCATION}/../../conan_paths.cmake")

if (EXISTS "${XLIB_TESTS_LOCATION}/../../conan_paths.cmake")
    message(STATUS "conan_paths: TRUE")

    include(${XLIB_TESTS_LOCATION}/../../conan_paths.cmake)
else()
    message(STATUS "conan_paths: FALSE")
endif()
#--------------------------------------------------------------------------------------------------
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
message(STATUS "")
message(STATUS "::::: CTest :::::")

include(CTest)
enable_testing()
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)

    # TODO: temp test
    if (NOT "${TEST_NAME}" MATCHES "Test_Xml")
        continue()
    endif()

    # [Debug]
    if (1)
        message(STATUS "")
        message(STATUS "::::: Project :::::")
        message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
        message(STATUS "TEST_NAME:    ${TEST_NAME}")
        message(STATUS "")
        message(STATUS "::::: LIBXML2 :::::")
        message(STATUS "LIBXML2_INCLUDE_DIRS: ${LIBXML2_INCLUDE_DIRS}")
        message(STATUS "LIBXML2_LIBRARIES:    ${LIBXML2_LIBRARIES}")
        message(STATUS "")
        message(STATUS "::::: xLib :::::")
        message(STATUS "XLIB_INCLUDES:    ${XLIB_INCLUDES}")
        message(STATUS "cmXLIB_INCLUDES:  ${cmXLIB_INCLUDES}")
        message(STATUS "")
        message(STATUS "XLIB_LIBRARIES:   ${XLIB_LIBRARIES}")
        message(STATUS "cmXLIB_LIBRARIES: ${cmXLIB_LIBRARIES}")
        message(STATUS "")
    endif()

    add_executable(${TEST_NAME}
        ${IT_SOURCE})

    target_include_directories(${TEST_NAME}
        ${XLIB_INCLUDES}
        ${cmXLIB_INCLUDES})

    target_link_libraries(${TEST_NAME} PRIVATE
        ${XLIB_LIBRARIES}
        ${cmXLIB_LIBRARIES}
        # ${LIBXML2_LIBRARIES}
        LibXml2::LibXml2)

    if (MSVC)
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

    add_test(NAME ${TEST_NAME} COMMAND "${TEST_NAME}")
endforeach()
#--------------------------------------------------------------------------------------------------
