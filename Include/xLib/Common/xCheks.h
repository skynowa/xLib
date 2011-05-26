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
#if defined(xUNICODE) && (defined(xOS_LINUX) || defined(xOS_FREEBSD))
    #error xLib: unicode unsupported for Linux and FreeBSD
#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xCheksH
