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
	struct Cmd
	{
		std::tstring_t projectName;
		std::tstring_t dirPath;
		std::tstring_t dirPathsDisabled;
		size_t         buildPriority;
		std::tstring_t cmdPath;
		std::tstring_t cmdPathQuick;
		bool           isEnabled;
	};

    static std::cmap_tstring_t dbCmds
    {
		#include "cmds_suppliers.db"
    };

    std::vec_tstring_t dbWatchDirPaths
#if 0
	{
		#include "fs_watcher_dirs_suppliers.db"
	};
#else
	;
	dbWatchDirPaths.push_back("/home/skynowa/Projects/xLib/Include/xLib/Fs");
#endif

    static std::cvec_tstring_t dbWatchDirPathsDisabled
    {
        #include "fs_watcher_dirs_disabled_suppliers.db"
    };

    xTEST_CASE("FsWatcher::FsWatcher")
    {
        for ( ; ; ) {
            FsWatcher watcher(dbWatchDirPathsDisabled, xT("*.cpp"));
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
