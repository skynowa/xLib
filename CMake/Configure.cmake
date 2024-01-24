#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief xLib - configure sources
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# includes
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)
#--------------------------------------------------------------------------------------------------
# find packages

# System
find_package(Threads     QUIET REQUIRED)
find_package(OpenSSL     QUIET REQUIRED)
find_package(CURL        QUIET REQUIRED)
find_package(LibXml2     QUIET REQUIRED)

# Custom (CMakeLib)
find_package(CMakeLib    QUIET REQUIRED) # at 1-st
find_package(OS          QUIET REQUIRED)
find_package(GitRevision QUIET REQUIRED)

#- find_package(MySQL       QUIET REQUIRED)
## find_package(libmysqlclient)
include(zstd-config)
include(libmysqlclient-config)

#- find_package(Ssh2        QUIET REQUIRED)
find_package(Libssh2)

find_package(Iconv       QUIET REQUIRED)
find_package(ZLIB)

if (ENV_UNIX)
    # Custom (CMakeLib)
    find_package(ExecInfo QUIET REQUIRED)

    if (ENV_APPLE)
        find_package(Atos QUIET REQUIRED)
    else()
        find_package(Addr2Line QUIET REQUIRED)
    endif()

    # cmGNU_GET_LIBC_FOUND
    CHECK_FUNCTION_EXISTS(gnu_get_libc_version _xGNU_GET_LIBC_VERSION)
    CHECK_FUNCTION_EXISTS(gnu_get_libc_release _xGNU_GET_LIBC_RELEASE)
    if (_xGNU_GET_LIBC_VERSION AND _xGNU_GET_LIBC_RELEASE)
        set(cmGNU_GET_LIBC_FOUND 1)
    endif()

    # cmCS_GNU_LIBPTHREAD_VERSION_FOUND
    CHECK_FUNCTION_EXISTS(confstr _xCONFSTR)
    CHECK_SYMBOL_EXISTS(_CS_GNU_LIBPTHREAD_VERSION "unistd.h" _xCS_GNU_LIBPTHREAD_VERSION)
    if (_xCONFSTR AND _xCS_GNU_LIBPTHREAD_VERSION)
        set(cmCS_GNU_LIBPTHREAD_VERSION_FOUND 1)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# includes (CMakeLib)
include(WarningFlagsAll)
#--------------------------------------------------------------------------------------------------
# configure
if     (ENV_WIN)
    # TODO: windows part
elseif (ENV_UNIX)
    # Headers
    CHECK_INCLUDE_FILES("features.h" cmHAVE_FEATURES_H)

    # Libs

    # Symbols
    CHECK_SYMBOL_EXISTS(PR_SET_DUMPABLE "sys/prctl.h"    cmHAVE_PR_SET_DUMPABLE)
    CHECK_SYMBOL_EXISTS(RLIMIT_CORE     "sys/resource.h" cmHAVE_RLIMIT_CORE)

    # Functions
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
    CHECK_FUNCTION_EXISTS(random_r          cmHAVE_RANDOM_R)

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
        # Symbols
        CHECK_SYMBOL_EXISTS(PT_DENY_ATTACH "sys/ptrace.h" cmHAVE_PT_DENY_ATTACH)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# config
if (DEFINED XLIB_LOCATION)
    set(CONFIG_PATH "${XLIB_LOCATION}/Include/xLib/Config.h")

    configure_file("${CONFIG_PATH}.in" ${CONFIG_PATH})
endif()
#--------------------------------------------------------------------------------------------------
