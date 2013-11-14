/**
 * \file  xLinking.h
 * \brief linking static library
 */


#pragma once

#ifndef xLib_xLinkingH
#define xLib_xLinkingH
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN
    #if !xLIB && xIS_AUTO_LINKING
        #if xBUILD_RELEASE
            #if xUNICODE
                #pragma comment(lib, "xLibW_Release.lib")
            #else
                #pragma comment(lib, "xLibA_Release.lib")
            #endif
        #else
            #if xUNICODE
                #pragma comment(lib, "xLibW_Debug.lib")
            #else
                #pragma comment(lib, "xLibA_Debug.lib")
            #endif
        #endif

    #endif
#else
    xNA;
#endif
//-------------------------------------------------------------------------------------------------
#endif // xLib_xLinkingH


#if xTODO
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

    #endif // _MSC_VER >= 1100

    #endif //  _MSC_VER

    #endif  // __libPerstStat_link_h__
#endif

