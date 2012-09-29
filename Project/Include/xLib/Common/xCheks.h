/**
 * \file  xCheks.h
 * \brief cheks for xLib
 */


#ifndef xLib_Common_xCheksH
#define xLib_Common_xCheksH
//---------------------------------------------------------------------------
//check for C++ compilation
#if !defined(__cplusplus)
    #error xLib: require C++ compilation (use a .cpp suffix)
#endif

//check for supporting unicode
#if xOS_ENV_UNIX
    #if xUNICODE
        #error xLib: unicode unsupported for Linux and FreeBSD
    #endif

    #if !defined(P_tmpdir)
        #error xLib: P_tmpdir not defined
    #endif
#endif

//TODO: for debug mode

//--------------------------------------------------
//Linux
#if xOS_ENV_UNIX

#endif

//--------------------------------------------------
//Win
#if   xOS_ENV_WIN
    #if !defined(MAX_PATH)
        #error xLib: MAX_PATH not defined
    #endif

    #if !defined(FILENAME_MAX)
        #error xLib: FILENAME_MAX not defined
    #endif
#endif

//---------------------------------------------------------------------------
#endif  //xLib_Common_xCheksH
