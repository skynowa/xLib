/**
 * \file   Test_BuildInfo.cpp
 * \brief  test BuildInfo
 */


#include "Test_BuildInfo.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_BuildInfo)
//---------------------------------------------------------------------------
/* virtual */
bool_t
Test_BuildInfo::unit()
{
    xTEST_CASE("isRelease")
    {
        BuildInfo info;

        m_bRv = info.isRelease();
        #if defined(NDEBUG)
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif

        #if xBUILD_DEBUG
            xTEST_EQ(m_bRv, false);
        #else
            xTEST_EQ(m_bRv, true);
        #endif
    }

    xTEST_CASE("datetime")
    {
        BuildInfo info;

        m_sRv = info.datetime();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("langStandart")
    {
        BuildInfo info;

        m_sRv = info.langStandart();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("osEnvironment")
    {
        BuildInfo info;

        m_sRv = info.osEnvironment();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("os")
    {
        BuildInfo info;

        m_sRv = info.os();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("arch")
    {
        BuildInfo info;

        m_sRv = info.arch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("bitsArch")
    {
        BuildInfo info;

        m_sRv = info.bitsArch();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("compiler")
    {
        BuildInfo info;

        m_sRv = info.compiler();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("libs")
    {
        BuildInfo info;

        m_sRv = info.libs();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("compilerFlags")
    {
        BuildInfo info;

        m_sRv = info.compilerFlags();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("isUnicodeEncoding")
    {
        BuildInfo info;

        m_bRv = info.isUnicodeEncoding();
        #if xUNICODE
            xTEST_EQ(m_bRv, true);
        #else
            xTEST_EQ(m_bRv, false);
        #endif
    }

    xTEST_CASE("stdLibC")
    {
        BuildInfo info;

        m_sRv = info.stdLibC();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("stdLibCpp")
    {
        BuildInfo info;

        m_sRv = info.stdLibCpp();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("qt")
    {
        BuildInfo info;

        m_sRv = info.qt();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("xlibVersion")
    {
        BuildInfo info;

        m_sRv = info.xlibVersion();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("binaryType")
    {
        BuildInfo info;

        m_sRv = info.binaryType();
        xTEST_DIFF(m_sRv, std::tstring_t( xT("xUNKNOWN_CSTRING") ));
    }

    return true;
}
//---------------------------------------------------------------------------
