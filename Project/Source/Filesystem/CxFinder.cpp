/**
 * \file   CxFinder.cpp
 * \brief
 */


#include <xLib/Filesystem/CxFinder.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxString.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxFinder::CxFinder(
    std::ctstring_t &a_csRootDirPath,
    std::ctstring_t &a_csShellFilter
) :
    _m_enEnrty      (),
    _m_csRootDirPath( CxPath(a_csRootDirPath).toNative(false) ),
    _m_csShellFilter(a_csShellFilter),
    _m_bIsMoveFirst (true)
{
    xTEST_EQ(false, isValid());
    xTEST_EQ(false, a_csRootDirPath.empty());
    xTEST_EQ(false, a_csShellFilter.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxFinder::~CxFinder() {
    close();
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxFinder::rootDirPath() const {
    xTEST_EQ(false, _m_csRootDirPath.empty());

    return _m_csRootDirPath;
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxFinder::shellFilter() const {
    xTEST_EQ(false, _m_csShellFilter.empty());

    return _m_csShellFilter;
}
//------------------------------------------------------------------------------
std::tstring_t
CxFinder::entryName() const {
    xTEST_EQ(true, isValid());

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.assign( _m_enEnrty.fdData.cFileName );
#elif xOS_ENV_UNIX
    sRv.assign( _m_enEnrty.pdrData->d_name );
#endif

    xTEST_EQ(false, sRv.empty());

    return sRv;
}
//------------------------------------------------------------------------------
CxFileAttribute::ExAttribute
CxFinder::attributes() const {
    xTEST_EQ(true, isValid());

    CxFileAttribute::ExAttribute faRv = CxFileAttribute::faInvalid;

#if   xOS_ENV_WIN
    faRv = static_cast<CxFileAttribute::ExAttribute>( _m_enEnrty.fdData.dwFileAttributes );
#elif xOS_ENV_UNIX
    uchar_t iRv = _m_enEnrty.pdrData->d_type;
	switch (iRv) {
    	case DT_BLK: // block device
            faRv = CxFileAttribute::faBlockDevice;
            break;
		case DT_CHR: // character device
            faRv = CxFileAttribute::faCharacterDevice;
            break;
		case DT_DIR: // directory
            faRv = CxFileAttribute::faDirectory;
            break;
		case DT_FIFO: // named pipe (FIFO)
            faRv = CxFileAttribute::faFifo;
            break;
    	case DT_LNK: // symbolic link
            faRv = CxFileAttribute::faSymbolicLink;
            break;
		case DT_REG: // regular file
            faRv = CxFileAttribute::faRegularFile;
            break;
		case DT_SOCK: // UNIX domain socket
            faRv = CxFileAttribute::faSocket;
            break;
		case DT_UNKNOWN: // type is unknown
    	default:
            faRv = CxFileAttribute::faInvalid;
            break;
    }
#endif

    return faRv;
}
//------------------------------------------------------------------------------
bool_t
CxFinder::isValid() const {
#if   xOS_ENV_WIN
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _m_enEnrty.hHandle, false);
    xCHECK_NA(_m_enEnrty.fdData);
#elif xOS_ENV_UNIX
    xCHECK_RET(NULL == _m_enEnrty.pHandle, false);
    xCHECK_RET(NULL == _m_enEnrty.pdrData, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
bool_t
CxFinder::moveNext() {
    // xTEST_EQ(true, isValid());

    if (_m_bIsMoveFirst) {
        bool_t bRv = _moveFirst();
        xCHECK_RET(!bRv, false);
    } else {
    #if   xOS_ENV_WIN
        BOOL blRv = ::FindNextFile(_m_enEnrty.hHandle, &_m_enEnrty.fdData);
        xCHECK_RET(FALSE == blRv, false);
    #elif xOS_ENV_UNIX
        xFOREVER {
            _m_enEnrty.pdrData = ::readdir(_m_enEnrty.pHandle);
            xCHECK_RET(NULL == _m_enEnrty.pdrData, false);

            // filter by pattern
            int_t iRv = ::fnmatch(shellFilter().c_str(), entryName().c_str(), 0);
            xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

            xCHECK_DO(FNM_NOMATCH == iRv, continue);
            xCHECK_DO(0           == iRv, break);
        }
    #endif
    }

    return true;
}
//------------------------------------------------------------------------------
void_t
CxFinder::close() {
    _m_bIsMoveFirst = true;

    xCHECK_DO(!isValid(), return);

    // close handle
    {
    #if   xOS_ENV_WIN
        BOOL blRes = ::FindClose(_m_enEnrty.hHandle);
        xTEST_DIFF(FALSE, blRes);
    #elif xOS_ENV_UNIX
        int_t iRv = ::closedir(_m_enEnrty.pHandle);
        xTEST_DIFF(- 1, iRv);
    #endif
    }

    // clear data
    {
    #if   xOS_ENV_WIN
        _m_enEnrty.hHandle = xNATIVE_HANDLE_INVALID;
        xSTRUCT_ZERO(_m_enEnrty.fdData);
    #elif xOS_ENV_UNIX
        _m_enEnrty.pHandle = NULL;
        _m_enEnrty.pdrData = NULL;
    #endif
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
void_t
CxFinder::dirs(
    std::ctstring_t    &a_csRootDirPath,
    std::ctstring_t    &a_csPattern,
    cbool_t            &a_cbIsRecursively,
    std::vec_tstring_t *a_pvsDirPathes
)
{
    xTEST_EQ(false, a_csRootDirPath.empty());
    xTEST_EQ(false, a_csPattern.empty());
    xTEST_NA(a_cbIsRecursively);
    xTEST_PTR(a_pvsDirPathes);

    CxFinder fnFinder(a_csRootDirPath, a_csPattern);

    xFOREVER {
        bool_t bRv = fnFinder.moveNext();
        xCHECK_DO(!bRv, break);

        xCHECK_DO(CxConst::xDOT  == fnFinder.entryName(), continue);
        xCHECK_DO(CxConst::x2DOT == fnFinder.entryName(), continue);

        // set filter for dirs
        xCHECK_DO(CxFileAttribute::faDirectory != fnFinder.attributes(), continue);

        std::ctstring_t csDirPath = CxPath(a_csRootDirPath).slashAppend() +
                                    fnFinder.entryName();

        a_pvsDirPathes->push_back(csDirPath);

        // is search in subdirs
        if (a_cbIsRecursively) {
            CxFinder::dirs(csDirPath, a_csPattern, true, a_pvsDirPathes);
        }
    }
}
//------------------------------------------------------------------------------
/* static */
void_t
CxFinder::files(
    std::ctstring_t    &a_csRootDirPath,
    std::ctstring_t    &a_csPattern,
    cbool_t            &a_cbIsRecursively,
    std::vec_tstring_t *a_pvsFilePathes
)
{
    xTEST_EQ(false, a_csRootDirPath.empty());
    xTEST_EQ(false, a_csPattern.empty());
    xTEST_NA(a_cbIsRecursively);
    xTEST_PTR(a_pvsFilePathes);

    if (!a_cbIsRecursively) {
        CxFinder fnFinder(a_csRootDirPath, a_csPattern);

        xFOREVER {
            bool_t bRv = fnFinder.moveNext();
            xCHECK_DO(!bRv, break);

            xCHECK_DO(CxConst::xDOT  == fnFinder.entryName(), continue);
            xCHECK_DO(CxConst::x2DOT == fnFinder.entryName(), continue);

            // set filter for files
            xCHECK_DO(CxFileAttribute::faRegularFile != fnFinder.attributes(), continue);

            std::ctstring_t csFilePath = CxPath(a_csRootDirPath).slashAppend() +
                                         fnFinder.entryName();

            a_pvsFilePathes->push_back(csFilePath);
        }
    } else {
        // subdirs
        std::vec_tstring_t m_vsDirPaths;
        dirs(a_csRootDirPath, CxConst::xMASK_ALL, true, &m_vsDirPaths);

        // files in root dir and each subdir
        files(a_csRootDirPath, a_csPattern, false, a_pvsFilePathes);

        xFOREACH_CONST(std::vec_tstring_t, it, m_vsDirPaths) {
            files(*it, a_csPattern, false, a_pvsFilePathes);
        }
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool_t
CxFinder::_moveFirst() {
    xTEST_EQ(false, isValid());

    _m_bIsMoveFirst = false;

#if   xOS_ENV_WIN
    _m_enEnrty.hHandle = ::FindFirstFile(
                            (rootDirPath() + CxConst::xSLASH + shellFilter()).c_str(),
                            &_m_enEnrty.fdData);
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _m_enEnrty.hHandle, false);
#elif xOS_ENV_UNIX
    _m_enEnrty.pHandle = ::opendir(rootDirPath().c_str());
    xTEST_PTR(_m_enEnrty.pHandle);

    bool_t bRv = moveNext();
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
