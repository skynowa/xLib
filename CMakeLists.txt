#--------------------------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib_test)

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(Configure)

#--------------------------------------------------------------------------------------------------
# includes
include_directories("${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")
include_directories("${OPENSSL_INCLUDE_DIR}")
include_directories("${MYSQL_INCLUDES}")
include_directories("${EXECINFO_INCLUDES}")

#--------------------------------------------------------------------------------------------------
# vars
set(XLIB_INSTALL_DIR  include/xLib)
set(XLIB_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${XLIB_INSTALL_DIR}")

#--------------------------------------------------------------------------------------------------
# sources
file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")

#--------------------------------------------------------------------------------------------------
# target
add_executable(xLib_test ${xLib_tests_SOURCES})

#--------------------------------------------------------------------------------------------------
# flags
if     (MSVC)
    set(FLAGS ${FLAGS} "/W3")
elseif (MINGW)
    set(LIBS ${LIBS} ws2_32 psapi uuid ole32 mpr)
    set(FLAGS ${FLAGS} "-Wall -pipe")
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(LIBS ${LIBS} pthread rt m z)
    set(FLAGS ${FLAGS} "-pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror -fcolor-diagnostics -Qunused-arguments "
        "-U__STRICT_ANSI__ -D__STDC_FORMAT_MACROS")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(LIBS ${LIBS} pthread rt m z)
    set(FLAGS ${FLAGS} "-pipe -Wall -Wno-deprecated -Wextra -Wconversion -Wshadow "
        "-Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas "
        "-Wno-return-type-c-linkage -Werror -U__STRICT_ANSI__ -D__STDC_FORMAT_MACROS")
else()
    message("xLib: unknown compiler")
endif()

set_target_properties(
    xLib_test PROPERTIES
        COMPILE_DEFINITIONS ${DEFINITIONS}
        COMPILE_FLAGS ${FLAGS}
)

target_link_libraries(xLib_test
    ${LIBS} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES} ${MYSQL_LIBRARIES}
    ${EXECINFO_LIBRARIES})

#--------------------------------------------------------------------------------------------------
# install
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/Include/xLib/
    DESTINATION ${XLIB_INSTALL_PATH}
    FILES_MATCHING PATTERN "*" PATTERN "*.h.in" EXCLUDE)

#--------------------------------------------------------------------------------------------------
# uninstall
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
