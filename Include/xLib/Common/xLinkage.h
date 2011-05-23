/****************************************************************************
* Class name:  xLinkage
* Description: linkage static library
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     02.12.2010 11:47:23
*
*****************************************************************************/


#ifndef xLib_Common_xLinkageH
#define xLib_Common_xLinkageH
//---------------------------------------------------------------------------
#if defined(xIS_AUTO_LINCKAGE) && defined(xOS_WIN) && defined(xCOMPILER_MS) && !defined(_LIB)
    #if defined(NDEBUG)
        //release
        #if defined(xUNICODE)
            ////#pragma message("  --- xLib: unicode, release ---")
            #pragma comment(lib, "xLibW_Release.lib")
        #else
            ////#pragma message("  --- xLib: ansi, release ---")
            #pragma comment(lib, "xLibA_Release.lib")
        #endif
    #else
        //debug
        #if defined(xUNICODE)
            ////#pragma message("  --- xLib: unicode, debug ---")
            #pragma comment(lib, "xLibW_Debug.lib")
        #else
            ////#pragma message("  --- xLib: ansi, debug ---")
            #pragma comment(lib, "xLibA_Debug.lib")
        #endif
    #endif
#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_xLinkageH





/*
#if !defined( __libPerstStat_link_h__ )
#define __libPerstStat_link_h__

#if defined (_MSC_VER) && !defined (_LIB)

#if !defined( __ProjectRootDirectory__ )
  #include <@host.h>
#endif  // __ProjectRootDirectory__

#if _MSC_VER >= 1100

#ifdef _DEBUG
#   if defined( _DLL )
#     pragma message ("Using library: " __ProjectRootDirectory__ "lib/libPerstStat_dmd.lib")
#     pragma comment(lib, __ProjectRootDirectory__ "lib/libPerstStat_dmd.lib")
#   elif defined( _MT )
#     pragma message ("Using library: " __ProjectRootDirectory__ "lib/libPerstStat_smd.lib")
#     pragma comment(lib, __ProjectRootDirectory__ "lib/libPerstStat_smd.lib")
#   else
#     pragma message ("Using library: " __ProjectRootDirectory__ "lib/libPerstStat_ssd.lib")
#     pragma comment(lib, __ProjectRootDirectory__ "lib/libPerstStat_ssd.lib")
#   endif
#else
#   if defined( _DLL )
#     pragma message ("Using library: " __ProjectRootDirectory__ "lib/libPerstStat_dmr.lib")
#     pragma comment(lib, __ProjectRootDirectory__ "lib/libPerstStat_dmr.lib")
#   elif defined( _MT )
#     pragma message ("Using library: " __ProjectRootDirectory__ "lib/libPerstStat_smr.lib")
#     pragma comment(lib, __ProjectRootDirectory__ "lib/libPerstStat_smr.lib")
#   else
#     pragma message ("Using library: " __ProjectRootDirectory__ "lib/libPerstStat_ssr.lib")
#     pragma comment(lib, __ProjectRootDirectory__ "lib/libPerstStat_ssr.lib")
#   endif
#endif

#else  // _MSC_VER < 1100

#  pragma message ( "VC 5.0 libraries only supported")

#endif    // _MSC_VER >= 1100

#endif    //  _MSC_VER

#endif  // __libPerstStat_link_h__
*/
