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
    const ulong_t &a_culMaxFileSizeBytes
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
void
CxFileLog::vSetFilePath(
    const std::tstring_t &a_csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, a_csFilePath.empty());

    if (std::tstring_t::npos == a_csFilePath.find(CxConst::xSLASH)) {
        _m_sFilePath = CxPath::sDir(CxPath::sExe()) + CxConst::xSLASH + a_csFilePath;
    } else {
        _m_sFilePath = a_csFilePath;
    }
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxFileLog::sFilePath() const {
    /*DEBUG*/

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
void
CxFileLog::vWrite(
    const tchar_t *a_pcszFormat, ...
)
{
    /*DEBUG*/xTEST_PTR(a_pcszFormat);

    _vDeleteIfFull();

    //-------------------------------------
    //time
    std::tstring_t sTime;
    sTime = CxDateTime::dtCurrent().sFormat(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::tstring_t sParam;
    va_list        palArgs;

    xVA_START(palArgs, a_pcszFormat);
    sParam = CxString::sFormatV(a_pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write to file
    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    CxFile sfFile;

    sfFile.vCreate(sFilePath(), CxFile::omAppend, false);

    int iRv = sfFile.iWrite(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    /*DEBUG*/xTEST_DIFF(iRv, static_cast<int>( CxFile::etError ));
}
//---------------------------------------------------------------------------
void
CxFileLog::vClear() {
    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    CxFile::vClear(sFilePath());
}
//---------------------------------------------------------------------------
void
CxFileLog::vDelete() {
    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    CxFile::vDelete(sFilePath());
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxFileLog::_vDeleteIfFull() {
    #if xTODO
        CxAutoIpcMutex SL(_m_mtFile);
    #endif

    bool bRv = CxFile::bIsExists(sFilePath());
    xCHECK_DO(false == bRv, return);

    //-------------------------------------
    //delete log, if full
    ulong_t ulSize = static_cast<ulong_t>( CxFile::llSize(sFilePath()) );

    xCHECK_DO(ulSize < _m_ulMaxFileSizeBytes, return);

    CxFile::vDelete(sFilePath());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
