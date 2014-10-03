/**
 * \file   [CLASS_NAME].cpp
 * \brief
 */


#if !xOPTION_HEADER_ONLY
    #include "[CLASS_NAME].h"
#endif

#if   xENV_WIN
    #include "Platform/Win/[CLASS_NAME]_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/[CLASS_NAME]_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Unix/[CLASS_NAME]_linux.inl"
    #elif xENV_BSD
        #include "Platform/Unix/[CLASS_NAME]_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/[CLASS_NAME]_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, [NAMESPACE])

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, [NAMESPACE])
