#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# unset cache
unset(cmMYSQL_FOUND CACHE)
unset(cmEXECINFO_FOUND CACHE)
unset(cmXCB_FOUND CACHE)
unset(cmADDR2LINE_FOUND CACHE)
unset(cmADDR2LINE_FILE_PATH  CACHE)
unset(cmGIT_REVISION_FOUND CACHE)
unset(cmGIT_REVISION_BRANCH CACHE)
unset(cmGIT_REVISION_HASH CACHE)
unset(cmCOMPILER_FLAGS CACHE)
unset(cmOPENSSL_CRYPTO_FOUND CACHE)
unset(cmHAVE_FEATURES_H CACHE)
unset(cmPR_SET_DUMPABLE_FOUND CACHE)
unset(cmRLIMIT_CORE_FOUND CACHE)
unset(cmPT_DENY_ATTACH_FOUND CACHE)
unset(cmSCHED_GETCPU_FOUND CACHE)
unset(cmGETCPU_FOUND CACHE)
unset(cmGETLOGIN_R_FOUND CACHE)
unset(cmGNU_GET_LIBC_FOUND CACHE)
unset(cmCS_GNU_LIBPTHREAD_VERSION_FOUND CACHE)
unset(cmSCHED_SETAFFINITY_FOUND CACHE)
unset(cmGETSID_FOUND CACHE)
unset(cmGETPWUID_R_FOUND CACHE)
unset(cmSETMNTENT_FOUND CACHE)
unset(cmGETMNTENT_R_FOUND CACHE)
unset(cmENDMNTENT_FOUND CACHE)
unset(cmRAND_R_FOUND CACHE)
unset(cmSRANDOM_R_FOUND CACHE)
unset(cmRANDOM_R_FOUND CACHE)

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
find_package(CMakeLib QUIET REQUIRED)
find_package(ClangTidy QUIET REQUIRED)
find_package(GitRevision QUIET REQUIRED)
find_package(OS QUIET REQUIRED)
find_package(OpenSSL QUIET REQUIRED)
find_package(MySQL QUIET REQUIRED)
find_package(Ssh2 QUIET REQUIRED)

if (ENV_UNIX)
   find_package(ExecInfo QUIET)    # TODO: REQUIRED - add
   find_package(XCB QUIET)         # TODO: REQUIRED - add
   find_package(Addr2Line QUIET REQUIRED)
endif()
#--------------------------------------------------------------------------------------------------
# configure
if (OPENSSL_FOUND)
    check_library_exists(crypto BF_cfb64_encrypt "" cmOPENSSL_CRYPTO_FOUND)
endif()

if (ENV_WIN)
    # TODO: windows part
elseif (ENV_UNIX)
    # Headers
    CHECK_INCLUDE_FILES("features.h" cmHAVE_FEATURES_H)

    # Libs

    # Symbols
    CHECK_SYMBOL_EXISTS(PR_SET_DUMPABLE "sys/prctl.h"    cmPR_SET_DUMPABLE_FOUND)
    CHECK_SYMBOL_EXISTS(RLIMIT_CORE     "sys/resource.h" cmRLIMIT_CORE_FOUND)
    # CHECK_SYMBOL_EXISTS(xxxxx         aaaaaaa          cmDDDDDDDDDDDDDDDD_FOUND)

    # Functions
    CHECK_FUNCTION_EXISTS(sched_getcpu      cmSCHED_GETCPU_FOUND)
    CHECK_FUNCTION_EXISTS(getcpu            cmGETCPU_FOUND)
    CHECK_FUNCTION_EXISTS(getlogin_r        cmGETLOGIN_R_FOUND)
    CHECK_FUNCTION_EXISTS(sched_setaffinity cmSCHED_SETAFFINITY_FOUND)
    CHECK_FUNCTION_EXISTS(getsid            cmGETSID_FOUND)
    CHECK_FUNCTION_EXISTS(getpwuid_r        cmGETPWUID_R_FOUND)
    CHECK_FUNCTION_EXISTS(setmntent         cmSETMNTENT_FOUND)
    CHECK_FUNCTION_EXISTS(getmntent_r       cmGETMNTENT_R_FOUND)
    CHECK_FUNCTION_EXISTS(endmntent         cmENDMNTENT_FOUND)
    CHECK_FUNCTION_EXISTS(rand_r            cmRAND_R_FOUND)
    CHECK_FUNCTION_EXISTS(srandom_r         cmSRANDOM_R_FOUND)
    CHECK_FUNCTION_EXISTS(srandom_r         cmRANDOM_R_FOUND)
    # CHECK_FUNCTION_EXISTS(xxxxx           cmDDDDDDDDDDDDDDDD_FOUND)

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
        CHECK_SYMBOL_EXISTS(PT_DENY_ATTACH "sys/ptrace.h" cmPT_DENY_ATTACH_FOUND)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
# config
configure_file(
    ${XLIB_LOCATION}/Include/xLib/Config.h.in
    ${XLIB_LOCATION}/Include/xLib/Config.h)
#--------------------------------------------------------------------------------------------------
