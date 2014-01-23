/**
 * \file   CxFinder.cpp
 * \brief
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


xNAMESPACE2_BEGIN(xlib, filesystem)

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
    xTEST_EQ(false, isValid());
    xTEST_EQ(false, a_rootDirPath.empty());
    xTEST_EQ(false, a_shellFilter.empty());
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
    xTEST_EQ(false, _rootDirPath.empty());

    return _rootDirPath;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFinder::shellFilter() const
{
    xTEST_EQ(false, _shellFilter.empty());

    return _shellFilter;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxFinder::entryName() const
{
    xTEST_EQ(true, isValid());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.assign( _entry.data.cFileName );
#elif xOS_ENV_UNIX
    sRv.assign( _entry.data.d_name );
#endif

    xTEST_EQ(false, sRv.empty());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxFinder::entryPath() const
{
    xTEST_EQ(true, isValid());

    std::tstring_t sRv;

    sRv = CxPath(rootDirPath()).slashAppend() + entryName();

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFinder::fileTypes() const
{
    xTEST_EQ(true, isValid());

#if   xOS_ENV_WIN
    CxFileType::types_t ftRv = CxFileType::faInvalid;

    ftRv = _entry.data.dwFileAttributes;
#elif xOS_ENV_UNIX
    CxFileType::types_t ftRv = 0;

    uchar_t ucRv = _entry.data.d_type;
    switch (ucRv) {
    case DT_BLK: // block device
        ftRv |= CxFileType::faBlockDevice;
        break;
    case DT_CHR: // character device
        ftRv |= CxFileType::faCharacterDevice;
        break;
    case DT_DIR: // directory
        ftRv |= CxFileType::faDirectory;
        break;
    case DT_FIFO: // named pipe (FIFO)
        ftRv |= CxFileType::faFifo;
        break;
    case DT_LNK: // symbolic link
        ftRv |= CxFileType::faSymbolicLink;
        break;
    case DT_REG: // regular file
        ftRv |= CxFileType::faRegularFile;
        break;
    case DT_SOCK: // UNIX domain socket
        ftRv |= CxFileType::faSocket;
        break;
    case DT_UNKNOWN: // type is unknown
    default:
        ftRv = CxFileType::faInvalid;
        break;
    }
#endif

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::isValid() const
{
#if   xOS_ENV_WIN
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _entry.handle, false);
    xCHECK_NA(_entry.data);
#elif xOS_ENV_UNIX
    xCHECK_RET(NULL == _entry.handle, false);
    xCHECK_NA(entry.data);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::moveNext()
{
    // xTEST_EQ(true, isValid());

    if (_isMoveFirst) {
        bool_t bRv = _moveFirst();
        xCHECK_RET(!bRv, false);
    } else {
    #if   xOS_ENV_WIN
        BOOL blRv = ::FindNextFile(_entry.handle, &_entry.data);
        if (FALSE == blRv) {
            xCHECK_RET(ERROR_NO_MORE_FILES == CxLastError::get(), false);

            xTEST_FAIL;
        }
    #elif xOS_ENV_UNIX
        int_t iRv = 0;

        xFOREVER {
            dirent *entryRv = NULL;

            iRv = ::readdir_r(_entry.handle, &_entry.data, &entryRv);
            xTEST_EQ(iRv, 0);
            xCHECK_RET(NULL == entryRv, false);

            // filter by pattern
            iRv = ::fnmatch(shellFilter().c_str(), entryName().c_str(), 0);
            xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

            xCHECK_DO(FNM_NOMATCH == iRv, continue);
            xCHECK_DO(0           == iRv, break);
        }
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFinder::close()
{
    _isMoveFirst = true;

    xCHECK_DO(!isValid(), return);

    // close handle
    {
    #if   xOS_ENV_WIN
        BOOL blRv = ::FindClose(_entry.handle);
        xTEST_DIFF(FALSE, blRv);
    #elif xOS_ENV_UNIX
        int_t iRv = ::closedir(_entry.handle);
        xTEST_DIFF(- 1, iRv);
    #endif
    }

    // clear data
    {
    #if   xOS_ENV_WIN
        _entry.handle = xNATIVE_HANDLE_INVALID;
    #elif xOS_ENV_UNIX
        _entry.handle = NULL;
    #endif
        xSTRUCT_ZERO(_entry.data);
    }
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
    xTEST_EQ(false, a_rootDirPath.empty());
    xTEST_EQ(false, a_shellFilter.empty());
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_dirPaths);

    CxFinder finder(a_rootDirPath, a_shellFilter);

    xFOREVER {
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
    xTEST_EQ(false, a_rootDirPath.empty());
    xTEST_EQ(false, a_shellFilter.empty());
    xTEST_NA(a_isRecursively);
    xTEST_PTR(a_filePaths);

    if (!a_isRecursively) {
        CxFinder finder(a_rootDirPath, a_shellFilter);

        xFOREVER {
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
    xTEST_EQ(false, isValid());

    _isMoveFirst = false;

#if   xOS_ENV_WIN
    _entry.handle = ::FindFirstFile((rootDirPath() + CxConst::slash() + shellFilter()).c_str(),
        &_entry.data);
    xCHECK_RET(_entry.handle == xNATIVE_HANDLE_INVALID, false);
#elif xOS_ENV_UNIX
    _entry.handle = ::opendir(rootDirPath().c_str());
    xCHECK_RET(_entry.handle == NULL, false);

    bool_t bRv = moveNext();
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, filesystem)
