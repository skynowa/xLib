/**
 * \file  xCore_unix.h
 * \brief Unix core header for xLib
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#if   xOS_LINUX
    #include <sys/vfs.h>
    #include <sys/prctl.h>
    #include <sys/sysinfo.h>
    #include <mntent.h>
    #include <gnu/libc-version.h>
#elif xOS_ANDROID

#endif
//-------------------------------------------------------------------------------------------------
