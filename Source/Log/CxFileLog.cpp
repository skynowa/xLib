/**
 * \file  CxFileLog.cpp
 * \brief logging to file
 */


#include <xLib/Log/CxFileLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxAutoMutex.h>
#endif


/****************************************************************************
*    public
*
*****************************************************************************/


//---------------------------------------------------------------------------
CxFileLog::CxFileLog(
    const ULONG culMaxFileSizeBytes
) :
    _m_sFilePath         (),
    _m_ulMaxFileSizeBytes(culMaxFileSizeBytes)
	#if xTODO
		CxAutoMutex
	#endif
{
    /*DEBUG*/xASSERT_DO(true        == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(lsLimitSize >  culMaxFileSizeBytes,  return);
    /*DEBUG*/xASSERT_DO(lsLimitSize >  lsDefaultMaxSize,     return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxFileLog::~CxFileLog() {

}
//---------------------------------------------------------------------------
BOOL
CxFileLog::bSetFilePath(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    if (std::tstring::npos == csFilePath.find(CxConst::xSLASH)) {
        _m_sFilePath.assign( CxPath::sGetDir(CxPath::sGetExe()) + CxConst::xSLASH + csFilePath);
    } else {
        _m_sFilePath.assign( csFilePath );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
const std::tstring &
CxFileLog::sGetFilePath() const {
    /*DEBUG*/

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
BOOL
CxFileLog::bWrite(
    LPCTSTR pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    BOOL bRes = FALSE;

    bRes = _bDeleteIfFull();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //time
    std::tstring sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::tstring sParam;
    va_list      palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write to file
	#if xTODO
		CxAutoMutex SL(_m_mtFile);
	#endif

    CxFile sfFile;

    bRes = sfFile.bOpen(sGetFilePath(), CxFile::omAppend, FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    INT iRes = sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    /*DEBUG*/xASSERT_RET(iRes != CxFile::etError, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFileLog::bClear() {
    BOOL bRes = FALSE;

	#if xTODO
		CxAutoMutex SL(_m_mtFile);
	#endif

    bRes = CxFile::bClear(sGetFilePath());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFileLog::bDelete() {
    BOOL bRes = FALSE;

	#if xTODO
		CxAutoMutex SL(_m_mtFile);
	#endif

    bRes = CxFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxFileLog::_bDeleteIfFull() {
    BOOL bRes = FALSE;

	#if xTODO
		CxAutoMutex SL(_m_mtFile);
	#endif

    bRes = CxFile::bIsExists(sGetFilePath());
    xCHECK_RET(FALSE == bRes, TRUE);

    //-------------------------------------
    //delete log, if full
    ULONG ulSize = static_cast<ULONG>( CxFile::liGetSize(sGetFilePath()) );

    xCHECK_RET(ulSize < _m_ulMaxFileSizeBytes, TRUE);

    bRes = CxFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
