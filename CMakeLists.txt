#--------------------------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required (VERSION 2.6)
include(CheckCXXSourceCompiles)

project (xLib_test)

#--------------------------------------------------------------------------------------------------
# prepare
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h)

find_package(OpenSSL REQUIRED)

if (UNIX)
    check_cxx_source_compiles(
        "#include <sys/prctl.h>

        int main() {
            ::prctl(PR_SET_DUMPABLE, 0);
            return 0;
        }"
        xHAVE_PR_SET_DUMPABLE)

    check_cxx_source_compiles(
        "#include <sys/resource.h>

        int main()
        {
            struct rlimit limit = {0, 0}
            ::setrlimit(RLIMIT_CORE, &limit);
            return 0;
        }"
        xHAVE_RLIMIT_CORE)

    if (APPLE)
        check_cxx_source_compiles(
            "#include <sys/types.h>
            #include <sys/ptrace.h>

            int main()
            {
                ::ptrace(PT_DENY_ATTACH, 0, 0, 0);
                return 0;
            }"
            xHAVE_PT_DENY_ATTACH)
    endif()
endif()

if (CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

#--------------------------------------------------------------------------------------------------
# includes
include_directories("${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/Tests/Include")
include_directories("${OPENSSL_INCLUDE_DIR}")
#--------------------------------------------------------------------------------------------------
# sources
file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")

#--------------------------------------------------------------------------------------------------
# target
add_executable(xLib_test ${xLib_tests_SOURCES})

#--------------------------------------------------------------------------------------------------
# flags
if     (MSVC)
    #set(LIBS ${LIBS} mysqlclient)
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

if (OPENSSL_FOUND)
    message("OpenSSL found:       ${OPENSSL_FOUND}")
    message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
    message("OpenSSL libraries:   ${OPENSSL_LIBRARIES}")

    set(XLIB_TESTS_DEFINITIONS ${XLIB_TESTS_DEFINITIONS} xOPENSSL_IS_USE=1)
endif(OPENSSL_FOUND)

set_target_properties(
    xLib_test PROPERTIES
        COMPILE_DEFINITIONS ${XLIB_TESTS_DEFINITIONS}
        COMPILE_FLAGS ${FLAGS}
)

target_link_libraries(xLib_test ${LIBS} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES})

#--------------------------------------------------------------------------------------------------
# install
set(XLib_INCLUDE_DIRS "")

file(GLOB_RECURSE XLib_HEADERS "Include/*")

foreach(_headerFile ${XLib_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND XLib_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES XLib_INCLUDE_DIRS)

install(DIRECTORY ${XLib_INCLUDE_DIRS} DESTINATION "include/xLib")
