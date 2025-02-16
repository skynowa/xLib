/**
 * \file  Finder.cpp
 * \brief Filesystem finder
 */


#include "Finder.h"

#include <xLib/Test/Test.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/System/Environment.h>

#if   xENV_WIN
    #include "Platform/Win/Finder_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Finder_unix.inl"
#endif


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Finder::Finder(
    std::ctstring_t &a_rootDirPath,   ///< target root dir
    std::ctstring_t &a_shellFilter    ///< shell wildcard pattern
) :
    _rootDirPath( Path(a_rootDirPath).toNative(false).str() ),
    _shellFilter(a_shellFilter)
{
    xTEST(!_entry.handle.isValid());
    xTEST(!a_rootDirPath.empty());
    xTEST(!a_shellFilter.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Finder::~Finder()
{
    close();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Finder::rootDirPath() const
{
	xTEST(!_rootDirPath.empty());

    return _rootDirPath;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Finder::shellFilter() const
{
	xTEST(!_shellFilter.empty());

    return _shellFilter;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Finder::entryName() const
{
	xTEST(_entry.handle.isValid());

    std::ctstring_t sRv = _entryName_impl();
    xTEST(!sRv.empty());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Finder::isDot() const
{
    std::ctstring_t &name = entryName();
    if (name == Const::dot() ||
        name == Const::dot2())
    {
    	return true;
    }

    return false;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Finder::entryPath() const
{
	xTEST(_entry.handle.isValid());

    std::tstring_t sRv;

    sRv = Path(rootDirPath()).slashAppend().str() + entryName();

    return sRv;
}
//-------------------------------------------------------------------------------------------------
FileType::types_t
Finder::fileTypes() const
{
	xTEST(_entry.handle.isValid());

    return _fileTypes_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Finder::moveNext()
{
    bool_t bRv {};

    if (_isMoveFirst) {
        bRv = _moveFirst();
        xCHECK_RET(!bRv, false);
    } else {
    	xTEST(_entry.handle.isValid());

        bRv = _moveNext_impl();
        xCHECK_RET(!bRv, false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Finder::close()
{
    _isMoveFirst = true;

    xCHECK_DO(!_entry.handle.isValid(), return);

    _close_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
Finder::dirs(
    std::ctstring_t    &a_rootDirPath,   ///< target root dir
    std::ctstring_t    &a_shellFilter,   ///< shell wildcard pattern
    cbool_t             a_isRecursively, ///< is recursive search
    std::vec_tstring_t *a_dirPaths       ///< result dir paths
)
{
    xTEST(!a_rootDirPath.empty());
    xTEST(!a_shellFilter.empty());
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_dirPaths);

    if ( !Dir(a_rootDirPath).isExists() ) {
    	return;
    }

    for (Finder finder(a_rootDirPath, a_shellFilter); finder.moveNext(); ) {
        xCHECK_DO(finder.isDot(), continue);

        // set filter for dirs
        if ( !(static_cast<FileType::types_t>(FileType::Type::Directory) & finder.fileTypes()) ) {
            continue;
        }

        a_dirPaths->push_back( finder.entryPath() );

        // is search in subdirs
        if (a_isRecursively) {
            Finder::dirs(finder.entryPath(), a_shellFilter, true, a_dirPaths);
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Finder::files(
    std::ctstring_t    &a_rootDirPath,   ///< target root dir
    std::ctstring_t    &a_shellFilter,   ///< shell wildcard pattern
    cbool_t             a_isRecursively, ///< is recursive search
    std::vec_tstring_t *a_filePaths      ///< result file paths
)
{
	xTEST(!a_rootDirPath.empty());
	xTEST(!a_shellFilter.empty());
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_filePaths);

    if (!a_isRecursively) {
        for (Finder finder(a_rootDirPath, a_shellFilter); finder.moveNext(); ) {
            xCHECK_DO(finder.isDot(), continue);

            // set filter for files
            if (static_cast<FileType::types_t>(FileType::Type::Directory) & finder.fileTypes()) {
                continue;
            }

            a_filePaths->push_back(finder.entryPath());
        }
    } else {
        // subdirs
        std::vec_tstring_t dirPaths;
        dirs(a_rootDirPath, Const::maskAll(), true, &dirPaths);

        // files in root dir and each subdir
        files(a_rootDirPath, a_shellFilter, false, a_filePaths);

        for (const auto &it : dirPaths) {
            files(it, a_shellFilter, false, a_filePaths);
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Finder::file(
	std::cvec_tstring_t &a_rootDirPaths,
	std::ctstring_t     &a_shellFilter,
    cbool_t              a_isRecursively
)
{
	for (const auto &it_rootDirPath : a_rootDirPaths) {
		std::vec_tstring_t outFles;
		files(it_rootDirPath, a_shellFilter, a_isRecursively, &outFles);
		if ( outFles.empty() ) {
			continue;
		}

		return outFles.front();
	}

	return {};
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Finder::fileInEnvPath(
	std::ctstring_t &a_shellFilter,
    cbool_t          a_isRecursively
)
{
    const Environment env = Environment::path();

	return file(env.values(), a_shellFilter, a_isRecursively);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Finder::_moveFirst()
{
    xTEST(!_entry.handle.isValid());

    _isMoveFirst = false;

    return _moveFirst_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
