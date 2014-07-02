#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# unset cache
unset(xHAVE_EXECINFO CACHE)
unset(xHAVE_XCB CACHE)
unset(xHAVE_ADDR2LINE CACHE)
unset(xADDR2LINE_FILE_PATH  CACHE)
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
unset(xHAVE_GETPWUID_R CACHE)
unset(xHAVE_SETMNTENT CACHE)
unset(xHAVE_GETMNTENT_R CACHE)
unset(xHAVE_ENDMNTENT CACHE)
unset(xHAVE_RAND_R CACHE)
unset(xHAVE_SRANDOM_R CACHE)
unset(xHAVE_RANDOM_R CACHE)

# internal
unset(_xGNU_GET_LIBC_VERSION CACHE)
unset(_xGNU_GET_LIBC_RELEASE CACHE)
unset(_xCONFSTR CACHE)
unset(_xCS_GNU_LIBPTHREAD_VERSION CACHE)
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
    ########## Libs ##########
    set(xHAVE_EXECINFO ${EXECINFO_FOUND})
    set(xHAVE_XCB ${XCB_FOUND})

    # xHAVE_ADDR2LINE
    if (ADDR2LINE_FOUND)
        set(xHAVE_ADDR2LINE      1)
        set(xADDR2LINE_FILE_PATH ${ADDR2LINE_FILE_PATH})
    endif()

    ########## Symbols ##########
    CHECK_SYMBOL_EXISTS(PR_SET_DUMPABLE "sys/prctl.h"    xHAVE_PR_SET_DUMPABLE)
    CHECK_SYMBOL_EXISTS(RLIMIT_CORE     "sys/resource.h" xHAVE_RLIMIT_CORE)
    # CHECK_SYMBOL_EXISTS(xxxxx         aaaaaaa          xHAVE_DDDDDDDDDDDDDDDD)

    ########## Functions ##########
    CHECK_FUNCTION_EXISTS(sched_getcpu      xHAVE_SCHED_GETCPU)
    CHECK_FUNCTION_EXISTS(getcpu            xHAVE_GETCPU)
    CHECK_FUNCTION_EXISTS(getlogin_r        xHAVE_GETLOGIN_R)
    CHECK_FUNCTION_EXISTS(sched_setaffinity xHAVE_SCHED_SETAFFINITY)
    CHECK_FUNCTION_EXISTS(getsid            xHAVE_GETSID)
    CHECK_FUNCTION_EXISTS(getpwuid_r        xHAVE_GETPWUID_R)
    CHECK_FUNCTION_EXISTS(setmntent         xHAVE_SETMNTENT)
    CHECK_FUNCTION_EXISTS(getmntent_r       xHAVE_GETMNTENT_R)
    CHECK_FUNCTION_EXISTS(endmntent         xHAVE_ENDMNTENT)
    CHECK_FUNCTION_EXISTS(rand_r            xHAVE_RAND_R)
    CHECK_FUNCTION_EXISTS(srandom_r         xHAVE_SRANDOM_R)
    CHECK_FUNCTION_EXISTS(srandom_r         xHAVE_RANDOM_R)
    # CHECK_FUNCTION_EXISTS(xxxxx           xHAVE_DDDDDDDDDDDDDDDD)

    # xHAVE_GNU_GET_LIBC
    CHECK_FUNCTION_EXISTS(gnu_get_libc_version _xGNU_GET_LIBC_VERSION)
    CHECK_FUNCTION_EXISTS(gnu_get_libc_release _xGNU_GET_LIBC_RELEASE)
    if (${_xGNU_GET_LIBC_VERSION} AND ${_xGNU_GET_LIBC_RELEASE})
        set(xHAVE_GNU_GET_LIBC 1)
    endif()

    # xHAVE_CS_GNU_LIBPTHREAD_VERSION
    CHECK_FUNCTION_EXISTS(confstr _xCONFSTR)
    CHECK_SYMBOL_EXISTS(_CS_GNU_LIBPTHREAD_VERSION "unistd.h" _xCS_GNU_LIBPTHREAD_VERSION)
    if (${_xCONFSTR} AND ${_xCS_GNU_LIBPTHREAD_VERSION})
        set(xHAVE_CS_GNU_LIBPTHREAD_VERSION 1)
    endif()

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
        ########## Symbols ##########
        CHECK_SYMBOL_EXISTS(PT_DENY_ATTACH "sys/ptrace.h" xHAVE_PT_DENY_ATTACH)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/Config_gen.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/Config_gen.h)
#--------------------------------------------------------------------------------------------------
