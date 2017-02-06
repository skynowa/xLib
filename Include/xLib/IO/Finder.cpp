/**
 * \file   Finder.inl
 * \brief  filesystem finder
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Finder.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>

#if   xENV_WIN
    #include "Platform/Win/Finder_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Finder_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xl, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Finder::Finder(
    std::ctstring_t &a_rootDirPath,   ///< target root dir
    std::ctstring_t &a_shellFilter    ///< shell wildcard pattern
) :
    _entry      (),
    _rootDirPath( Path(a_rootDirPath).toNative(false) ),
    _shellFilter(a_shellFilter),
    _isMoveFirst(true)
{
    xTEST_EQ(isValid(),             false);
    xTEST_EQ(a_rootDirPath.empty(), false);
    xTEST_EQ(a_shellFilter.empty(), false);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Finder::~Finder()
{
    close();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Finder::rootDirPath() const
{
    xTEST_EQ(_rootDirPath.empty(), false);

    return _rootDirPath;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Finder::shellFilter() const
{
    xTEST_EQ(_shellFilter.empty(), false);

    return _shellFilter;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Finder::entryName() const
{
    xTEST_EQ(isValid(), true);

    std::tstring_t sRv = _entryName_impl();
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Finder::entryPath() const
{
    xTEST_EQ(isValid(), true);

    std::tstring_t sRv;

    sRv = Path(rootDirPath()).slashAppend() + entryName();

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE FileType::types_t
Finder::fileTypes() const
{
    xTEST_EQ(isValid(), true);

    return _fileTypes_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::moveNext()
{
    bool_t bRv = false;

    if (_isMoveFirst) {
        bRv = _moveFirst();
        xCHECK_RET(!bRv, false);
    } else {
        xTEST_EQ(isValid(), true);

        bRv = _moveNext_impl();
        xCHECK_RET(!bRv, false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Finder::close()
{
    _isMoveFirst = true;

    xCHECK_DO(!isValid(), return);

    _close_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Finder::dirs(
    std::ctstring_t    &a_rootDirPath,   ///< target root dir
    std::ctstring_t    &a_shellFilter,   ///< shell wildcard pattern
    cbool_t            &a_isRecursively, ///< is recursive search
    std::vec_tstring_t *a_dirPaths       ///< result dir paths
)
{
    xTEST_EQ(a_rootDirPath.empty(), false);
    xTEST_EQ(a_shellFilter.empty(), false);
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_dirPaths);

    Finder finder(a_rootDirPath, a_shellFilter);

    for ( ; ; ) {
        bool_t bRv = finder.moveNext();
        xCHECK_DO(!bRv, break);

        xCHECK_DO(finder.entryName() == Const::dot(),  continue);
        xCHECK_DO(finder.entryName() == Const::dot2(), continue);

        // set filter for dirs
        xCHECK_DO(!(FileType::faDirectory & finder.fileTypes()), continue);

        a_dirPaths->push_back( finder.entryPath() );

        // is search in subdirs
        if (a_isRecursively) {
            Finder::dirs(finder.entryPath(), a_shellFilter, true, a_dirPaths);
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Finder::files(
    std::ctstring_t    &a_rootDirPath,   ///< target root dir
    std::ctstring_t    &a_shellFilter,   ///< shell wildcard pattern
    cbool_t            &a_isRecursively, ///< is recursive search
    std::vec_tstring_t *a_filePaths      ///< result file paths
)
{
    xTEST_EQ(a_rootDirPath.empty(), false);
    xTEST_EQ(a_shellFilter.empty(), false);
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_filePaths);

    if (!a_isRecursively) {
        Finder finder(a_rootDirPath, a_shellFilter);

        for ( ; ; ) {
            bool_t bRv = finder.moveNext();
            xCHECK_DO(!bRv, break);

            xCHECK_DO(finder.entryName() == Const::dot(),  continue);
            xCHECK_DO(finder.entryName() == Const::dot2(), continue);

            // set filter for files
            xCHECK_DO(FileType::faDirectory & finder.fileTypes(), continue);

            a_filePaths->push_back(finder.entryPath());
        }
    } else {
        // subdirs
        std::vec_tstring_t dirPaths;
        dirs(a_rootDirPath, Const::maskAll(), true, &dirPaths);

        // files in root dir and each subdir
        files(a_rootDirPath, a_shellFilter, false, a_filePaths);

        xFOR_EACH_CONST(std::vec_tstring_t, it, dirPaths) {
            files(*it, a_shellFilter, false, a_filePaths);
        }
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::_moveFirst()
{
    xTEST_EQ(isValid(), false);

    _isMoveFirst = false;

    return _moveFirst_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, io)
