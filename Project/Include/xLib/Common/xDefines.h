/**
 * \file  xDefines.h
 * \brief predefined macros
 */


#ifndef xLib_Common_xDefinesH
#define xLib_Common_xDefinesH
//----------------------------------------------------------------------------------------------------
#include <stdlib.h>         // compilres
#include <limits.h>         // standard C libraries
//----------------------------------------------------------------------------------------------------
// xLib info
#define xLIB_VERSION xT("1.0.000")
    ///< xLib version
#define xLIB_AUTHOR  xT("Skynowa")
    ///< xLib author
#define xLIB_DATE    xDATETIME
    ///< xLib build datetime stamp

//--------------------------------------------------
// OS family
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define xOS_WIN 1
        ///< operating system Windows
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define xOS_LINUX 1
        ///< operating system Linux
#elif defined(__FreeBSD__)
    #define xOS_FREEBSD 1
        ///< operating system FreeBSD
#else
    #error xLib: unsupported OS
#endif

//--------------------------------------------------
// OS environment
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define xOS_ENV_WIN 1
#elif defined(__unix__) || defined(__unix)
    #define xOS_ENV_UNIX 1
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
    #define xOS_ENV_BSD 1
#else
    #error xLib: unsupported OS environment
#endif

//--------------------------------------------------
// OS version
#define xOS_WIN_VER     WINVER      ///< Windows version

#define xOS_WIN_NT4     0x0400      ///< Windows NT 4.0
#define xOS_WIN_2K      0x0500      ///< Windows 2000
#define xOS_WIN_XP      0x0501      ///< Windows Server 2003, Windows XP
#define xOS_WIN_S03     0x0502      ///< Windows Server 2003 with SP1, Windows XP with SP2
#define xOS_WIN_VISTA   0x0600      ///< Windows Vista, Windows Server 2008
#define xOS_WIN_7       0x0601      ///< Windows 7, Windows Server 2008 R2

#define xOS_LINUX_VER   0           ///< Linux version

#define xOS_FREEBSD_VER __FreeBSD__ ///< FreeBSD version

//--------------------------------------------------
// OS architecture
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__i386) || defined(_M_IX86) || \
    defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__I86__) || defined(__INTEL__)

    #define xCPU_32BIT 1
        ///< architecture 32-bit
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(__ia64__) || \
      defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64 )

    #define xCPU_64BIT 1
        ///< architecture 64-bit
#else
    #error xLib: unsupported architectures
#endif
//--------------------------------------------------
// compiler types
#if   defined(__MINGW32__) || defined(__MINGW64__)
    #define xCOMPILER_MINGW32  1
        ///< compiler MinGW
#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)
    #define xCOMPILER_MS       1
        ///< compiler Microsoft Visual C++
#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define xCOMPILER_CODEGEAR 1
        ///< compiler Borland C++, Code Gear
#elif defined(__GNUC__)
    #define xCOMPILER_GNUC     1
        ///< compiler GNU C/C++
#else
    #error xLib: unsupported compiler
#endif

//--------------------------------------------------
// compiler version
#define xCOMPILER_MINGW32_VER_MAJOR   __MINGW32_MAJOR_VERSION
#define xCOMPILER_MINGW32_VER_MINOR   __MINGW32_MINOR_VERSION
#define xCOMPILER_MINGW64_VER_MAJOR   __MINGW64_VERSION_MAJOR    //defined if <stdlib.h> is included
#define xCOMPILER_MINGW64_VER_MINOR   __MINGW64_VERSION_MINOR

#define xCOMPILER_MS_VER              _MSC_VER

#define xCOMPILER_CODEGEAR_VER        __CODEGEARC__

#define xCOMPILER_GNUC_VER_MAJOR      __GNUC__
#define xCOMPILER_GNUC_VER_MINOR      __GNUC_MINOR__
#define xCOMPILER_GNUC_VER_PATCHLEVEL __GNUC_PATCHLEVEL__

//--------------------------------------------------
// standard C libraries
#if   xOS_ENV_WIN
    //TODO: standard C libraries
    #if   xCOMPILER_MINGW32
        #include <bits/c++config.h> // standard C++ libraries
    #endif

    #if defined(__MSVCRT__)
        #define xSTD_LIBC_MSVCRT 1
            ///< Microsoft CRT
    #endif
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        //TODO: standard C libraries
    #else
        #include <features.h>   // standard C libraries
    #endif

    #include <bits/c++config.h>    // standard C++ libraries
#endif

#if   xOS_ENV_WIN
    #if defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP 1
            ///< GNU libstdc++
    #endif
#elif xOS_ENV_UNIX
    #if   defined(__GNU_LIBRARY__) || defined(__GLIBC__)
        #define xSTD_LIBC_GNU    1
            ///< GNU glibc
    #elif defined(__UCLIBC__)
        #define xSTD_LIBC_UC     1
            ///< uClibc
    #elif defined(__CRTL_VER)
        #define xSTD_LIBC_VMS    1
            ///< VMS libc
    #elif defined(__LIBREL__) || defined(__TARGET_LIB__)
        #define xSTD_LIBC_ZOS    1
            ///< z/OS libc
    #else
        //#warning xLib: unsupported standard C library
    #endif
#endif

//--------------------------------------------------
//TODO: standard C libraries versions
#define xSTD_LIBC_GNU_VER_MAJOR __GLIBC__
#define xSTD_LIBC_GNU_VER_MINOR __GLIBC_MINOR__

#define xSTD_LIBC_UC_VER        0
#define xSTD_LIBC_VMS_VER       0
#define xSTD_LIBC_ZOS_VER       0

//--------------------------------------------------
// standard C++ libraries
#if   xOS_ENV_WIN
    #if   defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP  1
    #endif
#elif xOS_ENV_UNIX
    #if   defined(__CPPLIB_VER)
        #define XSTD_LIBCPP_DINKUMWARE 1
            ///< Dinkumware
    #elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
        #define xSTD_LIBCPP_GNUSTDCPP  1
            ///< GNU libstdc++
    #elif defined(__INTEL_CXXLIB_ICC)
        #define xSTD_LIBCPP_INTEL      1
            ///< Intel C++ Run-Time Libraries
    #elif defined(_LIBCPP_VERSION) || defined(_LIBCPP_ABI_VERSION)
        #define xSTD_LIBCPP_LIBCPP     1
            ///< libc++
    #else
        #warning xLib: unsupported standard C++ library
    #endif
#endif

//--------------------------------------------------
//TODO: standard C++ libraries versions
#define xSTD_LIBCPP_GNU_VER 0
#define xSTD_LIBCPP_UC_VER  0
#define xSTD_LIBCPP_VMS_VER 0
#define xSTD_LIBCPP_ZOS_VER 0

//--------------------------------------------------
// unicode, ansi
#if defined(UNICODE) || defined(_UNICODE)
    #define xUNICODE 1
        ///< unicode
#else
    #define xANSI    1
        ///< ansi
#endif

//--------------------------------------------------
// debug, release build
#if defined(NDEBUG)
    #define xBUILD_RELEASE 1
        ///< release build
#else
    #define xBUILD_DEBUG   1
        ///< debug build
#endif


/****************************************************************************
*   macroses
*
*****************************************************************************/

//// #include <xLib/Common/xCommon.h>
#include <stdarg.h>

//--------------------------------------------------
// lexema utils
#define xLEX_TO_STR(a)              (#a)
    ///< make as string
#define xLEX_CAT(a, b)              (a##b)
    ///< concatinate strings

//--------------------------------------------------
// xTEXT, xT
#if xUNICODE
    #define xTEXT(x)               L##x
    #define xT(x)                  xTEXT(x)
#else
    #define xTEXT(x)               x
    #define xT(x)                  xTEXT(x)
#endif

//--------------------------------------------------
// xTEST_PRIVATE_DATA
#if xTEST_PRIVATE_DATA
    #define private                 public
    #define protected               public
#endif
    ///< for testing private class data

//--------------------------------------------------
// xFORCE_INLINE
#if   xCOMPILER_MINGW32
    #define xFORCE_INLINE           __attribute__((__always_inline__)) inline
#elif xCOMPILER_MS
    #define xFORCE_INLINE           __forceinline
#elif xCOMPILER_GNUC
    #define xFORCE_INLINE           __attribute__((__always_inline__)) inline
#else
    #define xFORCE_INLINE           inline
#endif
    ///< keyword "inline"

//--------------------------------------------------
// xSTDCALL
#if   xOS_ENV_WIN
    #define xSTDCALL                __stdcall
#elif xOS_ENV_UNIX
    #define xSTDCALL
#endif
    ///< calling convention

//--------------------------------------------------
// namespace
#define xNAMESPACE_BEGIN(n)         namespace n {
            ///< begin namespace
#define xNAMESPACE_END(n)           }
            ///< end namespace

#define xNAMESPACE_ANONYM_BEGIN     namespace {
            ///< begin anonymous namespace
#define xNAMESPACE_ANONYM_END       }
            ///< end anonymous namespace

//--------------------------------------------------
// converters
#define xS2US(s)                    std::ustring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::tstring_t to std::ustring_t
#define xUS2S(us)                   std::tstring_t( (us).begin(), (us).begin() + (us).size() )
    ///< convert std::ustring_t to std::tstring_t
#define xS2TS(s)                    std::tstring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::string to std::tstring_t
#define xTS2S(ts)                   std::string( (ts).begin(), (ts).begin() + (ts).size() )
    ///< convert std::tstring_t to std::string

//--------------------------------------------------
// utils
#define xPTR_DELETE(p)              { CxUtils::ptrDeleteT(p); }
    ///< delete object by pointer
#define xARRAY_DELETE(p)            { CxUtils::arrayDeleteT(p); }
    ///< delete array by pointer
#define xARRAY_SIZE(a)              ( CxUtils::arraySizeT(a) )
    ///< get array size
#define xARRAY_SIZE2(a)             ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
#define xBUFF_ZERO(Buff)            { std::memset(static_cast<void *>( &(Buff)[0] ), 0, sizeof(Buff)); }
    ///< zero buffer memory
#define xSTRUCT_ZERO(Buff)          { std::memset(static_cast<void *>( &(Buff) ),    0, sizeof(Buff)); }
    ///< zero struct memory
#define xBUFF_FREE(pvBuff)          { if (NULL != (pvBuff)) { std::free(pvBuff); (pvBuff) = NULL; }    }
    ///< free buffer memory
#define xFCLOSE(f)                  { if (NULL != (f)) { std::fclose(f); (f) = NULL; } }
    ///< close file stream (FILE *)
#define xRELEASE(p)                 { if (NULL != (p)) {(p)->Release(); (p) = NULL; } }
    ///< release object
#define xMAX(a, b)                  ( CxUtils::maxT( (a), (b) ) )
    ///< get max value
#define xMIN(a, b)                  ( CxUtils::minT( (a), (b) ) )
    ///< get min value
#define xINT_TO_BOOL(expr)          ( (0 == (expr)) ? false : true )
    ///< convert int to bool

//--------------------------------------------------
// xUNUSED
#if   xCOMPILER_MINGW32 || xCOMPILER_MS
    #define xUNUSED(arg)            ( static_cast<void>( arg ) )
#elif xCOMPILER_CODEGEAR
    #define xUNUSED(arg)            ( static_cast<void>( arg ) )
#elif xCOMPILER_GNUC
    #define xUNUSED(arg)            { static_cast<void>( (arg) = ((true) ? (arg) : (arg)) ); }
#else
    #define xUNUSED(arg)            ( static_cast<void>( arg ) )
#endif
    /// < hide "unused variable" warnings

//--------------------------------------------------
// xENUM_INC, xENUM_DEC
#define xENUM_INC(type, obj)        { (obj) = static_cast<type>( static_cast<int>( obj ) + 1 ); }
    ///< increment enumerator
#define xENUM_DEC(type, obj)        { (obj) = static_cast<type>( static_cast<int>( obj ) - 1 ); }
    ///< decriment enumerator

//--------------------------------------------------
// temporary enable/disable code
#define xTEMP_ENABLED               1
    ///< temporary code enabled
#define xTEMP_DISABLED              0
    ///< temporary code disable
#define xDEPRECIATE                 0
    ///< temporary code depreciate
#define xTODO                       0
    ///< todo code
#define xCAN_REMOVE                 0
    ///< can remove code
#define xTEST_IGNORE                0
    ///< ignore test code
#define xREVIEW                     1
    ///< code for review
#define xCOMMENT                    0
    ///< comment for code
#define xDEBUG_VAR_NA(var)          ;
    ///< at this point debug code for variable is not applicable
#define xDEBUG_VARS_NA              ;
    ///< at this point debug code for variables is not applicable
#define xNA                         ;
    ///< at this point the code is not applicable

//--------------------------------------------------
// buildin macroses

// xFILE
#if defined(__FILE__)
    #define xFILE                   xT(__FILE__)
#else
    #define xFILE                   xT("<unknown xFILE>")
#endif
    ///< source file path


// xLINE
#if defined(__LINE__)
    #define xLINE                   __LINE__
#else
    #define xLINE                   0UL
#endif
    ///< source code line number


// xFUNCTION
#if   xCOMPILER_MS
    #define xFUNCTION               xT(__FUNCTION__)
#elif xCOMPILER_CODEGEAR
    #define xFUNCTION               xT(__FUNC__)
#elif xCOMPILER_GNUC || xCOMPILER_MINGW32
    #define xFUNCTION               xT(__PRETTY_FUNCTION__)
#else
    #define xFUNCTION               xT("<unknown xFUNCTION>")
#endif
    ///< source function name


// xDATE
#if defined(__DATE__)
    #define xDATE                   xT(__DATE__)
#else
    #define xDATE                   xT("<unknown xDATE>")
#endif
    ///< build source date stamp


// xTIME
#if defined(__TIME__)
    #define xTIME                   xT(__TIME__)
#else
    #define xTIME                   xT("<unknown xTIME>")
#endif
    ///< build source time stamp


// xDATETIME
#if defined(__DATE__) && defined(__TIME__)
    #define xDATETIME               xT(__DATE__) xT(" ") xT(__TIME__)
#else
    #define xDATETIME               xT("<unknown xDATETIME>")
#endif
    ///< build source datetime stamp


// xCOUNTER
#if defined(__COUNTER__)
    #define xCOUNTER                __COUNTER__
#else
    #define xCOUNTER                0UL
#endif
    ///< Expands to an integer starting with 0 and incrementing by 1 every time it is used in a compiland

//--------------------------------------------------
// function params
#define xIN
    ///< incoming param
#define xOUT
    ///< outcoming param
#define xIN_OUT
    ///< incoming and outcoming param

//--------------------------------------------------
// xHOST_NAME_MAX
#if   xOS_ENV_WIN
    #if defined(MAX_COMPUTERNAME_LENGTH)
        #define xHOST_NAME_MAX      MAX_COMPUTERNAME_LENGTH
    #else
        #define xHOST_NAME_MAX      256 // custom define
    #endif
#elif xOS_ENV_UNIX
    #if   defined(HOST_NAME_MAX)
        #define xHOST_NAME_MAX      HOST_NAME_MAX
    #elif defined(MAXHOSTNAMELEN)
        #define xHOST_NAME_MAX      MAXHOSTNAMELEN
    #else
        #define xHOST_NAME_MAX      256 //custom define
    #endif
#endif
    ///< max host name length

//--------------------------------------------------
// xPATH_MAX
#define xPATH_MAX                   ( CxPath::uiGetMaxSize() )
    ///< max path length

//--------------------------------------------------
// xNAME_MAX
#define xNAME_MAX                   ( CxPath::uiGetNameMaxSize() )
    ///< max file name length

//--------------------------------------------------
// xLINE_MAX
#if   xOS_ENV_WIN
    #define xLINE_MAX               2048 // custom define
#elif xOS_ENV_UNIX
    #if   defined(LINE_MAX)
        #define xLINE_MAX           LINE_MAX
    #elif defined(_SC_LINE_MAX)
        #define xLINE_MAX           _SC_LINE_MAX
    #else
        #error xLib: xLINE_MAX not defined
    #endif
#endif
    ///< maximum length of a utility's input line, either from standard input or from a file

//--------------------------------------------------
// xENV_MAX
#if   xOS_ENV_WIN
    #if   xCOMPILER_MS
        #define xENV_MAX            _MAX_ENV
    #else
        #define xENV_MAX            32767 // custom define
    #endif
#elif xOS_ENV_UNIX
    #define xENV_MAX                32767 // custom define
#endif
    ///< maximum permissible string length of an environmental variable

//--------------------------------------------------
// xFRAMES_MAX
#if   xOS_ENV_WIN
    #define xSTACK_TRACE_FRAMES_MAX 62UL    // from MSDN, ::CaptureStackBackTrace
#elif xOS_ENV_UNIX
    #define xSTACK_TRACE_FRAMES_MAX 256     // custom define, this should be enough
#endif
    ///< maximum frames for stack trace

//--------------------------------------------------
// xSEMAPHORE_VALUE_MAX
#if   xOS_ENV_WIN
    #define xSEMAPHORE_VALUE_MAX    ( (std::numeric_limits<LONG>::max)() )    // LONG, custom define (tested on Win7 x64)
#elif xOS_ENV_UNIX
    #define xSEMAPHORE_VALUE_MAX    (SEM_VALUE_MAX)                         // int
#endif
    ///< semaphore maximum value

//--------------------------------------------------
// var args
#if defined(va_start)
    #define xVA_START(val, fmt)     ( va_start(val, fmt) )
        ///< initializes ap for subsequent use by xVA_ARG() and xVA_END(), and must be called first
#endif

#if defined(va_copy)
    #define xVA_COPY(dest, src)     ( va_copy(dest, src) )
#elif defined(__va_copy)
    #define xVA_COPY(dest, src)     ( __va_copy(dest, src) )
#else
    #define xVA_COPY(dest, src)     ( (void)std::memcpy(&dest, &src, sizeof(va_list)) )
#endif
    ///< copy xVA_LIST

#if defined(va_end)
    #define xVA_END(val)            ( va_end(val) )
        ///< Each invocation of xVA_START() must be matched by a corresponding invocation of xVA_END() in the same function
#endif

//--------------------------------------------------
// qualifiers
#if   xOS_ENV_WIN
    #ifdef xCPU_64BIT
        #define xPR_SIZET           xT("I")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("I64d")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("I64u")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x            xT("I64x")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("I64X")
            ///< qualifier for long_t long_t int (hex)
    #else
        #define xPR_SIZET           xT("u")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("llu")
            ///< qualifier for unsigned long_t long_t in
        #define xPR_I64x            xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #endif
#elif xOS_ENV_UNIX
    #ifdef xCPU_64BIT
        #define xPR_SIZET           xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("llu")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x            xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #else
        #define xPR_SIZET           xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("llu")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x            xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #endif
#endif
    ///< qualifiers

//--------------------------------------------------
// xTIMEOUT_INFINITE
#if   xOS_ENV_WIN
    #define xTIMEOUT_INFINITE       INFINITE
#elif xOS_ENV_UNIX
    #define xTIMEOUT_INFINITE       ( ~(0UL) )
#endif
    ///< infinite timeout

//--------------------------------------------------
// xPAGE_SIZE
#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
    #if   defined(_SC_PAGESIZE)
        #define xPAGE_SIZE          _SC_PAGESIZE
    #elif defined(_SC_PAGE_SIZE)
        #define xPAGE_SIZE          _SC_PAGE_SIZE
    #else
        #error xLib: xPAGE_SIZE not defined
    #endif
#endif
    ///< filesystem page size

//--------------------------------------------------
// xSTATVFS (struct and function)
#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        #define xSTATVFS            statvfs
        #define xSTATVFS_F_FRSIZE   f_frsize
    #else
        #define xSTATVFS            statfs64
        #define xSTATVFS_F_FRSIZE   f_bsize
    #endif
#endif
    ///< filesystem statfs (struct and function)


// xDIR_TEMP temprory directory
#if   xOS_ENV_WIN
    #if defined(P_tmpdir)
        #define xDIR_TEMP           xT(P_tmpdir)
    #else
        #define xDIR_TEMP           xT("C:\\Temp")  // custom define
    #endif
#elif xOS_ENV_UNIX
    #if defined(P_tmpdir)
        #define xDIR_TEMP           xT(P_tmpdir)
    #else
        #define xDIR_TEMP           xT("/tmp")      // custom define
    #endif
#endif
    ///< temprory directory

//--------------------------------------------------
// xNATIVE_HANDLE_NULL, xNATIVE_HANDLE_INVALID
#if   xOS_ENV_WIN
    #define xNATIVE_HANDLE_NULL     ( static_cast<native_handle_t>( NULL ) )                  ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID  ( static_cast<native_handle_t>( INVALID_HANDLE_VALUE ) )  ///< native handle value "invalid"
#elif xOS_ENV_UNIX
    #define xNATIVE_HANDLE_NULL     ( static_cast<native_handle_t>( 0 ) )                     ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID  ( static_cast<native_handle_t>( - 1 ) )                   ///< native handle value "invalid"
#endif

//--------------------------------------------------
// xFOREACH
#define xFOREACH(it_t, it, cont)  \
                                    for (it_t::iterator               it((cont).begin());  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::iterator)

#define xFOREACH_CONST(it_t, it, cont) \
                                    for (it_t::const_iterator         it((cont).begin());  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::const_iterator)

#define xFOREACH_R(it_t, it, cont)  \
                                    for (it_t::reverse_iterator       it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::reverse_iterator)

#define xFOREACH_R_CONST(it_t, it, cont)  \
                                    for (it_t::const_reverse_iterator it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::const_reverse_iterator)

//--------------------------------------------------
// other

//----------------------------------------------------------------------------------------------------
#endif  //xLib_Common_xDefinesH
