/**
 * \file   Test_Format.cpp
 * \brief  test Format
 */


#include "Test_Format.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Format)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Format::unit()
{
    xTEST_CASE("Format")
    {
        cbool_t value = false;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("0")));
    }

    xTEST_CASE("Format")
    {
        ctchar_t value = xT('a');

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("a")));
    }

    xTEST_CASE("Format")
    {
        cuchar_t value = 'b';

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("b")));
    }

    xTEST_CASE("Format")
    {
        cshort_t value = -10;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-10")));
    }

    xTEST_CASE("Format")
    {
        cushort_t value = 10;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("10")));
    }

    xTEST_CASE("Format")
    {
        cint_t value = -111;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-111")));
    }

    xTEST_CASE("Format")
    {
        cuint_t value = 111U;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("111")));
    }

    xTEST_CASE("Format")
    {
        clong_t value = -222L;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-222")));
    }

    xTEST_CASE("Format")
    {
        culong_t value = 222UL;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("222")));
    }

    xTEST_CASE("Format")
    {
        clonglong_t value = -333LL;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-333")));
    }

    xTEST_CASE("Format")
    {
        culonglong_t value = 333ULL;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("333")));
    }

    xTEST_CASE("Format")
    {
        cfloat_t value = 444.0f;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("444.00000")));
    }

    xTEST_CASE("Format")
    {
        cdouble_t value = 555.0f;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("555.0000000000")));
    }

    xTEST_CASE("Format")
    {
        clongdouble_t value = 666.0L;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("666.00000000000000000000")));
    }

    xTEST_CASE("Format")
    {
        cvoid_t * value = (cvoid_t *)777;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("0x309")));
    }

    xTEST_CASE("Format")
    {
        std::ctstring_t value = std::ctstring_t(xT("aaa"));

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("aaa")));
    }

    xTEST_CASE("Format")
    {
        ctchar_t * value = xT("bbb");

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("bbb")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
