/**
 * \file  PathExe.cpp
 * \brief file system path
 *
 * http://www.cplusplus.com/forum/general/11104/
 * http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
 * http://libsylph.sourceforge.net/wiki/Full_path_to_binary
 * http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?
 *     ciid=88086d6e1de021106d6e1de02110275d6e10RCRD
 */


#include "PathExe.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Sync/Process.h>
#include <xLib/Log/Trace.h>
#include <xLib/System/User.h>


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
