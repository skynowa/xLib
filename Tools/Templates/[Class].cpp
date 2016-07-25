/**
 * \file   [Class].cpp
 * \brief  [Comments]
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "[Class].h"
#endif

#if   xENV_WIN
    #include "Platform/Win/[Class]_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/[Class]_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Unix/[Class]_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Unix/[Class]_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/[Class]_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, [XLIB_NS])

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
[Class]::[Class]()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE
[Class]::~[Class]()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, [XLIB_NS])
