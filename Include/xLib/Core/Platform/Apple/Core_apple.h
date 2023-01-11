/**
 * \file  Core_apple.h
 * \brief Apple core header for xLib
 */


#pragma once

#include <sys/mount.h>
#include <sys/statvfs.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/user.h> // for struct kinfo_proc

// POSIX
#include <cpio.h>
#include <tar.h>
#include <sys/msg.h>

// Fs
#include <mach-o/dyld.h> // _NSGetExecutablePath
#include <sys/param.h>
#include <sys/mount.h>

// thread
#include <sys/sem.h>

// Net
#include <sys/socket.h>
#include <netdb.h>
