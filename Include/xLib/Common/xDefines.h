/****************************************************************************
* Class name:  xDefines
* Description: predefined macros
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     20.05.2011
*
*****************************************************************************/


#ifndef xLib_Common_xDefinesH
#define xLib_Common_xDefinesH
//---------------------------------------------------------------------------
//DONE: OS family (http://predef.sourceforge.net/preos.html)
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define xOS_WIN
    //#pragma message("  --- xLib: xOS_WIN ---")
#elif defined(linux) || defined(__linux)
    #define xOS_LINUX
    //#pragma message("  --- xLib: xOS_LINUX ---")
#elif defined(__FreeBSD__)
    #define xOS_FREEBSD
    //#pragma message("  --- xLib: xOS_FREEBSD ---")
    #error xLib: xOS_FREEBSD
#else
    #error xLib: unsupported OS
#endif
//---------------------------------------------------------------------------
//DONE: OS architecture (http://predef.sourceforge.net/preos.html)
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__i386) || defined(_M_IX86) || \
    defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__I86__) || defined(__INTEL__)

    #define xARCHITECTURE_32BIT
    //#pragma message("  --- xLib: xARCHITECTURE_32BIT ---")
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(__ia64__) || \
      defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64 )

    #define xARCHITECTURE_64BIT
    //#pragma message("  --- xLib: xARCHITECTURE_64BIT ---")
#else
    #error xLib: unsupported architectures
#endif
//---------------------------------------------------------------------------
//DONE: Compilers
#if   defined(__MINGW32__)
    #define xCOMPILER_MINGW32
    //#pragma message("  --- xLib: xCOMPILER_MINGW32 ---")
#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)
    #define xCOMPILER_MS
    //#pragma message("  --- xLib: xCOMPILER_MS ---")
#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define xCOMPILER_CODEGEAR
    //#pragma message("  --- xLib: xCOMPILER_CODEGEAR ---")
#elif defined(__GNUC__)
    #define xCOMPILER_GNUC
    //#pragma message("  --- xLib: xCOMPILER_GNUC ---")
#else
    #error xLib: unsupported compiler
#endif
//---------------------------------------------------------------------------
//DONE: unicode, ansi
#if defined(UNICODE) || defined(_UNICODE)
    #define xUNICODE
    //#pragma message("  --- xLib: xUNICODE ---")
#else
    #define xANSI
    //#pragma message("  --- xLib: xANSI ---")
#endif

//---------------------------------------------------------------------------
//DONE: inline
#if !defined(xCOMPILER_MS)
    #define __forceinline  inline
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xDefinesH
