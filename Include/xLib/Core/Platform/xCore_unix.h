/**
 * \file  xCommon_Unix.h
 * \brief Unix common header for xLib
 */


#pragma once

#ifndef xLib_xCore_UnixH
#define xLib_xCore_UnixH
//-------------------------------------------------------------------------------------------------
// POSIX
#include <cpio.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <tar.h>
#include <termios.h>
#include <utime.h>
#include <csignal>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <sys/syscall.h>
#include <sys/param.h>

// filesystem
#include <fnmatch.h>    // fnmatch

// thread
#include <pthread.h>    // lib: -pthread
#include <sched.h>
#include <sys/sem.h>
#include <semaphore.h>

// dll
#include <dlfcn.h>

#if   xOS_LINUX
    #include <sys/vfs.h>
    #include <sys/prctl.h>
    #include <sys/sysinfo.h>
    #include <mntent.h>
#elif xOS_FREEBSD
    #include <osreldate.h>
    #include <pthread_np.h>     // lib: libpthread, -lpthread (FreeBSD)
    #include <sys/mount.h>
    #include <sys/statvfs.h>
    #include <sys/resource.h>
    #include <sys/sysctl.h>
    #include <sys/user.h>       // for struct kinfo_proc
#endif

// socket
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// system
#include <sys/resource.h>
//-------------------------------------------------------------------------------------------------
#endif // xLib_xCore_UnixH
