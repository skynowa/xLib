/**
 * \file   xFunctions.inl
 * \brief  function macroses
 */


#if   xENV_WIN
    #include "Platform/Win/xFunctions_win.h"
#elif xENV_UNIX
    // #include "Platform/Unix/xFunctions_unix.h"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/xFunctions_android.inl"
        #elif xOS_LINUX
            // #include "Platform/Linux/xFunctions_linux.h"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/xFunctions_bsd.h"
    #elif xENV_APPLE
        #include "Platform/Apple/xFunctions_apple.h"
    #endif
#endif
