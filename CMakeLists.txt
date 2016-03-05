#--------------------------------------------------------------------------------------------------
# \file  FindxLib.cmake
# \brief Find xLib
#
# XLIB_LOCATION    - root diractory [in]
# XLIB_FOUND       - found or not
# XLIB_DEFINITIONS - definitions
# XLIB_INCLUDES    - include pathes
# XLIB_SOURCES     - source pathes
# XLIB_LIBRARIES   - libraries list
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib)
set(PROJECT_TYPE "CXX")
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    # None           (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
    # Debug          (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
    # Release        (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
    # RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
    # MinSizeRel     (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# message("CMAKE_CXX_COMPILE_FEATURES: ${CMAKE_CXX_COMPILE_FEATURES}")
#--------------------------------------------------------------------------------------------------
# vars
unset(XLIB_FOUND       CACHE)
unset(XLIB_DEFINITIONS CACHE)
unset(XLIB_INCLUDES    CACHE)
unset(XLIB_SOURCES     CACHE)
unset(XLIB_LIBRARIES   CACHE)

unset(XLIB_LOCATION    CACHE)

if (NOT XLIB_LOCATION)
    set(XLIB_LOCATION ${CMAKE_SOURCE_DIR})
endif()
#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH ${XLIB_LOCATION}/CMakeLib)
include(${XLIB_LOCATION}/Config.cmake)
include(Configure)
#--------------------------------------------------------------------------------------------------
# includes, libs
set(XLIB_INCLUDES ${XLIB_INCLUDES} ${XLIB_LOCATION}/Include)
file(GLOB_RECURSE XLIB_SOURCES ${XLIB_LOCATION}/Include/*.cpp)

if (OPENSSL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${OPENSSL_INCLUDE_DIR})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${OPENSSL_LIBRARIES})
endif()

if (MYSQL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${MYSQL_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${MYSQL_LIBRARIES})
endif()

if (SSH2_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${SSH2_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${SSH2_LIBRARIES})
endif()

if (ENV_UNIX)
    if (XCB_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${XCB_INCLUDE_DIR})
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${XCB_LIBRARIES})
    endif()

    if (EXECINFO_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES} ${EXECINFO_INCLUDES})
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${EXECINFO_LIBRARIES})
    endif()

    if (OS_ANDROID)
        # set(ANDROID_NDK "/opt/Libs/Android/NDK")
        # set(XLIB_INCLUDES ${XLIB_INCLUDES} "${ANDROID_NDK}/platforms/android-9/arch-arm/usr/include")
        # set(XLIB_LIBRARIES ${XLIB_LIBRARIES})
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# includes
include_directories(${XLIB_INCLUDES})
#--------------------------------------------------------------------------------------------------
# vars
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGCC 1)
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

set(XLIB_INSTALL_DIR  include/xLib)
set(XLIB_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/${XLIB_INSTALL_DIR})
#--------------------------------------------------------------------------------------------------
# flags
include(CxxFlags)
# include(CMakeVariables)

#--------------------------------------------------------------------------------------------------
# definitions
if (xOPTION_CPP11)
    set(CMAKE_CXX_STANDARD 11)

    # add_definitions(-std=c++11)
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} "-std=c++11")
else()
    set(CMAKE_CXX_STANDARD 98)  # 98, 11 and 14
endif()
message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XLIB_DEFINITIONS}")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
#--------------------------------------------------------------------------------------------------
# libraries
set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

if     (MSVC)

elseif (MINGW)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} pthread rt m z)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} pthread rt m z)
else()
    message("xLib: unknown compiler")
endif()

if (OS_ANDROID)
    unset(XLIB_DEFINITIONS CACHE)
    unset(XLIB_LIBRARIES   CACHE)

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} gnustl_static m z log)
endif()

if (NOT (XLIB_INCLUDES AND XLIB_LIBRARIES))
    set(XLIB_FOUND       0)
    set(XLIB_DEFINITIONS "")
    set(XLIB_INCLUDES    "")
    set(XLIB_SOURCES     "")
    set(XLIB_LIBRARIES   "")
else()
    set(XLIB_FOUND       1)
endif()
#--------------------------------------------------------------------------------------------------
# trace
if (NOT XLIB_FOUND AND XLIB_FIND_REQUIRED)
    message(FATAL_ERROR "XLIB_FOUND: ${XLIB_FOUND}")
else()
    message(STATUS "XLIB_FOUND: ${XLIB_FOUND}")
    # message("    XLIB_LOCATION:    ${XLIB_LOCATION}")
    # message("    XLIB_DEFINITIONS: ${XLIB_DEFINITIONS}")
    # message("    XLIB_INCLUDES:    ${XLIB_INCLUDES}")
    # message("    XLIB_LIBRARIES:   ${XLIB_LIBRARIES}")
    # message("    XLIB_SOURCES:     ${XLIB_SOURCES}")
endif()
#--------------------------------------------------------------------------------------------------
# targets, install
if (xOPTION_PROJECT_HEADER_ONLY)
    # n/a
endif()

if (xOPTION_PROJECT_LIB_STATIC)
    add_library(${PROJECT_NAME}_static STATIC ${XLIB_SOURCES})
    install(TARGETS ${PROJECT_NAME}_static DESTINATION "bin")
endif()

if (xOPTION_PROJECT_LIB_SHARE)
    add_library(${PROJECT_NAME}_shared SHARED ${XLIB_SOURCES})
    install(TARGETS ${PROJECT_NAME}_shared DESTINATION "bin")
endif()

if (xOPTION_PROJECT_LIB_MODULE)
    add_library(${PROJECT_NAME}_module MODULE ${XLIB_SOURCES})
    install(TARGETS ${PROJECT_NAME}_module DESTINATION "bin")
endif()

if (xOPTION_PROJECT_TESTS)
    include_directories(${XLIB_LOCATION}/Tests/Include)
    file(GLOB_RECURSE XLIB_TESTS_SOURCES ${XLIB_LOCATION}/Tests/Source/*.cpp)

    add_executable(${PROJECT_NAME}_tests ${XLIB_SOURCES} ${XLIB_TESTS_SOURCES})
    target_link_libraries(${PROJECT_NAME}_tests ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_NAME}_tests  DESTINATION "bin")
endif()

set(XLIB_FOUND       ${XLIB_FOUND}       PARENT_SCOPE)
set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} PARENT_SCOPE)
set(XLIB_INCLUDES    ${XLIB_INCLUDES}    PARENT_SCOPE)
set(XLIB_SOURCES     ${XLIB_SOURCES}     PARENT_SCOPE)
set(XLIB_LIBRARIES   ${XLIB_LIBRARIES}   PARENT_SCOPE)
set(XLIB_LOCATION    ${XLIB_LOCATION}    PARENT_SCOPE)
#--------------------------------------------------------------------------------------------------
# install
#install(
#    DIRECTORY ${XLIB_LOCATION}/Include/xLib/
#    DESTINATION ${XLIB_INSTALL_PATH}
#    FILES_MATCHING PATTERN "*" PATTERN "*.h.in" EXCLUDE)
#--------------------------------------------------------------------------------------------------
# uninstall
configure_file(
    ${XLIB_LOCATION}/CMakeLib/Uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake)
#--------------------------------------------------------------------------------------------------
# run tests after build
if (xOPTION_PROJECT_TESTS)
    add_custom_command(TARGET ${PROJECT_NAME}_tests POST_BUILD COMMAND ${PROJECT_NAME}_tests)
endif()
#--------------------------------------------------------------------------------------------------
# fix warning "Manually-specified variables were not used by the project"
unset(CMAKE_TOOLCHAIN_FILE)
