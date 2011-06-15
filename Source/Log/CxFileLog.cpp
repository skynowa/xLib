/****************************************************************************
* Class name:  CxFileLog
* Description: logging to file
* File name:   CxFileLog.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:40:37
*
*****************************************************************************/


#include <xLib/Log/CxFileLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxAutoMutex.h>
#elif defined(xOS_LINUX)

#endif


/****************************************************************************
*    public
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxFileLog
CxFileLog::CxFileLog(
    const ULONG culMaxFileSizeBytes
) :
    _m_sFilePath      (),
    _m_ulMaxFileSizeBytes(culMaxFileSizeBytes)
#if defined(xOS_WIN)
//    ,
//    _m_mtFile         ()
#elif defined(xOS_LINUX)
    //TODO: CxMutex
#endif
{
    /*DEBUG*/xASSERT_DO(true        == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(lsLimitSize >  culMaxFileSizeBytes,  return);
    /*DEBUG*/xASSERT_DO(lsLimitSize >  lsDefaultMaxSize,     return);
}
//---------------------------------------------------------------------------
//DONE: ~CxFileLog
/*virtual*/
CxFileLog::~CxFileLog() {

}
//---------------------------------------------------------------------------
//DONE: bSetFilePath (set log path)
BOOL
CxFileLog::bSetFilePath(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    if (tString::npos == csFilePath.find(CxConst::xSLASH)) {
        _m_sFilePath.assign( CxPath::sGetDir(CxPath::sGetExe()) + CxConst::xSLASH + csFilePath);
    } else {
        _m_sFilePath.assign( csFilePath );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetFilePath (get log path)
const tString &
CxFileLog::sGetFilePath() const {
    /*DEBUG*/

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
//DONE: bWrite (write)
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
    tString sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    tString sParam;
    va_list palArgs = NULL;

    va_start(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    va_end(palArgs);

    //-------------------------------------
    //write to file
#if defined(xOS_WIN)
//    /*LOCK*/CxAutoMutex SL(_m_mtFile);
#elif defined(xOS_LINUX)
    //TODO: lock
#endif

    CxStdioFile sfFile;

    bRes = sfFile.bOpen(sGetFilePath(), CxStdioFile::omAppend, FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    INT iRes = sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    /*DEBUG*/xASSERT_RET(iRes != CxStdioFile::etError, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear content)
BOOL
CxFileLog::bClear() {
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
//    /*LOCK*/CxAutoMutex SL(_m_mtFile);
#elif defined(xOS_LINUX)
    //TODO: lock
#endif

    bRes = CxStdioFile::bClear(sGetFilePath());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (delete)
BOOL
CxFileLog::bDelete() {
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
//    /*LOCK*/CxAutoMutex SL(_m_mtFile);
#elif defined(xOS_LINUX)
    //TODO: lock
#endif

    bRes = CxStdioFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bDeleteIfFull (delete log, if it is full)
BOOL
CxFileLog::_bDeleteIfFull() {
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
//    /*LOCK*/CxAutoMutex SL(_m_mtFile);
#elif defined(xOS_LINUX)
    //TODO: lock
#endif

    bRes = CxStdioFile::bIsExists(sGetFilePath());
    xCHECK_RET(FALSE == bRes, TRUE);

    //-------------------------------------
    //delete log, if full
    ULONG ulSize = static_cast<ULONG>(  CxStdioFile::liGetSize(sGetFilePath()) );

    xCHECK_RET(ulSize < _m_ulMaxFileSizeBytes, TRUE);

    bRes = CxStdioFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
