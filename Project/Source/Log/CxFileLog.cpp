/**
 * \file  CxFileLog.cpp
 * \brief logging to file
 */


#include <xLib/Log/CxFileLog.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if xOS_ENV_WIN
    #include <xLib/Sync/CxAutoIpcMutex.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxFileLog::CxFileLog(
    culong_t &a_maxFileSizeBytes
) :
    _filePath         (),
    _maxFileSizeBytes(a_maxFileSizeBytes)
    #if xTODO
        CxAutoIpcMutex
    #endif
{
    xTEST_EQ(true, _filePath.empty());
    xTEST_GR(lsLimitSize, lsDefaultMaxSize);
    xTEST_GR(static_cast<ulong_t>( lsLimitSize ), a_maxFileSizeBytes);
}
//------------------------------------------------------------------------------
/* virtual */
CxFileLog::~CxFileLog()
{
}
//------------------------------------------------------------------------------
void_t
CxFileLog::setFilePath(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    if (std::tstring_t::npos == a_filePath.find(CxConst::xSLASH)) {
        _filePath = CxPath(CxPath::exe()).dir() + CxConst::xSLASH + a_filePath;
    } else {
        _filePath = a_filePath;
    }
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxFileLog::filePath() const
{
    return _filePath;
}
//------------------------------------------------------------------------------
void_t
CxFileLog::write(
    ctchar_t *a_format, ...
)
{
    xTEST_PTR(a_format);

    _removeIfFull();

    //-------------------------------------
    //time
    std::tstring_t sTime;
    sTime = CxDateTime::current().format(CxDateTime::ftTime);

    //-------------------------------------
    //comment
    std::tstring_t sParam;
    va_list        palArgs;

    xVA_START(palArgs, a_format);
    sParam = CxString::formatV(a_format, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write to file
    #if xTODO
        CxAutoIpcMutex SL(_mutex);
    #endif

    CxFile sfFile;

    sfFile.create(filePath(), CxFile::omAppend, false);

    int_t iRv = sfFile.write(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());
    xTEST_DIFF(- 1, iRv);
}
//------------------------------------------------------------------------------
void_t
CxFileLog::clear()
{
    #if xTODO
        CxAutoIpcMutex SL(_mutex);
    #endif

    CxFile::clear(filePath());
}
//------------------------------------------------------------------------------
void_t
CxFileLog::remove()
{
    #if xTODO
        CxAutoIpcMutex SL(_mutex);
    #endif

    CxFile::remove(filePath());
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxFileLog::_removeIfFull()
{
    #if xTODO
        CxAutoIpcMutex SL(_mutex);
    #endif

    bool_t bRv = CxFile::isExists(filePath());
    xCHECK_DO(!bRv, return);

    //-------------------------------------
    // remove log, if full
    ulong_t ulSize = static_cast<ulong_t>( CxFile::size(filePath()) );

    xCHECK_DO(ulSize < _maxFileSizeBytes, return);

    CxFile::remove(filePath());
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
