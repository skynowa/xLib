/**
 * \file  Path.inl
 * \brief file system path
 */


#include "PathDll.h"

#include <xLib/Fs/FileInfo.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>

#if   xENV_WIN
    #include "Platform/Win/PathDll_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/PathDll_unix.inl"
#endif


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
PathDll::PathDll() :
	Path( _dll_impl() )
{
	xTEST(FileInfo( str() ).isExists());
}
//-------------------------------------------------------------------------------------------------

} // namespace
