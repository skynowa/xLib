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
    const std::tstring_t &a_csFilterByShell
) :
    _m_enEnrty           (),
    _m_csRootDirPath     (a_csRootDirPath),
    _m_csFilterByShell   (a_csFilterByShell),
    _m_bIsMoveFirstPassed(false)
{
    xTEST_NA(bIsValid());
    xTEST_EQ(false, _m_csRootDirPath.empty());
    xTEST_EQ(false, _m_csFilterByShell.empty());
    xTEST_EQ(false, _m_bIsMoveFirstPassed);
}
//---------------------------------------------------------------------------
/* virtual */
CxFinder::~CxFinder() {
    vClose();
}
//--------------------------------------------------------------------------
const std::tstring_t &
CxFinder::sRootDirPath() const {
    xTEST_EQ(false, _m_csRootDirPath.empty());

    return _m_csRootDirPath;
}
//--------------------------------------------------------------------------
const std::tstring_t &
CxFinder::sFilterByShell() const {
    xTEST_EQ(false, _m_csFilterByShell.empty());

    return _m_csFilterByShell;
}
//--------------------------------------------------------------------------
std::tstring_t
CxFinder::sEntryName() const {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.assign( _m_enEnrty.fdData.cFileName );
#elif xOS_ENV_UNIX
    sRv.assign( _m_enEnrty.pdrData->d_name );
#endif

    xTEST_EQ(false, sRv.empty());

    return sRv;
}
//--------------------------------------------------------------------------
CxFileAttribute::ExAttribute
CxFinder::faAttributes() const {
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
CxFinder::bIsValid() const {
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
CxFinder::bMoveFirst() {
#if   xOS_ENV_WIN
    _m_enEnrty.hHandle = ::FindFirstFile(
                            (sRootDirPath() + CxConst::xSLASH + sFilterByShell()).c_str(),
                            &_m_enEnrty.fdData);
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _m_enEnrty.hHandle, false);
#elif xOS_ENV_UNIX
    _m_enEnrty.pHandle = ::opendir(sRootDirPath().c_str());
    xTEST_PTR(_m_enEnrty.pHandle);

    bool bRv = bMoveNext();
    xCHECK_RET(false == bRv, false);
#endif

    // set flag
    _m_bIsMoveFirstPassed = true;

    return true;
}
//---------------------------------------------------------------------------
bool
CxFinder::bMoveNext() {
#if   xOS_ENV_WIN
    BOOL blRv = ::FindNextFile(_m_enEnrty.hHandle, &_m_enEnrty.fdData);
    xCHECK_RET(FALSE == blRv, false);
#elif xOS_ENV_UNIX
    xFOREVER {
        _m_enEnrty.pdrData = ::readdir(_m_enEnrty.pHandle);
        xCHECK_RET(NULL == _m_enEnrty.pdrData, false);

        // filter by pattern
        int iRv = ::fnmatch(sFilter().c_str(), sEntryName().c_str(), 0);
        xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

        xCHECK_DO(FNM_NOMATCH == iRv, continue);
        xCHECK_DO(0           == iRv, break);
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
void
CxFinder::vClose() {
    // reset flag
    _m_bIsMoveFirstPassed = false;

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

xNAMESPACE_END(NxLib)
