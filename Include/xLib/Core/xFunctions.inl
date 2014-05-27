/**
 * \file   xFunctions.inl
 * \brief  function macroses
 */


#if   xENV_WIN
    #include "Platform/Win/xFunctions_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        // n/a
    #elif xENV_BSD
        #include "Platform/Unix/xFunctions_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/xFunctions_bsd.inl"
    #endif
#endif
