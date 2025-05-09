#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief xLib unit tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15)

project(xLib_tests DESCRIPTION "xLib library tests")
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: Config :::::")

include(../CMake/Config.cmake)

set(cmOPTION_PROJECT_LIB_TYPE "")
#--------------------------------------------------------------------------------------------------
# Modules
message(STATUS "\n::::: Modules :::::")

set(DIR_HOME $ENV{HOME})

# modules
if (EXISTS "${CMAKE_ROOT}/Modules/CMakeLib")
    list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_ROOT}/Modules/CMakeLib"
        "${CMAKE_SOURCE_DIR}/../../xLib_conan"
        "${CMAKE_SOURCE_DIR}")
else()
    list(APPEND CMAKE_MODULE_PATH
        "${DIR_HOME}/Projects/CMakeLib"
        "${CMAKE_SOURCE_DIR}/../../xLib_conan"
        "${CMAKE_SOURCE_DIR}")
endif()

message(STATUS "CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: Conan :::::")

set(XLIB_TESTS_LOCATION ${CMAKE_SOURCE_DIR})
message(STATUS "XLIB_TESTS_LOCATION: ${XLIB_TESTS_LOCATION}")
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: Configure :::::")

find_package(xLib QUIET REQUIRED)

include(../CMake/Configure)

# System
if (OPENSSL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${OPENSSL_INCLUDE_DIR})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${OPENSSL_LIBRARIES})
endif()

message(STATUS "OPENSSL_FOUND: ${OPENSSL_FOUND}")

if (CURL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${CURL_INCLUDE_DIRS})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CURL_LIBRARIES})
endif()

message(STATUS "CURL_FOUND: ${CURL_FOUND}")

if (Iconv_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${Iconv_INCLUDE_DIRS})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${Iconv_LIBRARIES})
endif()

message(STATUS "Iconv_FOUND: ${Iconv_FOUND}")

if (LIBXML2_FOUND)
    set(XLIB_INCLUDES    ${XLIB_INCLUDES}    ${LIBXML2_INCLUDE_DIRS})
    set(XLIB_LIBRARIES   ${XLIB_LIBRARIES}   ${LIBXML2_LIBRARIES})
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} ${LIBXML2_DEFINITIONS})
endif()

message(STATUS "LIBXML2_FOUND: ${LIBXML2_FOUND}")

# CMakeLib
if (cmMYSQL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmMYSQL_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmMYSQL_LIBRARIES})
endif()

if (cmSSH2_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmSSH2_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmSSH2_LIBRARIES})
endif()

if (ENV_UNIX)
    if (cmEXECINFO_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmEXECINFO_INCLUDES})
        ## set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmEXECINFO_LIBRARIES})
    endif()

    if (OS_ANDROID)
        set(ANDROID_NDK    "/opt/Libs/Android/NDK")
        set(XLIB_INCLUDES  ${XLIB_INCLUDES} "${ANDROID_NDK}/platforms/android-9/arch-arm/usr/include")
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES})
    endif()
endif()
#--------------------------------------------------------------------------------------------------
message(STATUS "\n::::: CTest :::::")

include(CTest)
enable_testing()
#--------------------------------------------------------------------------------------------------
file(GLOB_RECURSE XLIB_TESTS_SOURCES *.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(TEST_NAME ${IT_SOURCE} NAME_WE)

    # TODO: temp test
    # if (NOT "${TEST_NAME}" MATCHES "Test_HttpClient")
    #     continue()
    # endif()

    # [Debug]
    if (0)
        message(STATUS "\n::::: Unit test :::::")
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

    target_compile_definitions(${TEST_NAME} PUBLIC
        ${XLIB_DEFINITIONS})

    target_include_directories(${TEST_NAME} PUBLIC
        ${cmXLIB_INCLUDES}
        ${XLIB_INCLUDES})

    # For debug::StackTrace
    if (ENV_UNIX)
        target_link_options(${TEST_NAME} PUBLIC
            "$<$<CONFIG:Debug>:-rdynamic>"
            "$<$<CONFIG:Release>:-rdynamic>")

        # get_target_property(LINK_FLAGS ${TEST_NAME} LINK_OPTIONS)
        # message(STATUS "LINK_FLAGS: ${LINK_FLAGS}")
    endif()

    target_link_libraries(${TEST_NAME} PUBLIC
        ${CONAN_LIBS}   # ?????

        ${cmXLIB_LIBRARIES}
        ${cmXLIB_EXTRA_LIBRARIES}
        ${cmXLIB_SYS_LIBRARIES}

        ${XLIB_LIBRARIES}
    )

    add_test(NAME ${TEST_NAME} COMMAND "${TEST_NAME}")

	# Targets - Build, run single test
	add_custom_target(test_${TEST_NAME}
		COMMAND           ${TEST_NAME}
		DEPENDS           ${TEST_NAME}
		WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
endforeach()
#--------------------------------------------------------------------------------------------------
