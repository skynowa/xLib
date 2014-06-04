/**
 * \file  xCore_unix.h
 * \brief Unix core header for xLib
 */


#pragma once

#if   xOS_LINUX
    #include <linux/version.h>
    #include <gnu/libc-version.h>
    #include <sys/vfs.h>
    #include <sys/prctl.h>
    #include <sys/sysinfo.h>
    #include <mntent.h>

    // POSIX
    #include <cpio.h>
    #include <tar.h>
    #include <sys/msg.h>

    // thread
    #include <sys/sem.h>

    // GUI
    #if xTEMP_DISABLED
        #include <linux/kd.h>   // beep
        #include <X11/Xlib.h>   // beep -lX11
    #endif
#elif xOS_ANDROID

#endif
