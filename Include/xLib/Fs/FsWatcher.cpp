/**
 * \file   FsWatcher.cpp
 * \brief  File system watcher
 */


#include "FsWatcher.h"

#if   xENV_WIN
    #include "Platform/Win/FsWatcher_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Linux/FsWatcher_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/FsWatcher_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/FsWatcher_apple.inl"
    #endif
#endif

#include <xLib/Fs/File.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Sync/Thread.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FsWatcher::FsWatcher(
    std::cvec_tstring_t &a_dirPathsDisabled,
    std::ctstring_t     &a_shellFilter
) :
    _dirPathsDisabled(a_dirPathsDisabled),
    _shellFilter     (a_shellFilter)
{
}
//-------------------------------------------------------------------------------------------------
FsWatcher::~FsWatcher()
{
    close();
}
//-------------------------------------------------------------------------------------------------
bool_t
FsWatcher::open(
    std::cvec_tstring_t &a_filePaths,
    std::cmap_tstring_t &a_cmds
)
{
    // _filePaths
    for (auto &it_filePath : a_filePaths) {
        File file;
        file.create(it_filePath, File::omRead);

        if ( !file.get().isValid() ) {
            std::tcout << "[FsWatcher] Can't open: " << it_filePath << std::endl;
            continue;
        }

        _filePaths.push_back(it_filePath);
        _fileHandles.push_back( file.getNative() );

        HandleStdFile &handle = file.detach();
        xUNUSED(handle);
    }

    if ( _filePaths.empty() ) {
        return false;
    }

    // a_cmds
    _cmds = a_cmds;

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
FsWatcher::openDirs(
    std::cvec_tstring_t &a_dirPaths,
    std::cmap_tstring_t &a_cmds
)
{
    bool_t bRv = false;

    for (auto &it_dirPath : a_dirPaths) {
        std::vec_tstring_t filePaths;
        Finder::files(it_dirPath, _shellFilter, true, &filePaths);
        if ( filePaths.empty() ) {
            continue;
        }

        bRv = open(filePaths, a_cmds);
        if (!bRv) {
            continue;
        }
    }

    std::tcout << "[FsWatcher] Opened files: " << _filePaths.size() << std::endl;

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::watch(
    culong_t a_timeoutMsec
)
{
    _watch_impl();

    Thread::currentSleep(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::close()
{
    _close_impl();

	for (auto &it_fileHandle : _fileHandles) {
		HandleNativeInvalid handle;
		handle = it_fileHandle;

		handle.close();
	}

    _fileHandles.clear();
    _filePaths.clear();
    _cmds.clear();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
