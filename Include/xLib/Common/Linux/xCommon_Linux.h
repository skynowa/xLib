/**
 * \file  xCommon_Linux.h
 * \brief Linux common header for xLib
 */


//----------------------------------------------------------------------------------------------------
#ifndef xLib_Common_Linux_xCommon_LinuxH
#define xLib_Common_Linux_xCommon_LinuxH
//----------------------------------------------------------------------------------------------------
//POSIX
#include <cpio.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <tar.h>
#include <termios.h>
#include <unistd.h>
#include <utime.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <sys/syscall.h>
#include <string.h>

//thread
#include <pthread.h>    //lib: -pthread
#include <sched.h>
#include <sys/sem.h>

//dll
#include <dlfcn.h>      //lib: -ldl, -lc (FreeBSD)

#if defined(xOS_FREEBSD)
    #include <osreldate.h>
    #include <pthread_np.h>    //lib: libpthread, -lpthread (FreeBSD)
    #include <sys/param.h>
    #include <sys/mount.h>
    #include <sys/statvfs.h>
    #include <sys/resource.h>
    #include <sys/sysctl.h>
#else
    #include <sys/vfs.h>
    #include <sys/prctl.h>
#endif

//socket
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//----------------------------------------------------------------------------------------------------
#endif //xLib_Common_Linux_xCommon_LinuxH
//----------------------------------------------------------------------------------------------------
