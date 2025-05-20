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
FileLog::FileLog(
    std::ctstring_t &a_filePath
) :
	FileLog(a_filePath, LogSizes::DefaultMb)
{
}
//-------------------------------------------------------------------------------------------------
FileLog::FileLog(
    std::ctstring_t &a_filePath,
    cLogSizes        a_fileSizeMaxBytes
) :
	FileLog(a_filePath, static_cast<std::size_t>(a_fileSizeMaxBytes))
{
}
//-------------------------------------------------------------------------------------------------
FileLog::FileLog(
    std::ctstring_t &a_filePath,
    std::csize_t     a_fileSizeMaxBytes
) :
    _filePath        (), // Set later
    _fileSizeMaxBytes(a_fileSizeMaxBytes)
{
    xTEST(_filePath.empty());

    if (a_filePath.find( Const::slash() ) == std::tstring_t::npos) {
        _filePath = Path::exe().dir() + Const::slash() + a_filePath;
    } else {
        _filePath = a_filePath;
    }
}
//-------------------------------------------------------------------------------------------------
/* virtual */
FileLog::~FileLog()
{
    write(xT("%s"), _oss.str().c_str());
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
    xCHECK_DO(_filePath.empty(),   return);

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
    xCHECK_DO(!isEnabled(),      return);
    xCHECK_DO(_filePath.empty(), return);

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

        if (a_level == ILog::Level::Trace) {
            // Skip
        } else {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    // write
    {
        FileIO file(_filePath);
        file.open(FileIO::OpenMode::Append, false);
        int_t iRv = file.write(xT("[%s] %s\n"), time.c_str(), msg.c_str());
        xTEST_DIFF(iRv, - 1);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
FileLog::clear() const
{
    FileIO file(_filePath);
    file.open(FileIO::OpenMode::Write);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
void_t
FileLog::remove() const
{
    File(_filePath).remove();
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
	FileInfo info(_filePath);

    bool_t bRv = info.isExists();
    xCHECK_DO(!bRv, return);

    // remove log, if full
    xCHECK_DO(info.size() < _fileSizeMaxBytes, return);

    remove();
}
//-------------------------------------------------------------------------------------------------

} // namespace
