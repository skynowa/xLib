/**
 * \file  DirTemp.cpp
 * \brief DirTemp
 */


#include "DirTemp.h"

#if   xENV_WIN
    #include "Platform/Win/DirTemp_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/DirTemp_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/DirTemp_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/DirTemp_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Apple/DirTemp_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
DirTemp::DirTemp()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
DirTemp::~DirTemp()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
