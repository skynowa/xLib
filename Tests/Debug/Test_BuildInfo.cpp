/**
 * \file   Test_BuildInfo.cpp
 * \brief  test BuildInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_BuildInfo)
//---------------------------------------------------------------------------
/* virtual */
bool_t
Test_BuildInfo::unit()
{
	BuildInfo info;

    xTEST_CASE("isRelease")
    {
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
        m_sRv = info.datetime();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("langStandart")
    {
        m_sRv = info.langStandart();
        // LogCout() << xTRACE_VAR(m_sRv);
        // LogCout() << xTRACE_VAR(__STDC_VERSION__);
        xTEST(!m_sRv.empty());
        xTEST_EQ(m_sRv, xT("C89, C++20"));
    }

    xTEST_CASE("osEnvironment")
    {
        m_sRv = info.osEnvironment();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("os")
    {
        m_sRv = info.os();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("arch")
    {
        m_sRv = info.arch();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("bitsArch")
    {
        m_sRv = info.bitsArch();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("compiler")
    {
        m_sRv = info.compiler();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("compilerFlags")
    {
        m_sRv = info.compilerFlags();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("libs")
    {
        m_sRv = info.libs();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("isUnicodeEncoding")
    {
        m_bRv = info.isUnicodeEncoding();
	#if xUNICODE
		xTEST(m_bRv);
	#else
		xTEST(!m_bRv);
	#endif
    }

    xTEST_CASE("stdLibC")
    {
        m_sRv = info.stdLibC();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("stdLibCpp")
    {
        m_sRv = info.stdLibCpp();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("qt")
    {
        m_sRv = info.qt();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xlibVersion")
    {
        m_sRv = info.xlibVersion();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xlibBinaryType")
    {
        m_sRv = info.xlibBinaryType();
        xTEST_DIFF(m_sRv, std::tstring_t(xUNKNOWN_CSTRING));
    }

    xTEST_CASE("xlibBuildType")
    {
        m_sRv = info.xlibBuildType();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("cmake")
    {
        m_sRv = info.cmake();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//---------------------------------------------------------------------------
