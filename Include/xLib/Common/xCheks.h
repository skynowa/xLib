/****************************************************************************
* Class name:  xCheks
* Description: cheks for xLib
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.05.2011
*
*****************************************************************************/


#ifndef xLib_Common_xCheksH
#define xLib_Common_xCheksH
//---------------------------------------------------------------------------
//check for C++ compilation
#if !defined(__cplusplus)
    #error xLib: require C++ compilation (use a .cpp suffix)
#endif

//check for supporting unicode
#if defined(xOS_LINUX)
    #if defined(xUNICODE)
        #error xLib: unicode unsupported for Linux and FreeBSD
    #endif

    #if !defined(P_tmpdir)
        #error xLib: P_tmpdir not defined
    #endif
#endif

//TODO: for debug mode

//--------------------------------------------------
//Linux
#if defined(xOS_LINUX)

#endif

//--------------------------------------------------
//Win
#if defined(xOS_WIN)
    #if !defined(MAX_PATH)
        #error xLib: MAX_PATH not defined
    #endif

    #if !defined(FILENAME_MAX)
        #error xLib: FILENAME_MAX not defined
    #endif
#endif

//---------------------------------------------------------------------------
#endif  //xLib_Common_xCheksH
