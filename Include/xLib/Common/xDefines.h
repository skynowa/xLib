/**
 * \file  xDefines.h
 * \brief predefined macros
 */


#ifndef xLib_Common_xDefinesH
#define xLib_Common_xDefinesH
//---------------------------------------------------------------------------
// xLib info
#define xLIB_VERSION xT("1.0.000")
    ///< xLib version
#define xLIB_AUTHOR  xT("Skynowa")
    ///< xLib author
#define xLIB_DATE    xDATETIME
    ///< xLib build datetime stamp


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


// OS version
#define xOS_WIN_VER     WINVER
#define xOS_LINUX_VER   0
#define xOS_FREEBSD_VER __FreeBSD__

//---------------------------------------------------------------------------
// OS architecture
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__i386) || defined(_M_IX86) || \
    defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__I86__) || defined(__INTEL__)

    #define xARCHITECTURE_32BIT 1
        ///< architecture 32-bit
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(__ia64__) || \
      defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64 )

    #define xARCHITECTURE_64BIT 1
        ///< architecture 64-bit
#else
    #error xLib: unsupported architectures
#endif
//---------------------------------------------------------------------------
// compiler types
#if   defined(__MINGW32__)
    #define xCOMPILER_MINGW32 1
        ///< compiler MinGW
#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICL)
    #define xCOMPILER_INTEL 1
        ///< compiler Intel C/C++
#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)
    #define xCOMPILER_MS 1
        ///< compiler Microsoft Visual C++
#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define xCOMPILER_CODEGEAR 1
        ///< compiler Borland C++, Code Gear
#elif defined(__GNUC__)
    #define xCOMPILER_GNUC 1
        ///< compiler GNU C/C++
#else
    #error xLib: unsupported compiler
#endif

// compiler version
#define xCOMPILER_MINGW32_MAJOR_VER __MINGW32_MAJOR_VERSION
#define xCOMPILER_MINGW32_MINOR_VER __MINGW32_MINOR_VERSION

#define xCOMPILER_INTEL_VER         __INTEL_COMPILER
#define xCOMPILER_MS_VER            _MSC_VER
#define xCOMPILER_CODEGEAR_VER      __CODEGEARC__
#define xCOMPILER_GNUC_VER          __GNUC_VERSION__
//---------------------------------------------------------------------------
// unicode, ansi
#if defined(UNICODE) || defined(_UNICODE)
    #define xUNICODE 1
        ///< unicode
#else
    #define xANSI 1
        ///< ansi
#endif
//---------------------------------------------------------------------------
// debug, release build
#if defined(NDEBUG)
    #define xBUILD_RELEASE 1
        ///< release build
#else
    #define xBUILD_DEBUG 1
        ///< debug build
#endif

//--------------------------------------------------
//TODO: library types


//---------------------------------------------------------------------------
#endif  //xLib_Common_xDefinesH
