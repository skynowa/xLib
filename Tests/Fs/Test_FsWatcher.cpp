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
class AutoBuilder :
    public FsWatcher
{
public:
	AutoBuilder(std::cvec_tstring_t &dirPathsDisabled, std::ctstring_t &shellFilter) :
		FsWatcher(dirPathsDisabled, shellFilter)
	{
	}

	virtual
	void_t onEvent(std::ctstring_t &a_fsName, cEvent a_event) xOVERRIDE
	{
		std::tcout << xTRACE_VAR(a_fsName) << ": ";

		switch (a_event) {
		case Attrib:
			std::tcout << xT("Attrib") << " ";
			break;
		case CloseNoWrite:
			std::tcout << xT("CloseNoWrite") << " ";
			break;
		case CloseWrite:
			std::tcout << xT("CloseWrite") << " ";
			break;
		case Open:
			std::tcout << xT("Open") << " ";
			break;
		case MovedTo:
			std::tcout << xT("MovedTo") << " ";
			break;
		case Delete:
			std::tcout << xT("Delete") << " ";
			break;
		case Unknown:
		default:
			std::tcout << xT("Unknown") << " ";
			break;
		}

		std::tcout << std::endl;
	}
};
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
            AutoBuilder builder(dbWatchDirPathsDisabled, xT("*.inl"));
            m_bRv = builder.openDirs(dbWatchDirPaths, dbCmds);
            if ( !m_bRv ) {
                continue;
            }

            builder.watch(5 * 1000);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
