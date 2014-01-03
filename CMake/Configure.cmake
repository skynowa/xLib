#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


include(CheckLibraryExists)
include(CheckCXXSourceCompiles)
include(FindMySQL)
include(FindExecInfo)

#--------------------------------------------------------------------------------------------------
# unset cache
unset(xHAVE_OPENSSL_CRYPTO  CACHE)
unset(xHAVE_MYSQL           CACHE)
unset(xHAVE_PR_SET_DUMPABLE CACHE)
unset(xHAVE_RLIMIT_CORE     CACHE)
unset(xHAVE_PT_DENY_ATTACH  CACHE)
unset(xHAVE_SCHED_GETCPU    CACHE)
unset(xHAVE_SCHED_GETCPU    CACHE)
unset(xHAVE_ADDR2LINE       CACHE)
unset(xHAVE_XMESSAGE        CACHE)
unset(xHAVE_EXECINFO        CACHE)

#--------------------------------------------------------------------------------------------------
# find packages
find_package(OpenSSL)
find_package(MySQL)

if (UNIX)
    find_package(X11)
    find_package(ExecInfo REQUIRED)
endif()

#--------------------------------------------------------------------------------------------------
# configure
if (OPENSSL_FOUND)
    check_library_exists(crypto BF_cfb64_encrypt "" xHAVE_OPENSSL_CRYPTO)
endif()

if (WIN32)
    # TODO: windows part
elseif (UNIX)
    if (X11_FOUND)
        set(xHAVE_X11 TRUE)
    endif()

    # xHAVE_EXECINFO
    if (EXECINFO_FOUND)
        set(xHAVE_EXECINFO TRUE)
    endif()

    # xHAVE_PR_SET_DUMPABLE
    check_cxx_source_compiles(
        "#include <sys/prctl.h>

        int main()
        {
            ::prctl(PR_SET_DUMPABLE, 0);
            return 0;
        }"
        xHAVE_PR_SET_DUMPABLE
    )

    # xHAVE_RLIMIT_CORE
    check_cxx_source_compiles(
        "#include <sys/resource.h>

        int main()
        {
            struct rlimit limit = {0, 0}
            ::setrlimit(RLIMIT_CORE, &limit);
            return 0;
        }"
        xHAVE_RLIMIT_CORE
    )

    # xHAVE_ADDR2LINE
    find_file(xHAVE_ADDR2LINE "addr2line")
    if (xHAVE_ADDR2LINE)
        message(STATUS "addr2line - found")
    else()
        message(WARNING "addr2line - failed")
    endif()

    # xHAVE_XMESSAGE
    find_file(xHAVE_XMESSAGE "xmessage")
    if (xHAVE_XMESSAGE)
        message(STATUS "xmessage - found")
    else()
        message(WARNING "xmessage - failed")
    endif()

    # xHAVE_SCHED_GETCPU
    check_cxx_source_compiles(
        "#define _GNU_SOURCE
        #include <sched.h>

        int main()
        {
            int iRv = ::sched_getcpu();
            return 0;
        }"
        xHAVE_SCHED_GETCPU
    )

    # xHAVE_GETCPU
    check_cxx_source_compiles(
        "#include <linux/getcpu.h>

        int main()
        {
            unsigned int cpu = 0U;
            int iRv = ::getcpu(&cpu, NULL, NULL);
            return 0;
        }"
        xHAVE_GETCPU
    )


    # Linux
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    endif()


    # Apple
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
            xHAVE_PT_DENY_ATTACH
        )
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h)
#--------------------------------------------------------------------------------------------------
