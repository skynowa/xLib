/**
 * \file  xCore_unix.h
 * \brief Unix core header for xLib
 */


#pragma once

//-------------------------------------------------------------------------------------------------
// POSIX
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
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
#include <semaphore.h>

// dll
#include <dlfcn.h>

// socket
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// system
#include <sys/resource.h>
//-------------------------------------------------------------------------------------------------
