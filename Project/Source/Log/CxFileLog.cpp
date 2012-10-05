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
    /*DEBUG*/xTEST_GR(lsLimitSize, lsDefaultMaxSize);
    /*DEBUG*/xTEST_GR(static_cast<ulong_t>( lsLimitSize ), a_culMaxFileSizeBytes);
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
    /*DEBUG*/xTEST_EQ(false, a_csFilePath.empty());

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
    /*DEBUG*/xTEST_PTR(a_pcszFormat);

    bool bRv = false;

    bRv = _bDeleteIfFull();
    /*DEBUG*/xTEST_EQ(true, bRv);

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

    sfFile.vCreate(sGetFilePath(), CxFile::omAppend, false);

    int iRv = sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    /*DEBUG*/xTEST_DIFF(iRv, static_cast<int>( CxFile::etError ));

    return true;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bClear() {
    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    CxFile::vClear(sGetFilePath());

    return true;
}
//---------------------------------------------------------------------------
bool
CxFileLog::bDelete() {
    bool bRv = false;

    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    CxFile::vDelete(sGetFilePath());

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

    CxFile::vDelete(sGetFilePath());

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
