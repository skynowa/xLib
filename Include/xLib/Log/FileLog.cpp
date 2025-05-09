/**
 * \file   FileLog.cpp
 * \brief  logging to file
 */


#include "FileLog.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Sync/AutoIpcMutex.h>


namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileLog::FileLog() :
    _fileSizeMaxBytes( static_cast<std::size_t>(LogSizes::DefaultMb) )
{
    xTEST(_filePath.empty());
}
//-------------------------------------------------------------------------------------------------
FileLog::FileLog(
    cLogSizes a_fileSizeMaxBytes
) :
    _fileSizeMaxBytes( static_cast<std::size_t>(a_fileSizeMaxBytes) )
{
    xTEST(_filePath.empty());
}
//-------------------------------------------------------------------------------------------------
FileLog::FileLog(
    std::csize_t a_fileSizeMaxBytes
) :
    _fileSizeMaxBytes(a_fileSizeMaxBytes)
{
    xTEST(_filePath.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
FileLog::~FileLog()
{
    write(xT("%s"), _oss.str().c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
FileLog::setFilePath(
    std::ctstring_t &a_filePath ///< full path or name
)
{
    xTEST(!a_filePath.empty());

    if (a_filePath.find( Const::slash() ) == std::tstring_t::npos) {
        _filePath = Path::exe().dir() + Const::slash() + a_filePath;
    } else {
        _filePath = a_filePath;
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
FileLog::filePath() const
{
    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
FileLog::write(
    cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),        return);
    xCHECK_DO(a_format == nullptr, return);
    xCHECK_DO(filePath().empty(),  return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = FormatC::strV(a_format, args);
    xVA_END(args);

    write(Level::Trace, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
FileLog::write(
    cLevel        a_level,
    cptr_ctchar_t a_format, ...
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
        msg = FormatC::strV(a_format, args);
        xVA_END(args);

        if (a_level != Level::Trace) {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    // write
    {
        FileIO file(filePath());
        file.open(FileIO::OpenMode::Append, false);
        int_t iRv = file.write(xT("[%s] %s\n"), time.c_str(), msg.c_str());
        xTEST_DIFF(iRv, - 1);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
FileLog::clear() const
{
    FileIO file(filePath());
    file.open(FileIO::OpenMode::Write);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
void_t
FileLog::remove() const
{
    File(filePath()).remove();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FileLog::_removeIfFull() const
{
    bool_t bRv = FileInfo( filePath() ).isExists();
    xCHECK_DO(!bRv, return);

    // remove log, if full
    xCHECK_DO(FileInfo(filePath()).size() < static_cast<longlong_t>(_fileSizeMaxBytes), return);

    remove();
}
//-------------------------------------------------------------------------------------------------

} // namespace
