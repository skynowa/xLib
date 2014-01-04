/**
 * \file  xCommon_Darwin.h
 * \brief Darwin common header for xLib
 */


#pragma once

#ifndef xLib_xCore_DarwinH
#define xLib_xCore_DarwinH
//-------------------------------------------------------------------------------------------------
// POSIX
#include <cpio.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <tar.h>
#include <termios.h>
#include <unistd.h>
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

// Darwin
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/user.h>       // for struct kinfo_proc

// socket
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// system
#include <sys/resource.h>
//-------------------------------------------------------------------------------------------------
#endif // xLib_xCore_DarwinH
