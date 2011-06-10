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
#include <xLib/Sync/CxProcess.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxAutoCriticalSection.h>
#elif defined(xOS_LINUX)

#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxFileLog
CxFileLog::CxFileLog() :
    _m_sFilePath       (),
    _m_ulMaxFileSizeMb(lsDefaultMaxSize)
#if defined(xOS_WIN)
    ,
    _m_csFile         ()
#elif defined(xOS_LINUX)
    //TODO: CxCriticalSection
#endif
{
    /*DEBUG*/xASSERT_DO(lsLimitSize > lsDefaultMaxSize, return);

    bSetFilePath( CxPath::sSetExt(CxPath::sGetExe(), xT("exe.log")) );
}
//---------------------------------------------------------------------------
//DONE: CxFileLog
CxFileLog::CxFileLog(
    const tString &csFilePath,
    const ULONG    culMaxFileSizeMb
) :
    _m_sFilePath      (),
    _m_ulMaxFileSizeMb(culMaxFileSizeMb)
#if defined(xOS_WIN)
    ,
    _m_csFile         ()
#elif defined(xOS_LINUX)
    //TODO: CxCriticalSection
#endif
{
    /*DEBUG*/xASSERT_DO(false      == csFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(lsLimitSize > culMaxFileSizeMb,   return);
    /*DEBUG*/xASSERT_DO(lsLimitSize > lsDefaultMaxSize,   return);

    if (tString::npos == csFilePath.find(CxConst::xSLASH)) {
        bSetFilePath( CxPath::sGetDir(CxPath::sGetExe()) + CxConst::xSLASH + csFilePath/* + ".log"*/ );
    } else {
        bSetFilePath( csFilePath );
    }
}
//---------------------------------------------------------------------------
//DONE: ~CxFileLog
CxFileLog::~CxFileLog() {

}
//---------------------------------------------------------------------------
//TODO: bSetFilePath (set log path)
//TODO: test bSetFilePath
BOOL
CxFileLog::bSetFilePath(
    const tString &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    _m_sFilePath.assign(csFilePath);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetFilePath (get log path)
//TODO: test sGetFilePath
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
    /*LOCK*/CxAutoCriticalSection SL(_m_csFile);
#elif defined(xOS_LINUX)
    //TODO: lock
#endif

    CxStdioFile sfFile;

    bRes = sfFile.bOpen(sGetFilePath(), CxStdioFile::omAppend, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen (execute)
BOOL
CxFileLog::bOpen() {
    BOOL bRes = FALSE;

    bRes = CxProcess::bExec(sGetFilePath(), xT(""));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear content)
BOOL
CxFileLog::bClear() {
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    /*LOCK*/CxAutoCriticalSection SL(_m_csFile);
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
    /*LOCK*/CxAutoCriticalSection SL(_m_csFile);
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
    /*LOCK*/CxAutoCriticalSection SL(_m_csFile);
#elif defined(xOS_LINUX)
    //TODO: lock
#endif

    bRes = CxStdioFile::bIsExists(sGetFilePath());
    xCHECK_RET(FALSE == bRes, TRUE);

    LONG liSize = CxStdioFile::liGetSize(sGetFilePath());

    //-------------------------------------
    //delete log, if it is full
    if (static_cast<ULONG>(liSize / 1000000) >= _m_ulMaxFileSizeMb) {
        bRes = CxStdioFile::bDelete(sGetFilePath());
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
