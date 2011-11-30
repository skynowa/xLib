/**
 * \file  CxFileLog.cpp
 * \brief logging to file
 */


#include <xLib/Log/CxFileLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if xOS_ENV_WIN
    #include <xLib/Sync/CxAutoMutex.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFileLog::CxFileLog(
    const ulong_t culMaxFileSizeBytes
) :
    _m_sFilePath         (),
    _m_ulMaxFileSizeBytes(culMaxFileSizeBytes)
    #if xTODO
        CxAutoMutex
    #endif
{
    /*DEBUG*/xASSERT_DO(true        == _m_sFilePath.empty(), return);
    /*DEBUG*/xASSERT_DO(lsLimitSize >  lsDefaultMaxSize,     return);
	/*DEBUG*/xASSERT_DO(lsLimitSize >  culMaxFileSizeBytes,  return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxFileLog::~CxFileLog() {

}
//---------------------------------------------------------------------------
bool
CxFileLog::bSetFilePath(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    if (std::tstring_t::npos == csFilePath.find(CxConst::xSLASH)) {
        _m_sFilePath = CxPath::sGetDir(CxPath::sGetExe()) + CxConst::xSLASH + csFilePath;
    } else {
        _m_sFilePath = csFilePath;
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
    const tchar_t *pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, false);

    bool bRes = false;

    bRes = _bDeleteIfFull();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    //-------------------------------------
    //time
    std::tstring_t sTime;
    sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::tstring_t sParam;
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

    bRes = sfFile.bCreate(sGetFilePath(), CxFile::omAppend, false);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    int iRes = sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    /*DEBUG*/xASSERT_RET(iRes != CxFile::etError, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bClear() {
    bool bRes = false;

    #if xTODO
        CxAutoMutex SL(_m_mtFile);
    #endif

    bRes = CxFile::bClear(sGetFilePath());
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bDelete() {
    bool bRes = false;

    #if xTODO
        CxAutoMutex SL(_m_mtFile);
    #endif

    bRes = CxFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(false != bRes, false);

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
    bool bRes = false;

    #if xTODO
        CxAutoMutex SL(_m_mtFile);
    #endif

    bRes = CxFile::bIsExists(sGetFilePath());
    xCHECK_RET(false == bRes, true);

    //-------------------------------------
    //delete log, if full
    ulong_t ulSize = static_cast<ulong_t>( CxFile::liGetSize(sGetFilePath()) );

    xCHECK_RET(ulSize < _m_ulMaxFileSizeBytes, true);

    bRes = CxFile::bDelete(sGetFilePath());
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
