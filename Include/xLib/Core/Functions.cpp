/**
 * \file   Functions.cpp
 * \brief  function macroses
 */


#if !xOPTION_HEADER_ONLY
    #include "Functions.h"
#endif

#if   xENV_WIN
    #include "Platform/Win/Functions_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Functions_unix.inl"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/Functions_android.inl"
        #elif xOS_LINUX
            // #include "Platform/Linux/Functions_linux.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/Functions_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/Functions_apple.inl"
    #endif
#endif
