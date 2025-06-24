/**
 * \file   FsWatcher.cpp
 * \brief  File system watcher
 */


#include "FsWatcher.h"

#include <xLib/Core/Const.h>

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

#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Sync/ThreadCurrent.h>


namespace xl::fs
{

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
FsWatcher::openFiles(
    std::cvec_tstring_t &a_filePaths,
    std::cmap_tstring_t &a_cmds
)
{
	close();

    // _filePaths
    for (const auto &it_filePath : a_filePaths) {
        FileIO file(it_filePath);
        file.open(FileIO::OpenMode::ReadOnly);

        if ( !file.get().isValid() ) {
            std::tcout << "[FsWatcher] Can't open: " << it_filePath << std::endl;
            continue;
        }

        _filePaths.push_back(it_filePath);
        _fileHandles.push_back( file.getNative() );

        // TODO: FileIO::detach - removed
        // HandleStdFile &handle = file.detach();
        // xUNUSED(handle);
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
    bool_t bRv {};

	close();

    for (const auto &it_dirPath : a_dirPaths) {
        std::vec_tstring_t filePaths;
        Finder::files(it_dirPath, _shellFilter, true, &filePaths);
        std::tcout << "[FsWatcher] Open dir: " << it_dirPath << ", " << filePaths.size() << std::endl;
        if ( filePaths.empty() ) {
            continue;
        }

        bRv = openFiles(filePaths, a_cmds);
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

    ThreadCurrent::sleep(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::close()
{
    _close_impl();

	for (const auto &it_fileHandle : _fileHandles) {
        // TODO: Close handles
		xUNUSED(it_fileHandle);

    #if 0
		HandleNativeInvalid handle;
		handle = it_fileHandle;

		handle.close();
    #endif
	}

    _fileHandles.clear();
    _filePaths.clear();
    _cmds.clear();
}
//-------------------------------------------------------------------------------------------------

} // namespace
