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
    xTEST_CASE("cbool_t")
    {
        cbool_t value = false;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("0")));
    }

    xTEST_CASE("ctchar_t")
    {
        ctchar_t value = xT('a');

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("a")));
    }

    xTEST_CASE("cuchar_t")
    {
        cuchar_t value = 'b';

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("b")));
    }

    xTEST_CASE("cshort_t")
    {
        cshort_t value = -10;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-10")));
    }

    xTEST_CASE("cushort_t")
    {
        cushort_t value = 10;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("10")));
    }

    xTEST_CASE("cint_t")
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

    xTEST_CASE("clong_t")
    {
        clong_t value = -222L;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-222")));
    }

    xTEST_CASE("culong_t")
    {
        culong_t value = 222UL;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("222")));
    }

    xTEST_CASE("clonglong_t")
    {
        clonglong_t value = -333LL;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-333")));
    }

    xTEST_CASE("culonglong_t")
    {
        culonglong_t value = 333ULL;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("333")));
    }

    xTEST_CASE("cfloat_t")
    {
        cfloat_t value = 444.0f;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("444.00000")));
    }

    xTEST_CASE("cdouble_t")
    {
        cdouble_t value = 555.0f;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("555.0000000000")));
    }

    xTEST_CASE("clongdouble_t")
    {
        clongdouble_t value = 666.0L;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("666.00000000000000000000")));
    }

    xTEST_CASE("cvoid_t *")
    {
        cvoid_t * value = (cvoid_t *)777;

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("0x309")));
    }

    xTEST_CASE("std::ctstring_t")
    {
        std::ctstring_t value = std::ctstring_t(xT("aaa"));

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("aaa")));
    }

    xTEST_CASE("ctchar_t *")
    {
        ctchar_t * value = xT("bbb");

        m_sRv = Format::format(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("bbb")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
