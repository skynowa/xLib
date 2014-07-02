/**
 * \file   Test_FileLog.cpp
 * \brief
 */


#include <Test/Log/Test_FileLog.h>

#include <xLib/Core/Const.h>
#include <xLib/IO/File.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_FileLog::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = tempDirPath() + Const::slash() + xT("FileLog.log");

    FileLog log(FileLog::lsDefaultMb);

    xTEST_CASE("FileLog::setFilePath filePath", a_caseLoops)
    {
        log.setFilePath(filePath);

        m_sRv = log.filePath();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("FileLog::write", a_caseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            log.write(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_LESS(0LL, File::size( log.filePath()) );
        }
    }

    xTEST_CASE("FileLog::write(cExLevel &level, ...)", a_caseLoops)
    {
        log.write(IxLog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvUnknown),  12345);
        log.write(IxLog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvEmerg),    12345);
        log.write(IxLog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvAlert),    12345);
        log.write(IxLog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvCritical), 12345);
        log.write(IxLog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvError),    12345);
        log.write(IxLog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvWarning),  12345);
        log.write(IxLog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvNotice),   12345);
        log.write(IxLog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvInfo),     12345);
        log.write(IxLog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvDebug),    12345);
        log.write(IxLog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvPlain),    12345);
    }

    xTEST_CASE("FileLog::clear", a_caseLoops)
    {
        log.clear();
        xTEST_EQ(0LL, File::size( log.filePath()) );
    }

    xTEST_CASE("FileLog::remove", a_caseLoops)
    {
        log.remove();
        xTEST_EQ(false, File::isExists( log.filePath()) );
    }
}
//-------------------------------------------------------------------------------------------------
