/**
 * \file  xCore_unix.h
 * \brief Unix core header for xLib
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#if xOS_FREEBSD
    #include <osreldate.h>
    #include <pthread_np.h>     // lib: libpthread, -lpthread (FreeBSD)
    #include <sys/mount.h>
    #include <sys/statvfs.h>
    #include <sys/resource.h>
    #include <sys/sysctl.h>
    #include <sys/user.h>       // for struct kinfo_proc

    // POSIX
    #include <cpio.h>
    #include <tar.h>
    #include <sys/msg.h>

    // thread
    #include <sys/sem.h>
#endif
//-------------------------------------------------------------------------------------------------
