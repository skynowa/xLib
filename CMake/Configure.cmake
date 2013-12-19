#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


include(CheckLibraryExists)
include(CheckCXXSourceCompiles)
include(FindMySQL)
include(FindExecInfo)


#--------------------------------------------------------------------------------------------------
# find packages
find_package(OpenSSL REQUIRED)
find_package(MySQL REQUIRED)
find_package(ExecInfo REQUIRED)

#--------------------------------------------------------------------------------------------------
# configure
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h)

check_library_exists(crypto BF_cfb64_encrypt "" xHAVE_OPENSSL_CRYPTO)

if (WIN32)
    # TODO: windows part
elseif (UNIX)
    # xHAVE_EXECINFO
    if (EXECINFO_FOUND)
        add_definitions(-DxHAVE_EXECINFO=1)
        include_directories(${EXECINFO_INCLUDES})
        link_libraries(${EXECINFO_LIBRARIES})
    endif()

    # xHAVE_PR_SET_DUMPABLE
    check_cxx_source_compiles(
        "#include <sys/prctl.h>

        int main()
        {
            ::prctl(PR_SET_DUMPABLE, 0);
            return 0;
        }"
        xHAVE_PR_SET_DUMPABLE)

    # xHAVE_RLIMIT_CORE
    check_cxx_source_compiles(
        "#include <sys/resource.h>

        int main()
        {
            struct rlimit limit = {0, 0}
            ::setrlimit(RLIMIT_CORE, &limit);
            return 0;
        }"
        xHAVE_RLIMIT_CORE)

    # xHAVE_ADDR2LINE
    find_file(IS_ADDR2LINE "addr2line")
    if (IS_ADDR2LINE)
        set(DEFINITIONS ${DEFINITIONS} "xHAVE_ADDR2LINE=1")
        message(STATUS "addr2line - found")
    else()
        set(DEFINITIONS ${DEFINITIONS} "xHAVE_ADDR2LINE=0")
        message(WARNING "addr2line - failed")
    endif()

    if (APPLE)
        # xHAVE_PT_DENY_ATTACH
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
#--------------------------------------------------------------------------------------------------
