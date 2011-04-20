/****************************************************************************
* Class name:  xCommon_Linux.h
* Description: Linux common header for xLib
* File name:   xCommon_Linux.h.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.12.2010 23:26:11
*
*****************************************************************************/


//----------------------------------------------------------------------------------------------------
#ifndef xLib_Common_Linux_xCommon_LinuxH
#define xLib_Common_Linux_xCommon_LinuxH
//----------------------------------------------------------------------------------------------------
//xLib
#include <xLib/Common/CxMacros.h>

//POSIX
#include <cpio.h>           //Magic numbers for the cpio archive format.
#include <dirent.h>         //Allows the opening and listing of directories.
#include <fcntl.h>          //File opening, locking and other operations.
#include <grp.h>            //User group information and control.
#include <pthread.h>        //Defines an API for creating and manipulating POSIX threads.
#include <pwd.h>            //passwd (user information) access and control.
#include <sys/ipc.h>        //Inter-process communication (IPC).
#include <sys/msg.h>        //POSIX message queues.
#include <sys/sem.h>        //POSIX semaphores.
#include <sys/stat.h>       //File information (stat et al.).
#include <sys/time.h>       //Time and date functions and structures.
#include <sys/types.h>      //Various data types used elsewhere.
#include <sys/utsname.h>    //uname and related structures.
#include <sys/wait.h>       //Status of terminated child processes (see wait)
#include <sys/uio.h>
#include <tar.h>            //Magic numbers for the tar archive format.
#include <termios.h>        //Allows terminal I/O interfaces.
#include <unistd.h>         //Various essential POSIX functions and constants.
#include <utime.h>          //inode access and modification times.

//socket
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

////#define _POSIX_SOURCE 1

#if !defined(BOOL)
    typedef enum { FALSE = 0, TRUE = 1 } BOOL;
#endif

    typedef void                   VOID;
    typedef void *                 LPVOID;

    typedef int                    INT;
    typedef short int              SHORT;
    typedef long int               LONG;
    typedef long long int          LONGLONG;

    typedef unsigned int           UINT;
    typedef unsigned short int     USHORT;
    typedef unsigned long int      ULONG;
    typedef unsigned long long int ULONGLONG;

    typedef float                  FLOAT;
    typedef double                 DOUBLE;

    typedef char                   CHAR;
    typedef unsigned char          UCHAR;

//---------------------------------------------------------------------------
#if defined(UNICODE) || defined(_UNICODE)
    #error xLib: unicode unsupported for Linux

    //UNICODE
    #define _tmain      wmain
    #define _ftprintf   fwprintf
    #define _tasctime   _wasctime
    #define _tfopen     _wfopen
    #define _tsetlocale _wsetlocale
    #define _vsntprintf _vsnwprintf
    #define _tfreopen   _wfreopen
    #define _tperror    _wperror
    #define _vstprintf  _vswprintf
    #define _vtprintf   vwprintf
    #define _vftprintf  vfwprintf
    #define _gettc      getwc
    #define _putts      _putws
    #define _puttchar   putwchar
    #define _taccess    _waccess
    #define _getts      _getws
    #define _gettchar   getwchar
    #define _tsystem    _wsystem
    #define _ttmpnam    _wtmpnam
    #define _tmkstemp   mkstemp         //TODO: need unicode version
    #define _trename    _wrename
    #define _tunlink    _wunlink
    #define _tremove    _wremove
    #define _fputts     fputws
    #define _ungettc    ungetwc
    #define _fputtc     fputwc
    #define _fgetts     fgetws
    #define _tcslen     wcslen
    #define _tchmod     _wchmod

    #define _itot       _itow
    #define _ltot       _ltow
    #define _ultot      _ultow
    #define _i64tot     _i64toa
    #define _ui64tot    _ui64tow

    #define _totlower   towlower
    #define _totupper   towupper

    typedef addrinfo    ADDRINFOT;
#else
    //ANSI
    #define _tmain      main
    #define _ftprintf   fprintf
    #define _tasctime   asctime
    #define _tfopen     fopen
    #define _tsetlocale setlocale
    #define _vsntprintf vsnprintf   //_vsnprintf
    #define _tfreopen   freopen
    #define _tperror    perror
    #define _vstprintf  vsprintf
    #define _vtprintf   vprintf
    #define _vftprintf  vfprintf
    #define _gettc      getc
    #define _putts      puts
    #define _puttchar   putchar
    #define _taccess    access
    #define _getts      gets
    #define _gettchar   getchar
    #define _tsystem    system
    #define _ttmpnam    tmpnam
    #define _tmkstemp   mkstemp
    #define _trename    rename
    #define _tunlink    unlink
    #define _tremove    remove
    #define _fputts     fputs
    #define _ungettc    ungetc
    #define _fputtc     fputc
    #define _fgetts     fgets
    #define _tcslen     strlen
    #define _tchmod     chmod

//    #define _itot       itoa
//    #define _ltot       ltoa
//    #define _ultot      ultoa
//    #define _i64tot     _i64tow
//    #define _ui64tot    _ui64toa

    #define _totlower   tolower
    #define _totupper   toupper

    typedef addrinfo    ADDRINFOT;
#endif  /*_UNICODE*/
//----------------------------------------------------------------------------------------------------
#endif /*xLib_Common_Linux_xCommon_LinuxH*/
//----------------------------------------------------------------------------------------------------
