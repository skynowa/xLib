#--------------------------------------------------------------------------------------------------
# \file  FindxLib.cmake
# \brief Find xLib
#
# XLIB_LOCATION         - root diractory [in]
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


cmake_minimum_required(VERSION 3.5.0)

project(
    xLib
    DESCRIPTION "xLib library"
    VERSION      1.0.0.0)

set(XLIB_PROJECT_URL "https://github.com/skynowa/xLib/")
#--------------------------------------------------------------------------------------------------
# vars
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
list(APPEND CMAKE_MODULE_PATH "${XLIB_LOCATION}/CMake")

include(${XLIB_LOCATION}/Config.cmake)

if (EXISTS "${XLIB_LOCATION}/../conan_paths.cmake")
    include(${XLIB_LOCATION}/../conan_paths.cmake)
endif()

include(Configure)
#--------------------------------------------------------------------------------------------------
# includes, libs
set(XLIB_INCLUDES ${XLIB_INCLUDES} ${XLIB_LOCATION}/Include)
file(GLOB_RECURSE XLIB_HEADERS ${XLIB_LOCATION}/Include/*.h) # unused
file(GLOB_RECURSE XLIB_SOURCES ${XLIB_LOCATION}/Include/*.cpp)

if (OPENSSL_FOUND)
    message("   OPENSSL_FOUND:            ${OPENSSL_FOUND}")
    message("   OPENSSL_INCLUDE_DIR:      ${OPENSSL_INCLUDE_DIR}")
    message("   OPENSSL_CRYPTO_LIBRARY:   ${OPENSSL_CRYPTO_LIBRARY}")
    message("   OPENSSL_CRYPTO_LIBRARIES: ${OPENSSL_CRYPTO_LIBRARIES}")
    message("   OPENSSL_SSL_LIBRARY:      ${OPENSSL_SSL_LIBRARY}")
    message("   OPENSSL_SSL_LIBRARIES:    ${OPENSSL_SSL_LIBRARIES}")
    message("   OPENSSL_LIBRARIES:        ${OPENSSL_LIBRARIES}")
    message("   OPENSSL_VERSION:          ${OPENSSL_VERSION}")
    message("   OPENSSL_APPLINK_SOURCE:   ${OPENSSL_APPLINK_SOURCE}")

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

if (CURL_FOUND)
    set(XLIB_INCLUDES  ${XLIB_INCLUDES}  ${CURL_INCLUDE_DIRS})
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CURL_LIBRARIES})

    message("   CURL_LIBRARIES:   ${CURL_LIBRARIES}")
endif()

if (LIBXML2_FOUND)
    set(XLIB_INCLUDES    ${XLIB_INCLUDES}    ${LIBXML2_INCLUDE_DIR})
    set(XLIB_LIBRARIES   ${XLIB_LIBRARIES}   ${LIBXML2_LIBRARIES})
    set(XLIB_DEFINITIONS ${XLIB_DEFINITIONS} ${LIBXML2_DEFINITIONS})
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
#--------------------------------------------------------------------------------------------------
# definitions
if (OPTION_UNICODE)
    add_definitions(-DUNICODE=1)
    add_definitions(-D_UNICODE=1)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC ${XLIB_DEFINITIONS}")
#--------------------------------------------------------------------------------------------------
# libraries
set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

if     (MSVC)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} advapi32 ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
elseif (MINGW)
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} advapi32 ws2_32 netapi32 psapi uuid ole32 mpr dbghelp)
elseif (CMAKE_COMPILER_IS_CLANGXX)
    # -stdlib=libc++ or -stdlib=libstdc++ will probably work
    set(XLIB_LIBRARIES ${XLIB_LIBRARIES} -stdlib=libstdc++ -lc++abi pthread rt m z)
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
#--------------------------------------------------------------------------------------------------
# vars
set(cmCMAKE_VERSION       ${CMAKE_VERSION})
set(cmXLIB_COMPILER_FLAGS ${CMAKE_CXX_FLAGS} -Wfatal-errors)
set(cmXLIB_LIBRARIES      ${XLIB_LIBRARIES})
#--------------------------------------------------------------------------------------------------
# trace
message(STATUS "XLIB_LOCATION:         ${XLIB_LOCATION}")
message(STATUS "XLIB_DEFINITIONS:      ${XLIB_DEFINITIONS}")
message(STATUS "cmXLIB_COMPILER_FLAGS: ${cmXLIB_COMPILER_FLAGS}")
message(STATUS "XLIB_INCLUDES:         ${XLIB_INCLUDES}")
message(STATUS "XLIB_LIBRARIES:        ${XLIB_LIBRARIES}")
# message(STATUS "XLIB_SOURCES:          ${XLIB_SOURCES}")

message(STATUS "CMAKE_THREAD_LIBS:      ${CMAKE_THREAD_LIBS}")
message(STATUS "CMAKE_DL_LIBS:          ${CMAKE_DL_LIBS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
#--------------------------------------------------------------------------------------------------
# targets, install
if (cmOPTION_PROJECT_LIB_STATIC)
    set(PROJECT_LIB_STATIC ${PROJECT_NAME}_static)

    message("    PROJECT_LIB_STATIC: ${PROJECT_LIB_STATIC}")

    add_library(${PROJECT_LIB_STATIC} STATIC ${XLIB_SOURCES})
    target_link_libraries(${PROJECT_LIB_STATIC} LINK_PUBLIC ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_LIB_STATIC} DESTINATION "lib")
endif()

if (cmOPTION_PROJECT_LIB_SHARE)
    set(PROJECT_LIB_SHARE ${PROJECT_NAME}_shared)

    add_library(${PROJECT_LIB_SHARE} SHARED ${XLIB_SOURCES})
    target_link_libraries(${PROJECT_LIB_SHARE} ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_LIB_SHARE} DESTINATION "lib")
endif()

if (cmOPTION_PROJECT_LIB_MODULE)
    set(PROJECT_LIB_MODULE ${PROJECT_NAME}_module)

    add_library(${PROJECT_LIB_MODULE} MODULE ${XLIB_SOURCES})
    target_link_libraries(${PROJECT_LIB_MODULE} ${XLIB_LIBRARIES})
    install(TARGETS ${PROJECT_LIB_MODULE} DESTINATION "lib")
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${XLIB_LOCATION}/Include/xLib/Config.h.in
    ${XLIB_LOCATION}/Include/xLib/Config.h)
#--------------------------------------------------------------------------------------------------
install(
    DIRECTORY
        ${XLIB_LOCATION}/Include/xLib/
    DESTINATION
        ${XLIB_INSTALL_PATH}
    FILES_MATCHING
        PATTERN "*"
        PATTERN "*.h.in"   EXCLUDE
        PATTERN ".gitkeep" EXCLUDE)
#--------------------------------------------------------------------------------------------------
# TODO: uninstall - fix
add_custom_target(uninstall
    COMMAND
        ${CMAKE_COMMAND}
        -DXLIB_INSTALL_PATH="${XLIB_INSTALL_PATH}"
        -P Uninstall.cmake
    COMMENT
        "Uninstall...")
#--------------------------------------------------------------------------------------------------
# template
add_custom_target(template
    COMMAND
        ${CMAKE_COMMAND}
        -DXLIB_LOCATION="${XLIB_LOCATION}" -DXLIB_TEMPLATES="${XLIB_TEMPLATES}"
        -P ${XLIB_LOCATION}/CMake/Template.cmake
    COMMENT
        "Template...")
#--------------------------------------------------------------------------------------------------
# fix warning "Manually-specified variables were not used by the project"
unset(CMAKE_TOOLCHAIN_FILE)
#--------------------------------------------------------------------------------------------------
# tests
if (cmOPTION_BUILD_TESTS)
    enable_testing()

    add_subdirectory(${XLIB_LOCATION}/Tests/Core)
    add_subdirectory(${XLIB_LOCATION}/Tests/Interface)
    add_subdirectory(${XLIB_LOCATION}/Tests/Pattern)
    add_subdirectory(${XLIB_LOCATION}/Tests/Algo)
    add_subdirectory(${XLIB_LOCATION}/Tests/Crypt)
    add_subdirectory(${XLIB_LOCATION}/Tests/System)
    add_subdirectory(${XLIB_LOCATION}/Tests/Test)
    add_subdirectory(${XLIB_LOCATION}/Tests/Log)
    add_subdirectory(${XLIB_LOCATION}/Tests/Debug)
    add_subdirectory(${XLIB_LOCATION}/Tests/Fs)
    add_subdirectory(${XLIB_LOCATION}/Tests/Net)
    add_subdirectory(${XLIB_LOCATION}/Tests/Sync)
    add_subdirectory(${XLIB_LOCATION}/Tests/Db)
    add_subdirectory(${XLIB_LOCATION}/Tests/Ui)

    add_subdirectory(${XLIB_LOCATION}/Tests/Package)
endif()
#--------------------------------------------------------------------------------------------------
