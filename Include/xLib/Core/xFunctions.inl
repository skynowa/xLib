/**
 * \file   xFunctions.inl
 * \brief  function macroses
 */


#if   xENV_WIN
    #include "Platform/Win/xFunctions_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/xFunctions_unix.inl"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/xFunctions_android.inl"
        #elif xOS_LINUX
            // #include "Platform/Linux/xFunctions_linux.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/xFunctions_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/xFunctions_apple.inl"
    #endif
#endif
