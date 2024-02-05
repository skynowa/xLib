#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief xLib build
#
# XLIB_LOCATION         - root diractory [in]
# XLIB_DEFINITIONS      - definitions
# XLIB_INCLUDES         - include pathes
# XLIB_SOURCES          - source pathes
# XLIB_SYS_LIBRARIES    - system libraries
# XLIB_LIBRARIES        - libraries list
#
# cmCMAKE_VERSION       - CMake version
# cmXLIB_COMPILER_FLAGS - compiler flags
# cmXLIB_LIBRARIES      - libraries list
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15)

project(xLib DESCRIPTION "xLib library")
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# vars
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
set(XLIB_LOCATION  ${CMAKE_SOURCE_DIR})
set(XLIB_TEMPLATES ${XLIB_LOCATION}/Tools/Templates)
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# modules
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${XLIB_LOCATION}/CMake")

include(CMake/Config.cmake)

# CONAN_PATHS
set(CONAN_PATHS "${XLIB_LOCATION}/../xLib_conan/conan_paths.cmake")

if (EXISTS ${CONAN_PATHS})
    include(${CONAN_PATHS})
else()
    message(WARNING "CONAN_PATHS: ${CONAN_PATHS} - not exists")
endif()

message(STATUS "CONAN_PATHS: ${CONAN_PATHS}")

# CONAN_LIBS
include(${XLIB_LOCATION}/../xLib_conan/conanbuildinfo.cmake)
conan_basic_setup()
message(STATUS "CONAN_LIBS: ${CONAN_LIBS}")
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# includes, libs
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
set(XLIB_INCLUDES ${XLIB_INCLUDES} ${XLIB_LOCATION}/Include)
file(GLOB_RECURSE XLIB_SOURCES ${XLIB_LOCATION}/Include/*.cpp)
#--------------------------------------------------------------------------------------------------
include(Configure)

# System
if (OPENSSL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${OPENSSL_INCLUDE_DIR})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${OPENSSL_LIBRARIES})
endif()

if (CURL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${CURL_INCLUDE_DIRS})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CURL_LIBRARIES})
endif()

if (LIBXML2_FOUND)
    set(XLIB_INCLUDES    ${XLIB_INCLUDES}    ${LIBXML2_INCLUDE_DIRS})
    set(XLIB_LIBRARIES   ${XLIB_LIBRARIES}   ${LIBXML2_LIBRARIES})
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} ${LIBXML2_DEFINITIONS})
endif()

# CMakeLib
if (cmMYSQL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmMYSQL_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmMYSQL_LIBRARIES})
endif()

if (cmSSH2_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${cmSSH2_INCLUDES})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmSSH2_LIBRARIES})
endif()

if (cmICONV_FOUND)
    set(XLIB_INCLUDES ${XLIB_INCLUDES} ${cmICONV_INCLUDES})

    if (cmICONV_LIBRARIES)
        set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${cmICONV_LIBRARIES})
    endif()
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


#--------------------------------------------------------------------------------------------------
# vars
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
# CMAKE_INSTALL_PREFIX
# - UNIX    "/usr/local"
# - Windows "C:/Program Files/${PROJECT_NAME}"

set(XLIB_INSTALL_DIR  include/xLib)
set(XLIB_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/${XLIB_INSTALL_DIR})
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# Definitions
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
if (OPTION_UNICODE)
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} -DUNICODE=1 -D_UNICODE=1)
endif()
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# XLIB_SYS_LIBRARIES - System libraries
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
set(XLIB_SYS_LIBRARIES
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_THREAD_LIBS}
    ${CMAKE_DL_LIBS})

if     (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(XLIB_SYS_LIBRARIES ${XLIB_SYS_LIBRARIES} advapi32 ws2_32 netapi32 psapi uuid mpr dbghelp crypt32)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # -stdlib=libc++ or -stdlib=libstdc++ will probably work
    set(XLIB_SYS_LIBRARIES ${XLIB_SYS_LIBRARIES} -stdlib=libstdc++ c++abi pthread rt m z)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    # -stdlib=libc++ or -stdlib=libstdc++ will probably work
    set(XLIB_SYS_LIBRARIES ${XLIB_SYS_LIBRARIES} -stdlib=libstdc++ c++abi pthread rt m z)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (ENV_WIN)
        set(XLIB_SYS_LIBRARIES ${XLIB_SYS_LIBRARIES} advapi32 ws2_32 netapi32 psapi uuid mpr dbghelp crypt32)
    else()
        set(XLIB_SYS_LIBRARIES ${XLIB_SYS_LIBRARIES} pthread rt m z)
    endif()
else()
    message("xLib: ${CMAKE_CXX_COMPILER_ID} - unknown compiler")
endif()

if (OS_ANDROID)
    set(XLIB_SYS_LIBRARIES ${XLIB_SYS_LIBRARIES} gnustl_static m z log)
endif()
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# vars (sources)
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
set(cmCMAKE_VERSION       ${CMAKE_VERSION})
set(cmXLIB_COMPILER_FLAGS ${CMAKE_CXX_FLAGS})
set(cmXLIB_LIBRARIES      ${XLIB_LIBRARIES}) # TODO:
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# trace
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
message(STATUS "XLIB_LOCATION:         ${XLIB_LOCATION}")
message(STATUS "XLIB_DEFINITIONS:      ${XLIB_DEFINITIONS}")
message(STATUS "cmXLIB_COMPILER_FLAGS: ${cmXLIB_COMPILER_FLAGS}")
message(STATUS "XLIB_INCLUDES:         ${XLIB_INCLUDES}")
message(STATUS "XLIB_LIBRARIES:        ${XLIB_LIBRARIES}")
message(STATUS "XLIB_SYS_LIBRARIES:    ${XLIB_SYS_LIBRARIES}")
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# targets
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
add_library               (${PROJECT_NAME} ${cmOPTION_PROJECT_LIB_TYPE})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${XLIB_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PUBLIC ${XLIB_INCLUDES})
target_sources            (${PROJECT_NAME} PUBLIC ${XLIB_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CONAN_LIBS}
    ${XLIB_SYS_LIBRARIES}
    ${XLIB_LIBRARIES})
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# install
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
# Lib
install(TARGETS ${PROJECT_NAME} DESTINATION "lib")

# Sources
install(
    DIRECTORY
        ${XLIB_LOCATION}/Include/xLib/
    DESTINATION
        ${XLIB_INSTALL_PATH}
    FILES_MATCHING
        PATTERN "*"
        PATTERN "*.h.in"   EXCLUDE
        PATTERN ".gitkeep" EXCLUDE)

# Uninstall
add_custom_target(uninstall
    COMMAND
        ${CMAKE_COMMAND}
        -DXLIB_INSTALL_PATH="${XLIB_INSTALL_PATH}"
        -P ${CMAKE_LIB_INCLUDES}/CMakeLib/Uninstall.cmake
    COMMENT
        "Uninstall...")
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# Targets (custom)
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
# Template
add_custom_target(template
    COMMAND
        ${CMAKE_COMMAND}
        -DXLIB_LOCATION="${XLIB_LOCATION}" -DXLIB_TEMPLATES="${XLIB_TEMPLATES}"
        -P ${XLIB_LOCATION}/CMake/Template.cmake
    COMMENT
        "Template...")
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# Config.h
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
configure_file(
    ${XLIB_LOCATION}/Include/xLib/Config.h.in
    ${XLIB_LOCATION}/Include/xLib/Config.h)
#--------------------------------------------------------------------------------------------------
