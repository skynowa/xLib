/**
 * \file  CxFileLog.cpp
 * \brief logging to file
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if xOS_ENV_WIN
    #include <xLib/Sync/CxAutoIpcMutex.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxFileLog::CxFileLog() :
    _filePath        (),
    _maxFileSizeBytes(lsDefaultMb)
{
    xTEST_EQ(true, _filePath.empty());
}
//-------------------------------------------------------------------------------------------------
inline
CxFileLog::CxFileLog(
    std::csize_t &a_maxFileSizeBytes
) :
    _filePath        (),
    _maxFileSizeBytes(a_maxFileSizeBytes)
{
    xTEST_EQ(true, _filePath.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxFileLog::~CxFileLog()
{
    write(xT("%s"), _oss.str().c_str());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileLog::setFilePath(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(false, a_filePath.empty());

    if (std::tstring_t::npos == a_filePath.find(CxConst::slash())) {
        _filePath = CxPath(CxPath::exe()).dir() + CxConst::slash() + a_filePath;
    } else {
        _filePath = a_filePath;
    }
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFileLog::filePath() const
{
    return _filePath;
}
//-------------------------------------------------------------------------------------------------
template<class T>
inline CxFileLog &
CxFileLog::operator << (const T &valueT)
{
    _oss << valueT;
    return *this;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxFileLog::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),       return);
    xCHECK_DO(a_format == NULL,   return);
    xCHECK_DO(filePath().empty(), return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = CxString::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxFileLog::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),       return);
    xCHECK_DO(filePath().empty(), return);

    _removeIfFull();

    // datetime
    std::tstring_t time;
    time = CxDateTime::current().format(xT("%Y-%m-%d %H:%M:%S"));

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = CxString::formatV(a_format, args);
        xVA_END(args);

        if (a_level != lvPlain) {
            msg = _levelToString(a_level) + xT(": ") + msg;
        }
    }

    // write
    {
        CxFile file;
        file.create(filePath(), CxFile::omAppend, false);
        int_t iRv = file.write(xT("[%s] %s\n"), time.c_str(), msg.c_str());
        xTEST_DIFF(- 1, iRv);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileLog::clear() const
{
    CxFile::clear(filePath());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileLog::remove() const
{
    CxFile::remove(filePath());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxFileLog::_removeIfFull() const
{
    bool_t bRv = CxFile::isExists(filePath());
    xCHECK_DO(!bRv, return);

    // remove log, if full
    xCHECK_DO(CxFile::size( filePath() ) < static_cast<longlong_t>(_maxFileSizeBytes), return);

    CxFile::remove(filePath());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
