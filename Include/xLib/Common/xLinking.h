/**
 * \file  xLinking.h
 * \brief linking static library
 */


#ifndef xLib_Common_xLinkingH
#define xLib_Common_xLinkingH
//---------------------------------------------------------------------------
#if xOS_ENV_WIN
    #if !defined(_LIB) && xIS_AUTO_LINKING
        #if defined(NDEBUG)
            //release
            #if defined(xUNICODE)
                #pragma comment(lib, "xLibW_Release.lib")
                //#pragma message("  --- xLib: unicode, release ---")
            #else
                #pragma comment(lib, "xLibA_Release.lib")
                //#pragma message("  --- xLib: ansi, release ---")
            #endif
        #else
            //debug
            #if defined(xUNICODE)
                #pragma comment(lib, "xLibW_Debug.lib")
                //#pragma message("  --- xLib: unicode, debug ---")
            #else
                #pragma comment(lib, "xLibA_Debug.lib")
                //#pragma message("  --- xLib: ansi, debug ---")
            #endif
        #endif
    #endif
#elif xOS_ENV_UNIX
    // n/a
#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_xLinkingH


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

    #endif    // _MSC_VER >= 1100

    #endif    //  _MSC_VER

    #endif  // __libPerstStat_link_h__
#endif

