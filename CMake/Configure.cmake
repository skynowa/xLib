#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# unset cache
unset(xHAVE_GIT_REVISION CACHE)
unset(xGIT_REVISION_BRANCH CACHE)
unset(xGIT_REVISION_HASH CACHE)
unset(xHAVE_OPENSSL_CRYPTO CACHE)
unset(xHAVE_MYSQL CACHE)
unset(xHAVE_PR_SET_DUMPABLE CACHE)
unset(xHAVE_RLIMIT_CORE CACHE)
unset(xHAVE_PT_DENY_ATTACH CACHE)
unset(xHAVE_SCHED_GETCPU CACHE)
unset(xHAVE_GETLOGIN_R CACHE)
unset(xHAVE_GNU_GET_LIBC CACHE)
unset(xHAVE_CS_GNU_LIBPTHREAD_VERSION CACHE)
unset(xHAVE_SCHED_SETAFFINITY CACHE)
unset(xHAVE_GETSID CACHE)

# internal
unset(_xGNU_GET_LIBC_VERSION CACHE)
unset(_xGNU_GET_LIBC_RELEASE CACHE)
unset(_xCONFSTR CACHE)
unset(_xCS_GNU_LIBPTHREAD_VERSION CACHE)

unset(xHAVE_EXECINFO CACHE)
unset(xHAVE_XCB CACHE)
unset(xHAVE_ADDR2LINE CACHE)
unset(xADDR2LINE_FILE_PATH  CACHE)

#--------------------------------------------------------------------------------------------------
# includes
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)

#--------------------------------------------------------------------------------------------------
# find packages
find_package(GitRevision REQUIRED)
find_package(OS REQUIRED)
find_package(OpenSSL)
find_package(MySQL)

if (ENV_UNIX)
   find_package(ExecInfo REQUIRED)
   find_package(XCB)
   find_package(Addr2Line)
endif()
#--------------------------------------------------------------------------------------------------
# configure
if (GIT_REVISION_FOUND)
    set(xHAVE_GIT_REVISION   1)
    set(xGIT_REVISION_BRANCH ${GIT_REVISION_BRANCH})
    set(xGIT_REVISION_HASH   ${GIT_REVISION_HASH})
endif()

if (OPENSSL_FOUND)
    check_library_exists(crypto BF_cfb64_encrypt "" xHAVE_OPENSSL_CRYPTO)
endif()

if (ENV_WIN)
    # TODO: windows part
elseif (ENV_UNIX)
    set(xHAVE_EXECINFO ${EXECINFO_FOUND})
    set(xHAVE_XCB ${XCB_FOUND})

    # xHAVE_ADDR2LINE
    if (ADDR2LINE_FOUND)
        set(xHAVE_ADDR2LINE      1)
        set(xADDR2LINE_FILE_PATH ${ADDR2LINE_FILE_PATH})
    endif()

    # xHAVE_PR_SET_DUMPABLE
    # check_cxx_source_compiles(
    #     "#include <sys/prctl.h>
    #
    #     int main()
    #     {
    #         (int)::prctl(PR_SET_DUMPABLE, 0);
    #         return 0;
    #     }"
    #     xHAVE_PR_SET_DUMPABLE
    # )
    CHECK_SYMBOL_EXISTS(PR_SET_DUMPABLE "sys/prctl.h" xHAVE_PR_SET_DUMPABLE)

    # xHAVE_RLIMIT_CORE
    # check_cxx_source_compiles(
    #     "#include <sys/resource.h>

    #     int main()
    #     {
    #         struct rlimit limit = {0, 0}
    #         (int)::setrlimit(RLIMIT_CORE, &limit);
    #         return 0;
    #     }"
    #     xHAVE_RLIMIT_CORE
    # )
    CHECK_SYMBOL_EXISTS(RLIMIT_CORE "sys/resource.h" xHAVE_RLIMIT_CORE)

    # xHAVE_SCHED_GETCPU
    # check_cxx_source_compiles(
    #     "#define _GNU_SOURCE
    #     #include <sched.h>

    #     int main()
    #     {
    #         (int)::sched_getcpu();
    #         return 0;
    #     }"
    #     xHAVE_SCHED_GETCPU
    # )
    CHECK_FUNCTION_EXISTS(sched_getcpu xHAVE_SCHED_GETCPU)

    # xHAVE_GETCPU
    # check_cxx_source_compiles(
    #     "#include <linux/getcpu.h>

    #     int main()
    #     {
    #         unsigned int cpu = 0U;
    #         (int)::getcpu(&cpu, NULL, NULL);
    #         return 0;
    #     }"
    #     xHAVE_GETCPU
    # )
    CHECK_FUNCTION_EXISTS(getcpu xHAVE_GETCPU)

    # xHAVE_GETLOGIN_R
    # check_cxx_source_compiles(
    #     "#include <stdio.h>
    #     #include <unistd.h>

    #     int main()
    #     {
    #         char buff[L_cuserid + 1] = {0};
    #         (int)::getlogin_r(buff, L_cuserid);
    #         return 0;
    #     }"
    #     xHAVE_GETLOGIN_R
    # )
    CHECK_FUNCTION_EXISTS(getlogin_r xHAVE_GETLOGIN_R)

    # xHAVE_GNU_GET_LIBC
    # check_cxx_source_compiles(
    #     "#include <gnu/libc-version.h>

    #     int main()
    #     {
    #         (const char *)::gnu_get_libc_version();
    #         (const char *)::gnu_get_libc_release();
    #         return 0;
    #     }"
    #     xHAVE_GNU_GET_LIBC
    # )
    CHECK_FUNCTION_EXISTS(gnu_get_libc_version _xGNU_GET_LIBC_VERSION)
    CHECK_FUNCTION_EXISTS(gnu_get_libc_release _xGNU_GET_LIBC_RELEASE)

    if (${_xGNU_GET_LIBC_VERSION} AND ${_xGNU_GET_LIBC_RELEASE})
        set(xHAVE_GNU_GET_LIBC 1)
    endif()

    # xHAVE_CS_GNU_LIBPTHREAD_VERSION
    # check_cxx_source_compiles(
    #     "#include <unistd.h>
    #     #include <cstddef>

    #     int main()
    #     {
    #         (std::size_t)::confstr(_CS_GNU_LIBPTHREAD_VERSION, NULL, 0);
    #         return 0;
    #     }"
    #     xHAVE_CS_GNU_LIBPTHREAD_VERSION
    # )
    CHECK_FUNCTION_EXISTS(confstr _xCONFSTR)
    CHECK_SYMBOL_EXISTS(_CS_GNU_LIBPTHREAD_VERSION "unistd.h" _xCS_GNU_LIBPTHREAD_VERSION)

    if (${_xCONFSTR} AND ${_xCS_GNU_LIBPTHREAD_VERSION})
        set(xHAVE_CS_GNU_LIBPTHREAD_VERSION 1)
    endif()

    # xHAVE_SCHED_SETAFFINITY
    # check_cxx_source_compiles(
    #     "#include <sys/types.h>
    #     #include <unistd.h>
    #     #define _GNU_SOURCE
    #     #include <sched.h>

    #     int main()
    #     {
    #     #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
    #         cpuset_t  cpuSet;
    #     #else
    #         cpu_set_t cpuSet;
    #     #endif

    #         CPU_ZERO(&cpuSet);
    #         CPU_SET(1, &cpuSet);

    #         (int)::sched_setaffinity(::getpid(), sizeof(cpuSet), &cpuSet);
    #         return 0;
    #     }"
    #     xHAVE_SCHED_SETAFFINITY
    # )
    CHECK_FUNCTION_EXISTS(sched_setaffinity xHAVE_SCHED_SETAFFINITY)

    # xHAVE_GETSID
    # check_cxx_source_compiles(
    #     "#include <unistd.h>
    #      #include <sys/syscall.h>

    #     int main()
    #     {
    #         (pid_t)::getsid(static_cast<pid_t>( 0 ));
    #         return 0;
    #     }"
    #     xHAVE_GETSID
    # )
    CHECK_FUNCTION_EXISTS(getsid xHAVE_GETSID)

    # # xHAVE_[FUNCTION_NAME]
    # check_cxx_source_compiles(
    #     "#include <unistd.h>
    #     #include <sys/syscall.h>
    #
    #     int main()
    #     {
    #         [function_name];
    #         return 0;
    #     }"
    #     xHAVE_[FUNCTION_NAME]
    # )

    # Linux
    if (ENV_LINUX)
        if (OS_ANDROID)
            #
        else(OS_LINUX)
            #
        endif()
    endif()

    # BSD
    if (ENV_BSD)
        if (OS_FREEBSD)
            #
        endif()
    endif()

    # Apple
    if (ENV_APPLE)
        # # xHAVE_PT_DENY_ATTACH
        # check_cxx_source_compiles(
        #     "#include <sys/types.h>
        #     #include <sys/ptrace.h>

        #     int main()
        #     {
        #         ::ptrace(PT_DENY_ATTACH, 0, 0, 0);
        #         return 0;
        #     }"
        #     xHAVE_PT_DENY_ATTACH
        # )
        CHECK_SYMBOL_EXISTS(PT_DENY_ATTACH "sys/ptrace.h" xHAVE_PT_DENY_ATTACH)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig_gen.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig_gen.h)
#--------------------------------------------------------------------------------------------------
