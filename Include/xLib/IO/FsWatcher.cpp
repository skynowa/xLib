/**
 * \file   FsWatcher.cpp
 * \brief  File system watcher
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "FsWatcher.h"
#endif

#if   xENV_WIN
    #include "Platform/Win/FsWatcher_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/FsWatcher_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Unix/FsWatcher_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Unix/FsWatcher_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/FsWatcher_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
FsWatcher::FsWatcher()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE
FsWatcher::~FsWatcher()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, io)
