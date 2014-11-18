/**
 * \file   FileLog.inl
 * \brief  logging to file
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "FileLog.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/Sync/AutoIpcMutex.h>


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
FileLog::FileLog() :
    _filePath        (),
    _maxFileSizeBytes(lsDefaultMb)
{
    xTEST_EQ(_filePath.empty(), true);
}
//-------------------------------------------------------------------------------------------------
xINLINE
FileLog::FileLog(
    std::csize_t &a_maxFileSizeBytes
) :
    _filePath        (),
    _maxFileSizeBytes(a_maxFileSizeBytes)
{
    xTEST_EQ(_filePath.empty(), true);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
FileLog::~FileLog()
{
    write(xT("%s"), _oss.str().c_str());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileLog::setFilePath(
    std::ctstring_t &a_filePath
)
{
    xTEST_EQ(a_filePath.empty(), false);

    if (a_filePath.find(Const::slash()) == std::tstring_t::npos) {
        _filePath = Path(Path::exe()).dir() + Const::slash() + a_filePath;
    } else {
        _filePath = a_filePath;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
FileLog::filePath() const
{
    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
FileLog::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);
    xCHECK_DO(filePath().empty(),    return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = String::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
FileLog::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),       return);
    xCHECK_DO(filePath().empty(), return);

    _removeIfFull();

    // datetime
    std::tstring_t time;
    time = DateTime::current().format(xT("%Y-%m-%d %H:%M:%S"));

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = String::formatV(a_format, args);
        xVA_END(args);

        if (a_level != lvPlain) {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    // write
    {
        File file(false);
        file.create(filePath(), File::omAppend);
        int_t iRv = file.write(xT("[%s] %s\n"), time.c_str(), msg.c_str());
        xTEST_DIFF(iRv, - 1);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileLog::clear() const
{
    File::clear(filePath());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileLog::remove() const
{
    File::remove(filePath());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileLog::_removeIfFull() const
{
    bool_t bRv = File::isExists(filePath());
    xCHECK_DO(!bRv, return);

    // remove log, if full
    xCHECK_DO(File::size( filePath() ) < static_cast<longlong_t>(_maxFileSizeBytes), return);

    File::remove(filePath());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
