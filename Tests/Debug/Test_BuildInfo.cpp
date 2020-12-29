/**
 * \file   Test_BuildInfo.cpp
 * \brief  test BuildInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_BuildInfo)
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
            xTEST(m_bRv);
        #else
            xTEST(!m_bRv);
        #endif

        #if xBUILD_DEBUG
            xTEST(!m_bRv);
        #else
            xTEST(m_bRv);
        #endif
    }

    xTEST_CASE("datetime")
    {
        BuildInfo info;

        m_sRv = info.datetime();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("langStandart")
    {
        BuildInfo info;

        m_sRv = info.langStandart();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("osEnvironment")
    {
        BuildInfo info;

        m_sRv = info.osEnvironment();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("os")
    {
        BuildInfo info;

        m_sRv = info.os();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("arch")
    {
        BuildInfo info;

        m_sRv = info.arch();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("bitsArch")
    {
        BuildInfo info;

        m_sRv = info.bitsArch();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("compiler")
    {
        BuildInfo info;

        m_sRv = info.compiler();
        xTEST(!m_sRv.empty());
    }


    xTEST_CASE("compilerFlags")
    {
        BuildInfo info;

        m_sRv = info.compilerFlags();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("libs")
    {
        BuildInfo info;

        m_sRv = info.libs();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("isUnicodeEncoding")
    {
        BuildInfo info;

        m_bRv = info.isUnicodeEncoding();
        #if xUNICODE
            xTEST(m_bRv);
        #else
            xTEST(!m_bRv);
        #endif
    }

    xTEST_CASE("stdLibC")
    {
        BuildInfo info;

        m_sRv = info.stdLibC();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("stdLibCpp")
    {
        BuildInfo info;

        m_sRv = info.stdLibCpp();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("qt")
    {
        BuildInfo info;

        m_sRv = info.qt();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xlibVersion")
    {
        BuildInfo info;

        m_sRv = info.xlibVersion();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xlibBinaryType")
    {
        BuildInfo info;

        m_sRv = info.xlibBinaryType();
        xTEST_DIFF(m_sRv, std::tstring_t(xUNKNOWN_CSTRING));
    }

    xTEST_CASE("xlibBuildType")
    {
        BuildInfo info;

        m_sRv = info.xlibBuildType();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("cmake")
    {
        BuildInfo info;

        m_sRv = info.cmake();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//---------------------------------------------------------------------------
