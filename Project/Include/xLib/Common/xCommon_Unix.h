/**
 * \file  xCommon_Unix.h
 * \brief Unix common header for xLib
 */


//----------------------------------------------------------------------------------------------------
#ifndef xLib_Common_Unix_xCommon_UnixH
#define xLib_Common_Unix_xCommon_UnixH
//----------------------------------------------------------------------------------------------------
#if !defined(_GNU_SOURCE)
    #define _GNU_SOURCE 1
#endif

//----------------------------------------------------------------------------------------------------

// POSIX
#include <string.h>
#include <cpio.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <tar.h>
#include <termios.h>
#include <unistd.h>
#include <utime.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <sys/syscall.h>
#include <sys/param.h>

// filesystem


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
    #include <pthread_np.h>    // lib: libpthread, -lpthread (FreeBSD)
    #include <sys/mount.h>
    #include <sys/statvfs.h>
    #include <sys/resource.h>
    #include <sys/sysctl.h>
#endif

// socket
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//----------------------------------------------------------------------------------------------------
#endif // xLib_Common_Unix_xCommon_UnixH
//----------------------------------------------------------------------------------------------------
