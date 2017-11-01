/**
 * \file   Test_FsWatcher.cpp
 * \brief  test FsWatcher
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_FsWatcher)
xTEST_UNIT(Test_FsWatcher)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FsWatcher::unit()
{
    bool bRv = false;

    static const std::map<std::string, std::string> dbCmds
    {
        #include "cmds.db"
    };

    static const std::vector<std::string> dbWatchDirPaths
    {
        #include "fs_watcher_dirs.db"
    };

    static const std::vector<std::string> dbWatchDirPathsDisabled
    {
        #include "fs_watcher_dirs_disabled.db"
    };

    xTEST_CASE("FsWatcher::FsWatcher")
    {
        for ( ; ; ) {
            FsWatcher watcher(dbWatchDirPathsDisabled);
            bRv = watcher.openDirs(dbWatchDirPaths, dbCmds);
            if (!bRv) {
                continue;
            }

            watcher.watch();
            ::sleep(5);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
