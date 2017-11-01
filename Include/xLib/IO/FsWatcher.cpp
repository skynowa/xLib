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
        #include "Platform/Linux/FsWatcher_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/FsWatcher_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/FsWatcher_apple.inl"
    #endif
#endif

#include <xLib/IO/File.h>
#include <xLib/IO/Finder.h>


xNAMESPACE_BEGIN2(xl, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
FsWatcher::FsWatcher(
    std::cvec_tstring_t &a_dbWatchDirPathsDisabled
) :
    _dbWatchDirPathsDisabled(a_dbWatchDirPathsDisabled)
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE
FsWatcher::~FsWatcher()
{
    close();

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE
bool_t
FsWatcher::open(
    std::cvec_tstring_t &a_filePaths,
    std::cmap_tstring_t &a_dbCmds
)
{
    // _filePaths
    for (auto &it_filePath : a_filePaths) {
        File file;
        file.create(it_filePath, File::omRead);

        if ( !file.isValid() ) {
            std::tcout << "[FsWatcher] Can't open: " << it_filePath << std::endl;
            continue;
        }

        _filePaths.push_back(it_filePath);
        _fileHandles.push_back( file.getNative() );
    }

    if ( _filePaths.empty() ) {
        return false;
    }

    // a_dbCmds
    _dbCmds = a_dbCmds;

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE
bool
FsWatcher::openDirs(
    std::cvec_tstring_t &a_dirPaths,
    std::cmap_tstring_t &a_dbCmds
)
{
    bool bRv = false;

    for (auto &it_dirPath : a_dirPaths) {
        std::vec_tstring_t filePaths;
        Finder::files(it_dirPath, "*.cc", true, &filePaths);
        if ( filePaths.empty() ) {
            continue;
        }

        bRv = open(filePaths, a_dbCmds);
        if (!bRv) {
            continue;
        }
    }

    std::tcout << "[FsWatcher] Opened files: " << _filePaths.size() << std::endl;

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
FsWatcher::watch()
{
    _watch_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
FsWatcher::close()
{
    _close_impl();

    _fileHandles.clear();
    _filePaths.clear();
    _dbCmds.clear();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, io)
