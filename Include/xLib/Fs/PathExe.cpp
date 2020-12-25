/**
 * \file  PathExe.cpp
 * \brief file system path
 */


#include "PathExe.h"

#include <xLib/Fs/FileInfo.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>

#if   xENV_WIN
    #include "Platform/Win/PathExe_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/PathExe_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/PathExe_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/PathExe_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/PathExe_apple.inl"
    #endif
#endif

namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
PathExe::PathExe() :
	Path( _exe_impl() )
{
	xTEST(FileInfo( str() ).isExists());
}
//-------------------------------------------------------------------------------------------------

} // namespace
