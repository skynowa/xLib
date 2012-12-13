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

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFinder::CxFinder(
    const std::tstring_t &a_csRootDirPath,
    const std::tstring_t &a_csFileFilter
) :
    _m_enEnrty      (),
    _m_csRootDirPath(a_csRootDirPath),
    _m_csFilter     (a_csFileFilter)
{
    xTEST_EQ(false, a_csRootDirPath.empty());
    xTEST_EQ(false, a_csFileFilter.empty());
}
//---------------------------------------------------------------------------
/* virtual */
CxFinder::~CxFinder() {
    vClose();
}
//--------------------------------------------------------------------------
const std::tstring_t &
CxFinder::sRootDirPath() {
    return _m_csRootDirPath;
}
//--------------------------------------------------------------------------
const std::tstring_t &
CxFinder::sFilter() {
    return _m_csFilter;
}
//--------------------------------------------------------------------------
std::tstring_t
CxFinder::sFileName() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.assign( _m_enEnrty.fdData.cFileName );
#elif xOS_ENV_UNIX
    sRv.assign( _m_enEnrty.pdrData->d_name );
#endif

    return sRv;
}
//--------------------------------------------------------------------------
CxFileAttribute::ExAttribute
CxFinder::faAttributes() {
    CxFileAttribute::ExAttribute faAttr = CxFileAttribute::faInvalid;

#if   xOS_ENV_WIN
    faAttr = static_cast<CxFileAttribute::ExAttribute>( _m_enEnrty.fdData.dwFileAttributes );
#elif xOS_ENV_UNIX
    uchar_t iRv = _m_enEnrty.pdrData->d_type;
	switch (iRv) {
    	case DT_BLK:     { faAttr = CxFileAttribute::faBlockDevice;     } break;  // block device
		case DT_CHR:     { faAttr = CxFileAttribute::faCharacterDevice; } break;  // character device
		case DT_DIR:     { faAttr = CxFileAttribute::faDirectory;       } break;  // directory
		case DT_FIFO:    { faAttr = CxFileAttribute::faFifo;            } break;  // named pipe (FIFO)
    	case DT_LNK:     { faAttr = CxFileAttribute::faSymbolicLink;    } break;  // symbolic link
		case DT_REG:     { faAttr = CxFileAttribute::faRegularFile;     } break;  // regular file
		case DT_SOCK:    { faAttr = CxFileAttribute::faSocket;          } break;  // UNIX domain socket
		case DT_UNKNOWN: { faAttr = CxFileAttribute::faInvalid;         } break;  // type is unknown

    	default:         { faAttr = CxFileAttribute::faInvalid;         } break;
    }
#endif

    return faAttr;
}
//---------------------------------------------------------------------------
bool
CxFinder::bIsValid() {
#if   xOS_ENV_WIN
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _m_enEnrty.hHandle, false);
    xCHECK_NA(_m_enEnrty.fdData);
#elif xOS_ENV_UNIX
    xCHECK_RET(NULL == _m_enEnrty.pHandle, false);
    xCHECK_RET(NULL == _m_enEnrty.pdrData, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxFinder::bFirst() {
#if   xOS_ENV_WIN
    _m_enEnrty.hHandle = ::FindFirstFile(
                            (sRootDirPath() + CxConst::xSLASH + sFilter()).c_str(),
                            &_m_enEnrty.fdData);
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _m_enEnrty.hHandle, false);
#elif xOS_ENV_UNIX
    _m_enEnrty.pHandle = ::opendir(csRootDirPath().c_str());
    xTEST_PTR(_m_enEnrty.pHandle);

    _m_enEnrty.pdrData = ::readdir(_m_enEnrty.pHandle);
    xCHECK_RET(NULL == _m_enEnrty.pdrData, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxFinder::bNext() {
#if   xOS_ENV_WIN
    BOOL blRv = ::FindNextFile(_m_enEnrty.hHandle, &_m_enEnrty.fdData);
    xCHECK_RET(FALSE == blRv, false);
#elif xOS_ENV_UNIX
    _m_enEnrty.pdrData = ::readdir(_m_enEnrty.pHandle);
    xCHECK_RET(NULL == _m_enEnrty.pdrData, false);

    // filter by pattern
    {
        int iRv = ::fnmatch(sFilter().c_str(), sFileName().c_str(), 0);
        xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

        xCHECK_DO(0 != iRv, bNext());
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
void
CxFinder::vClose() {
    xCHECK_DO(false == bIsValid(), return);

    // close handle
    {
    #if   xOS_ENV_WIN
        BOOL blRes = ::FindClose(_m_enEnrty.hHandle);
        xTEST_DIFF(FALSE, blRes);
    #elif xOS_ENV_UNIX
        int iRv = ::closedir(_m_enEnrty.pHandle);
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
//--------------------------------------------------------------------------



//--------------------------------------------------------------------------
/* static */
void
vFindDirs(
    const std::tstring_t &a_csDirPath,          ///< directory path
    const std::tstring_t &a_csPattern,          ///< pattern
    const bool           &a_cbIsRecursively,    ///< recursively scan
    std::vec_tstring_t   *a_pvsDirPathes        ///< output directory paths (must be empty)
)
{
    xTEST_EQ(false, a_csDirPath.empty());
    xTEST_NA(a_cbIsRecursively);
    xTEST_PTR(a_pvsDirPathes);

    // TODO: CxDir::vFindDirs
    #if xTODO
        (*a_pvsDirPathes).clear();
    #endif

#if   xOS_ENV_WIN
    std::tstring_t  sRootDirPath = CxPath::sToNative( CxPath::sSlashAppend(a_csDirPath) + a_csPattern, false );
    WIN32_FIND_DATA fdData       = {0};

    HANDLE hFile = ::FindFirstFile(sRootDirPath.c_str(), &fdData);
    xTEST_DIFF(xNATIVE_HANDLE_INVALID, hFile);

    do {
        // dirs
        if (CxFileAttribute::faDirectory == (fdData.dwFileAttributes & CxFileAttribute::faDirectory)) {
            std::tstring_t sFileName = fdData.cFileName;

            // skip "." ".."
            xCHECK_DO(CxConst::xDOT  == sFileName, continue);
            xCHECK_DO(CxConst::x2DOT == sFileName, continue);

            std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath) + sFileName;

            (*a_pvsDirPathes).push_back(sDirPath);

            // is search in subdirs ?
            if (true == a_cbIsRecursively) {
                vFindDirs(sDirPath, a_csPattern, a_cbIsRecursively, a_pvsDirPathes);  // recursion
            }
        }
        // files, etc
        else {
            xNA;
        }
    }
    while ( FALSE != ::FindNextFile(hFile, &fdData) );

    BOOL blRes = ::FindClose(hFile);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    DIR *pDir = ::opendir(a_csDirPath.c_str());
    xTEST_PTR(pDir);

    dirent *pdrEntry = ::readdir(pDir);
    xTEST_PTR(pdrEntry);

    do {
        // dirs
        if (DT_DIR == pdrEntry->d_type) {
            std::tstring_t sFileName = pdrEntry->d_name;

            // skip "." ".."
            xCHECK_DO(CxConst::xDOT  == sFileName, continue);
            xCHECK_DO(CxConst::x2DOT == sFileName, continue);

            // filter by pattern
            {
                int iRv = ::fnmatch(a_csPattern.c_str(), sFileName.c_str(), 0);
                xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

                xCHECK_DO(0 != iRv, continue);
            }

            std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath) + sFileName;

            (*a_pvsDirPathes).push_back(sDirPath);

            // is search in subdirs ?
            if (true == a_cbIsRecursively) {
                vFindDirs(sDirPath, a_csPattern, a_cbIsRecursively, a_pvsDirPathes);  // recursion
            }
        }
        // files, etc
        else {
            xNA;
        }
    }
    while ( NULL != (pdrEntry = ::readdir(pDir)) );

    int iRv = ::closedir(pDir); pDir = NULL;
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

xNAMESPACE_END(NxLib)
