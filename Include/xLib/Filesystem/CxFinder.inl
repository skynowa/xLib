/**
 * \file   CxFinder.inl
 * \brief  filesystem finder
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if   xENV_WIN
    #include "Platform/Win/CxFinder_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxFinder_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxFinder_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxFinder_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxFinder::CxFinder(
    std::ctstring_t &a_rootDirPath,   ///< target root dir
    std::ctstring_t &a_shellFilter    ///< shell wildcard pattern
) :
    _entry      (),
    _rootDirPath( CxPath(a_rootDirPath).toNative(false) ),
    _shellFilter(a_shellFilter),
    _isMoveFirst (true)
{
    xTEST_EQ(isValid(), false);
    xTEST_EQ(a_rootDirPath.empty(), false);
    xTEST_EQ(a_shellFilter.empty(), false);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxFinder::~CxFinder()
{
    close();
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFinder::rootDirPath() const
{
    xTEST_EQ(_rootDirPath.empty(), false);

    return _rootDirPath;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFinder::shellFilter() const
{
    xTEST_EQ(_shellFilter.empty(), false);

    return _shellFilter;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxFinder::entryName() const
{
    xTEST_EQ(isValid(), true);

    std::tstring_t sRv = _entryName_impl();
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxFinder::entryPath() const
{
    xTEST_EQ(isValid(), true);

    std::tstring_t sRv;

    sRv = CxPath(rootDirPath()).slashAppend() + entryName();

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFinder::fileTypes() const
{
    xTEST_EQ(isValid(), true);

    return _fileTypes_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::moveNext()
{
    xTEST_EQ(isValid(), true);

    bool_t bRv = false;

    if (_isMoveFirst) {
        bRv = _moveFirst();
        xCHECK_RET(!bRv, false);
    } else {
        bRv = _moveNext_impl();
        xCHECK_RET(!bRv, false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFinder::close()
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
inline void_t
CxFinder::dirs(
    std::ctstring_t    &a_rootDirPath,    ///< target root dir
    std::ctstring_t    &a_shellFilter,    ///< shell wildcard pattern
    cbool_t            &a_isRecursively,  ///< is recursive search
    std::vec_tstring_t *a_dirPaths       ///< result dir paths
)
{
    xTEST_EQ(a_rootDirPath.empty(), false);
    xTEST_EQ(a_shellFilter.empty(), false);
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_dirPaths);

    CxFinder finder(a_rootDirPath, a_shellFilter);

    for ( ; ; ) {
        bool_t bRv = finder.moveNext();
        xCHECK_DO(!bRv, break);

        xCHECK_DO(CxConst::dot()  == finder.entryName(), continue);
        xCHECK_DO(CxConst::dot2() == finder.entryName(), continue);

        // set filter for dirs
        xCHECK_DO(!(CxFileType::faDirectory & finder.fileTypes()), continue);

        a_dirPaths->push_back( finder.entryPath() );

        // is search in subdirs
        if (a_isRecursively) {
            CxFinder::dirs(finder.entryPath(), a_shellFilter, true, a_dirPaths);
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxFinder::files(
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
        CxFinder finder(a_rootDirPath, a_shellFilter);

        for ( ; ; ) {
            bool_t bRv = finder.moveNext();
            xCHECK_DO(!bRv, break);

            xCHECK_DO(CxConst::dot()  == finder.entryName(), continue);
            xCHECK_DO(CxConst::dot2() == finder.entryName(), continue);

            // set filter for files
            xCHECK_DO(CxFileType::faDirectory & finder.fileTypes(), continue);

            a_filePaths->push_back(finder.entryPath());
        }
    } else {
        // subdirs
        std::vec_tstring_t dirPaths;
        dirs(a_rootDirPath, CxConst::maskAll(), true, &dirPaths);

        // files in root dir and each subdir
        files(a_rootDirPath, a_shellFilter, false, a_filePaths);

        xFOREACH_CONST(std::vec_tstring_t, it, dirPaths) {
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
inline bool_t
CxFinder::_moveFirst()
{
    xTEST_EQ(isValid(), false);

    _isMoveFirst = false;

    return _moveFirst_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
