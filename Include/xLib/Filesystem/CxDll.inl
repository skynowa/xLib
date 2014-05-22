/**
 * \file  CxDll.inl
 * \brief dynamic linking loader
 */


#if   xENV_WIN
    #include "Platform/Win/CxDll.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxDll.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxDll.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxDll.inl"
    #endif
#endif
