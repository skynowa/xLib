#--------------------------------------------------------------------------------------------------
# \file  FindxLib.cmake
# \brief Find xLib
#
# XLIB_LOCATION         - root diractory [in]
# cmXLIB_FOUND          - found or not
# XLIB_DEFINITIONS      - definitions
# cmXLIB_COMPILER_FLAGS - compiler flags
# XLIB_INCLUDES         - include pathes
# XLIB_SOURCES          - source pathes
# XLIB_LIBRARIES        - libraries list
#
# cmCMAKE_VERSION
# cmXLIB_COMPILER_FLAGS
# cmXLIB_LIBRARIES
#--------------------------------------------------------------------------------------------------


project(xLib)
cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------------------------------------
# options
set(PROJECT_TYPE "CXX")

set(CMAKE_COLOR_MAKEFILE        ON)
set(CMAKE_VERBOSE_MAKEFILE      OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_REQUIRED_QUIET        ON)

# message("CMAKE_CXX_COMPILE_FEATURES: ${CMAKE_CXX_COMPILE_FEATURES}")
#--------------------------------------------------------------------------------------------------
# vars
unset(cmXLIB_FOUND          CACHE)
unset(XLIB_DEFINITIONS      CACHE)
unset(cmXLIB_COMPILER_FLAGS CACHE)
unset(XLIB_INCLUDES         CACHE)
unset(XLIB_SOURCES          CACHE)
unset(XLIB_LIBRARIES        CACHE)

unset(XLIB_LOCATION         CACHE)
unset(XLIB_TEMPLATES        CACHE)

if (NOT XLIB_LOCATION)
    set(XLIB_LOCATION ${CMAKE_SOURCE_DIR})
endif()

set(XLIB_TEMPLATES ${XLIB_LOCATION}/Tools/Templates)
#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH ${XLIB_LOCATION}/CMake ${XLIB_LOCATION}/../CMakeLib)

include(${XLIB_LOCATION}/Config.cmake)
include(Configure)
#--------------------------------------------------------------------------------------------------
# includes, libs
set(XLIB_INCLUDES ${XLIB_INCLUDES} ${XLIB_LOCATION}/Include)
file(GLOB_RECURSE XLIB_SOURCES ${XLIB_LOCATION}/Include/*.cpp)

if (OPENSSL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${OPENSSL_INCLUDE_DIR})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${OPENSSL_LIBRARIES})
endif()

if (cmMYSQL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${MYSQL_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${MYSQL_LIBRARIES})
endif()

if (cmSSH2_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${SSH2_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${SSH2_LIBRARIES})
endif()

if (CURL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${CURL_INCLUDE_DIRS})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CURL_LIBRARIES})
endif()

if (ENV_UNIX)
    if (cmXCB_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${XCB_INCLUDE_DIR})
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${XCB_LIBRARIES})
    endif()

    if (cmEXECINFO_FOUND)
        set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${EXECINFO_INCLUDES})
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
if     (OPTION_CPP_98)
    set(CMAKE_CXX_STANDARD 98)
elseif (OPTION_CPP_11)
    set(CMAKE_CXX_STANDARD 11)
elseif (OPTION_CPP_14)
    set(CMAKE_CXX_STANDARD 14)
elseif (OPTION_CPP_17)
    set(CMAKE_CXX_STANDARD 17)
else()
    message(FATAL_ERROR "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD} - unknown")
endif()

if (OPTION_UNICODE)
    add_definitions(-DUNICODE=1)
    add_definitions(-D_UNICODE=1)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XLIB_DEFINITIONS}")
#--------------------------------------------------------------------------------------------------
# libraries
set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})

if     (MSVC)

elseif (MINGW)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
elseif (CMAKE_COMPILER_IS_CLANGXX)
    add_compile_options(-stdlib=libc++ -lc++abi)

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} pthread rt m z)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} pthread rt m z)
else()
    message(FATAL_ERROR "xLib: unknown compiler")
endif()

if (OS_ANDROID)
    unset(XLIB_DEFINITIONS      CACHE)
    unset(cmXLIB_COMPILER_FLAGS CACHE)
    unset(XLIB_LIBRARIES        CACHE)

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} gnustl_static m z log)
endif()

if (NOT (XLIB_INCLUDES AND XLIB_LIBRARIES))
    set(cmXLIB_FOUND          0)
    set(XLIB_DEFINITIONS      "")
    set(cmXLIB_COMPILER_FLAGS "")
    set(XLIB_INCLUDES         "")
    set(XLIB_SOURCES          "")
    set(XLIB_LIBRARIES        "")
else()
    set(cmXLIB_FOUND          1)
endif()
#--------------------------------------------------------------------------------------------------
# vars
set(cmCMAKE_VERSION       ${CMAKE_VERSION})
set(cmXLIB_COMPILER_FLAGS ${CMAKE_CXX_FLAGS})
set(cmXLIB_LIBRARIES      ${XLIB_LIBRARIES})
#--------------------------------------------------------------------------------------------------
# trace
if (NOT cmXLIB_FOUND AND XLIB_FIND_REQUIRED)
    message(FATAL_ERROR "cmXLIB_FOUND: ${cmXLIB_FOUND}")
else()
    # message(STATUS "cmXLIB_FOUND: ${cmXLIB_FOUND}")
    # message("    XLIB_LOCATION:         ${XLIB_LOCATION}")
    # message("    XLIB_DEFINITIONS:      ${XLIB_DEFINITIONS}")
    # message("    cmXLIB_COMPILER_FLAGS: ${cmXLIB_COMPILER_FLAGS}")
    # message("    XLIB_INCLUDES:         ${XLIB_INCLUDES}")
    # message("    XLIB_LIBRARIES:        ${XLIB_LIBRARIES}")
    # message("    XLIB_SOURCES:          ${XLIB_SOURCES}")
endif()
#--------------------------------------------------------------------------------------------------
# targets, install
if (cmOPTION_PROJECT_LIB_STATIC)
    set(PROJECT_LIB_STATIC ${PROJECT_NAME}_static)

    add_library(${PROJECT_LIB_STATIC} STATIC ${XLIB_SOURCES})
    target_link_libraries(${PROJECT_LIB_STATIC} ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_LIB_STATIC} DESTINATION "bin")

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${PROJECT_LIB_STATIC})
endif()

if (cmOPTION_PROJECT_LIB_SHARE)
    set(PROJECT_LIB_SHARE ${PROJECT_NAME}_shared)

    add_library(${PROJECT_LIB_SHARE} SHARED ${XLIB_SOURCES})
    target_link_libraries(${PROJECT_LIB_SHARE} ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_LIB_SHARE} DESTINATION "bin")

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${PROJECT_LIB_SHARE})
endif()

if (cmOPTION_PROJECT_LIB_MODULE)
    set(PROJECT_LIB_MODULE ${PROJECT_NAME}_module)

    add_library(${PROJECT_LIB_MODULE} MODULE ${XLIB_SOURCES})
    target_link_libraries(${PROJECT_LIB_MODULE} ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_LIB_MODULE} DESTINATION "bin")

    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${PROJECT_LIB_MODULE})
endif()

get_directory_property(IS_PARENT_SCOPE PARENT_DIRECTORY)
if (IS_PARENT_SCOPE)
    set(cmXLIB_FOUND          ${cmXLIB_FOUND}          PARENT_SCOPE)
    set(XLIB_DEFINITIONS      ${XLIB_DEFINITIONS}      PARENT_SCOPE)
    set(cmXLIB_COMPILER_FLAGS ${cmXLIB_COMPILER_FLAGS} PARENT_SCOPE)
    set(XLIB_INCLUDES         ${XLIB_INCLUDES}         PARENT_SCOPE)
    set(XLIB_SOURCES          ${XLIB_SOURCES}          PARENT_SCOPE)
    set(XLIB_LIBRARIES        ${XLIB_LIBRARIES}        PARENT_SCOPE)
    set(XLIB_LOCATION         ${XLIB_LOCATION}         PARENT_SCOPE)
    set(XLIB_TEMPLATES        ${XLIB_TEMPLATES}        PARENT_SCOPE)
else()
    set(cmXLIB_FOUND          ${cmXLIB_FOUND})
    set(XLIB_DEFINITIONS      ${XLIB_DEFINITIONS})
    set(cmXLIB_COMPILER_FLAGS ${cmXLIB_COMPILER_FLAGS})
    set(XLIB_INCLUDES         ${XLIB_INCLUDES})
    set(XLIB_SOURCES          ${XLIB_SOURCES})
    set(XLIB_LIBRARIES        ${XLIB_LIBRARIES})
    set(XLIB_LOCATION         ${XLIB_LOCATION})
    set(XLIB_TEMPLATES        ${XLIB_TEMPLATES})
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${XLIB_LOCATION}/Include/xLib/Config.h.in
    ${XLIB_LOCATION}/Include/xLib/Config.h)
#--------------------------------------------------------------------------------------------------
# install
install(
    DIRECTORY
        ${XLIB_LOCATION}/Include/xLib/
    DESTINATION
        ${XLIB_INSTALL_PATH}
    FILES_MATCHING
        PATTERN "*" PATTERN "*.h.in" EXCLUDE)
#--------------------------------------------------------------------------------------------------
# clang-tidy
add_custom_target(clang-tidy
    COMMAND
        ${cmCLANG_TIDY_FILE_PATH}
        ${XLIB_SOURCES}
        -config=''
        -export-fixes='clang-tidy-fixes.dat'
        --header-filter='.*'
        # -checks='*'
        # -list-checks
        --
        -std=c++11
        -I${XLIB_INCLUDES})
#--------------------------------------------------------------------------------------------------
# uninstall
add_custom_target(uninstall
    COMMAND
        ${CMAKE_COMMAND}
        -DXLIB_INSTALL_PATH="${XLIB_INSTALL_PATH}"
        -P ${XLIB_LOCATION}/CMake/Uninstall.cmake)
#--------------------------------------------------------------------------------------------------
add_custom_target(
        cppcheck
        COMMAND /usr/bin/cppcheck
        --enable=warning,performance,portability,information,missingInclude
        --std=c++11
        --library=qt.cfg
        --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
        --verbose
        --quiet
        ${XLIB_SOURCES})
#--------------------------------------------------------------------------------------------------
# template
add_custom_target(template
    COMMAND
        ${CMAKE_COMMAND}
        -DXLIB_LOCATION="${XLIB_LOCATION}" -DXLIB_TEMPLATES="${XLIB_TEMPLATES}"
        -P ${XLIB_LOCATION}/CMake/Template.cmake)
#--------------------------------------------------------------------------------------------------
# fix warning "Manually-specified variables were not used by the project"
unset(CMAKE_TOOLCHAIN_FILE)
#--------------------------------------------------------------------------------------------------
# tests
if (cmOPTION_BUILD_TESTS)
    enable_testing()
    add_subdirectory(${XLIB_LOCATION}/Tests)
endif()
#--------------------------------------------------------------------------------------------------
# enable_cppcheck(On)
# enable_clang_tidy(On)
