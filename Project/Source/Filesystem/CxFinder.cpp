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
    const std::tstring_t &a_csRootDirPath,
    const std::tstring_t &a_csFilterByShell
) :
    _m_enEnrty           (),
    _m_csRootDirPath     (a_csRootDirPath),
    _m_csFilterByShell   (a_csFilterByShell)
{
    xTEST_NA(bIsValid());
    xTEST_EQ(false, _m_csRootDirPath.empty());
    xTEST_EQ(false, _m_csFilterByShell.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxFinder::~CxFinder() {
    close();
}
//--------------------------------------------------------------------------
const std::tstring_t &
CxFinder::rootDirPath() const {
    xTEST_EQ(false, _m_csRootDirPath.empty());

    return _m_csRootDirPath;
}
//--------------------------------------------------------------------------
const std::tstring_t &
CxFinder::filterByShell() const {
    xTEST_EQ(false, _m_csFilterByShell.empty());

    return _m_csFilterByShell;
}
//--------------------------------------------------------------------------
std::tstring_t
CxFinder::entryName() const {
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
CxFinder::attributes() const {
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
bool
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
bool
CxFinder::moveFirst() {
#if   xOS_ENV_WIN
    _m_enEnrty.hHandle = ::FindFirstFile(
                            (rootDirPath() + CxConst::xSLASH + filterByShell()).c_str(),
                            &_m_enEnrty.fdData);
    xCHECK_RET(xNATIVE_HANDLE_INVALID == _m_enEnrty.hHandle, false);
#elif xOS_ENV_UNIX
    _m_enEnrty.pHandle = ::opendir(rootDirPath().c_str());
    xTEST_PTR(_m_enEnrty.pHandle);

    bool bRv = moveNext();
    xCHECK_RET(false == bRv, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
bool
CxFinder::moveNext() {
#if   xOS_ENV_WIN
    BOOL blRv = ::FindNextFile(_m_enEnrty.hHandle, &_m_enEnrty.fdData);
    xCHECK_RET(FALSE == blRv, false);
#elif xOS_ENV_UNIX
    xFOREVER {
        _m_enEnrty.pdrData = ::readdir(_m_enEnrty.pHandle);
        xCHECK_RET(NULL == _m_enEnrty.pdrData, false);

        // filter by pattern
        int iRv = ::fnmatch(filterByShell().c_str(), entryName().c_str(), 0);
        xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

        xCHECK_DO(FNM_NOMATCH == iRv, continue);
        xCHECK_DO(0           == iRv, break);
    }
#endif

    return true;
}
//------------------------------------------------------------------------------
void
CxFinder::close() {
    xCHECK_DO(false == isValid(), return);

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
