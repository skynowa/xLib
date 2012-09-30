/**
 * \file  CxFileLog.cpp
 * \brief logging to file
 */


#include <xLib/Log/CxFileLog.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if   xOS_ENV_WIN
    #include <xLib/Sync/CxAutoIpcMutex.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFileLog::CxFileLog(
    const ulong_t a_culMaxFileSizeBytes
) :
    _m_sFilePath         (),
    _m_ulMaxFileSizeBytes(a_culMaxFileSizeBytes)
    #if xTODO
        CxAutoIpcMutex
    #endif
{
    /*DEBUG*/xTEST_EQ(true, _m_sFilePath.empty());
    /*DEBUG*/xTEST_GREATER(lsLimitSize, lsDefaultMaxSize);
    /*DEBUG*/xTEST_GREATER(static_cast<ulong_t>( lsLimitSize ), a_culMaxFileSizeBytes);
}
//---------------------------------------------------------------------------
/* virtual */
CxFileLog::~CxFileLog() {

}
//---------------------------------------------------------------------------
bool
CxFileLog::bSetFilePath(
    const std::tstring_t &a_csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == a_csFilePath.empty(), false);

    if (std::tstring_t::npos == a_csFilePath.find(CxConst::xSLASH)) {
        _m_sFilePath = CxPath::sGetDir(CxPath::sGetExe()) + CxConst::xSLASH + a_csFilePath;
    } else {
        _m_sFilePath = a_csFilePath;
    }

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxFileLog::sGetFilePath() const {
    /*DEBUG*/

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bWrite(
    const tchar_t *a_pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != a_pcszFormat, false);

    bool bRv = false;

    bRv = _bDeleteIfFull();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //time
    std::tstring_t sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::tstring_t sParam;
    va_list      palArgs;

    xVA_START(palArgs, a_pcszFormat);
    sParam = CxString::sFormatV(a_pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write to file
    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    CxFile sfFile;

    bRv = sfFile.bCreate(sGetFilePath(), CxFile::omAppend, false);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    int iRv = sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    /*DEBUG*/xASSERT_RET(iRv != CxFile::etError, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bClear() {
    bool bRv = false;

    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    bRv = CxFile::bClear(sGetFilePath());
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bDelete() {
    bool bRv = false;

    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    bRv = CxFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxFileLog::_bDeleteIfFull() {
    bool bRv = false;

    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    bRv = CxFile::bIsExists(sGetFilePath());
    xCHECK_RET(false == bRv, true);

    //-------------------------------------
    //delete log, if full
    ulong_t ulSize = static_cast<ulong_t>( CxFile::llGetSize(sGetFilePath()) );

    xCHECK_RET(ulSize < _m_ulMaxFileSizeBytes, true);

    bRv = CxFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
