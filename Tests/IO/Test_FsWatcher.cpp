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
    static std::cmap_tstring_t dbCmds
    {
        #include "cmds.db"
    };

    static std::cvec_tstring_t dbWatchDirPaths
    {
        #include "fs_watcher_dirs.db"
    };

    static std::cvec_tstring_t dbWatchDirPathsDisabled
    {
        #include "fs_watcher_dirs_disabled.db"
    };

    xTEST_CASE("FsWatcher::FsWatcher")
    {
        for ( ; ; ) {
            FsWatcher watcher(dbWatchDirPathsDisabled, "*.cc");
            m_bRv = watcher.openDirs(dbWatchDirPaths, dbCmds);
            if ( !m_bRv ) {
                continue;
            }

            watcher.watch(5 * 1000);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
