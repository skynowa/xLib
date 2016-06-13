#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# unset cache
unset(cmHAVE_EXECINFO CACHE)
unset(cmHAVE_XCB CACHE)
unset(cmHAVE_ADDR2LINE CACHE)
unset(cmADDR2LINE_FILE_PATH  CACHE)
unset(cmHAVE_GIT_REVISION CACHE)
unset(cmGIT_REVISION_BRANCH CACHE)
unset(cmGIT_REVISION_HASH CACHE)
unset(cmHAVE_OPENSSL_CRYPTO CACHE)
unset(cmHAVE_MYSQL CACHE)
unset(cmHAVE_PR_SET_DUMPABLE CACHE)
unset(cmHAVE_RLIMIT_CORE CACHE)
unset(cmHAVE_PT_DENY_ATTACH CACHE)
unset(cmHAVE_SCHED_GETCPU CACHE)
unset(cmHAVE_GETLOGIN_R CACHE)
unset(cmHAVE_GNU_GET_LIBC CACHE)
unset(cmHAVE_CS_GNU_LIBPTHREAD_VERSION CACHE)
unset(cmHAVE_SCHED_SETAFFINITY CACHE)
unset(cmHAVE_GETSID CACHE)
unset(cmHAVE_GETPWUID_R CACHE)
unset(cmHAVE_SETMNTENT CACHE)
unset(cmHAVE_GETMNTENT_R CACHE)
unset(cmHAVE_ENDMNTENT CACHE)
unset(cmHAVE_RAND_R CACHE)
unset(cmHAVE_SRANDOM_R CACHE)
unset(cmHAVE_RANDOM_R CACHE)

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
find_package(GitRevision QUIET REQUIRED)
find_package(OS QUIET REQUIRED)
find_package(OpenSSL QUIET)
find_package(MySQL QUIET)
find_package(Ssh2 QUIET REQUIRED)

if (ENV_UNIX)
   find_package(ExecInfo QUIET REQUIRED)
   find_package(XCB QUIET)
   find_package(Addr2Line QUIET)
endif()
#--------------------------------------------------------------------------------------------------
# configure
if (GIT_REVISION_FOUND)
    set(cmHAVE_GIT_REVISION   1)
    set(cmGIT_REVISION_BRANCH ${GIT_REVISION_BRANCH})
    set(cmGIT_REVISION_HASH   ${GIT_REVISION_HASH})
endif()

if (OPENSSL_FOUND)
    check_library_exists(crypto BF_cfb64_encrypt "" cmHAVE_OPENSSL_CRYPTO)
endif()

if (ENV_WIN)
    # TODO: windows part
elseif (ENV_UNIX)
    ########## Libs ##########
    set(cmHAVE_EXECINFO ${EXECINFO_FOUND})
    set(cmHAVE_XCB ${XCB_FOUND})

    # cmHAVE_ADDR2LINE
    if (ADDR2LINE_FOUND)
        set(cmHAVE_ADDR2LINE      1)
        set(cmADDR2LINE_FILE_PATH ${ADDR2LINE_FILE_PATH})
    endif()

    ########## Symbols ##########
    CHECK_SYMBOL_EXISTS(PR_SET_DUMPABLE "sys/prctl.h"    cmHAVE_PR_SET_DUMPABLE)
    CHECK_SYMBOL_EXISTS(RLIMIT_CORE     "sys/resource.h" cmHAVE_RLIMIT_CORE)
    # CHECK_SYMBOL_EXISTS(xxxxx         aaaaaaa          cmHAVE_DDDDDDDDDDDDDDDD)

    ########## Functions ##########
    CHECK_FUNCTION_EXISTS(sched_getcpu      cmHAVE_SCHED_GETCPU)
    CHECK_FUNCTION_EXISTS(getcpu            cmHAVE_GETCPU)
    CHECK_FUNCTION_EXISTS(getlogin_r        cmHAVE_GETLOGIN_R)
    CHECK_FUNCTION_EXISTS(sched_setaffinity cmHAVE_SCHED_SETAFFINITY)
    CHECK_FUNCTION_EXISTS(getsid            cmHAVE_GETSID)
    CHECK_FUNCTION_EXISTS(getpwuid_r        cmHAVE_GETPWUID_R)
    CHECK_FUNCTION_EXISTS(setmntent         cmHAVE_SETMNTENT)
    CHECK_FUNCTION_EXISTS(getmntent_r       cmHAVE_GETMNTENT_R)
    CHECK_FUNCTION_EXISTS(endmntent         cmHAVE_ENDMNTENT)
    CHECK_FUNCTION_EXISTS(rand_r            cmHAVE_RAND_R)
    CHECK_FUNCTION_EXISTS(srandom_r         cmHAVE_SRANDOM_R)
    CHECK_FUNCTION_EXISTS(srandom_r         cmHAVE_RANDOM_R)
    # CHECK_FUNCTION_EXISTS(xxxxx           cmHAVE_DDDDDDDDDDDDDDDD)

    # cmHAVE_GNU_GET_LIBC
    CHECK_FUNCTION_EXISTS(gnu_get_libc_version _xGNU_GET_LIBC_VERSION)
    CHECK_FUNCTION_EXISTS(gnu_get_libc_release _xGNU_GET_LIBC_RELEASE)
    if (${_xGNU_GET_LIBC_VERSION} AND ${_xGNU_GET_LIBC_RELEASE})
        set(cmHAVE_GNU_GET_LIBC 1)
    endif()

    # cmHAVE_CS_GNU_LIBPTHREAD_VERSION
    CHECK_FUNCTION_EXISTS(confstr _xCONFSTR)
    CHECK_SYMBOL_EXISTS(_CS_GNU_LIBPTHREAD_VERSION "unistd.h" _xCS_GNU_LIBPTHREAD_VERSION)
    if (${_xCONFSTR} AND ${_xCS_GNU_LIBPTHREAD_VERSION})
        set(cmHAVE_CS_GNU_LIBPTHREAD_VERSION 1)
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
        CHECK_SYMBOL_EXISTS(PT_DENY_ATTACH "sys/ptrace.h" cmHAVE_PT_DENY_ATTACH)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${XLIB_LOCATION}/Include/xLib/Core/Config_gen.h.in
    ${XLIB_LOCATION}/Include/xLib/Core/Config_gen.h)
#--------------------------------------------------------------------------------------------------
