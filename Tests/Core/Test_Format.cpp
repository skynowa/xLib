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
    xTEST_CASE("c_str")
    {
        std::tstring_t sData;

        m_sRv = Format::c_str(xT("qqqq-wwww [%i]"), 1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = Format::c_str(xT("qqqq-wwww [%f]"), 1000.0);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = Format::c_str(xT("qqqq-wwww [%s]"), xT("1000"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = Format::c_str(xT("qqqq-wwww [%i]"), -1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [-1000]")));

        m_sRv = Format::c_str(xT("Characters: %c %c"), xT('a'), 65);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Characters: a A")));

        m_sRv = Format::c_str(xT("Decimals: %d %ld"), 1977, 650000L);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Decimals: 1977 650000")));

        m_sRv = Format::c_str(xT("Preceding with blanks: %10d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with blanks:       1977")));

        m_sRv = Format::c_str(xT("Preceding with zeros: %010d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with zeros: 0000001977")));

        m_sRv = Format::c_str(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Some different radixes: 100 64 144 0x64 0144")));

        m_sRv = Format::c_str(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = Format::c_str(xT("Width trick: %*d"), 5, 10);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Width trick:    10")));

        sData = xT("0A string2344565600");
        m_sRv = Format::c_str(xT("%s"), sData.c_str());
        xTEST_EQ(m_sRv, sData);

        sData = xT("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
        m_sRv = Format::c_str(xT("%s"), sData.c_str());
        xTEST_EQ(sData, m_sRv);

        //various string size
        {
            for (size_t i = 1; i < 1024 * 2; ++ i) {
                std::tstring_t _sData(i, xT('s'));

                std::tstring_t sRv = Format::c_str(xT("%s"), _sData.c_str());
                //xSTD_COUT("_sData (" << _sData.size() << ") = " << _sData << "\nsRes (" << sRv.size() << ") = " << sRv);

                xTEST_EQ(sRv.size(), _sData.size());
                xTEST_EQ(sRv,        _sData);
            }
        }
    }

    xTEST_CASE("formatV")
    {
        // TEST: Format::c_strV()
    }

    xTEST_CASE("cbool_t")
    {
        cbool_t value1 = false;
        cbool_t value2 = true;

        m_sRv = Format::str(xT("{},{}"), value1, value2);
        xTEST_EQ(m_sRv, std::tstring_t(xT("false,true")));
    }

    xTEST_CASE("ctchar_t")
    {
        ctchar_t value = xT('a');

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("a")));
    }

    xTEST_CASE("cuchar_t")
    {
        cuchar_t value = 'b';

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("b")));
    }

    xTEST_CASE("cshort_t")
    {
        cshort_t value = -10;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-10")));
    }

    xTEST_CASE("cushort_t")
    {
        cushort_t value = 10;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("10")));
    }

    xTEST_CASE("cint_t")
    {
        cint_t value = -111;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-111")));
    }

    xTEST_CASE("cuint_t")
    {
        cuint_t value = 111U;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("111")));
    }

    xTEST_CASE("clong_t")
    {
        clong_t value = -222L;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-222")));
    }

    xTEST_CASE("culong_t")
    {
        culong_t value = 222UL;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("222")));
    }

    xTEST_CASE("clonglong_t")
    {
        clonglong_t value = -333LL;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-333")));
    }

    xTEST_CASE("culonglong_t")
    {
        culonglong_t value = 333ULL;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("333")));
    }

    xTEST_CASE("cfloat_t")
    {
        cfloat_t value = 444.0f;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("444.0000000")));
    }

    xTEST_CASE("cdouble_t")
    {
        cdouble_t value = 555.0f;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("555.0000000000000000")));
    }

    xTEST_CASE("clongdouble_t")
    {
        clongdouble_t value = 666.0L;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("666.0000000000000000000")));
    }

    xTEST_CASE("cvoid_t *")
    {
        Data2<cvoid_t *, std::tstring_t> data[] =
        {
            {(cvoid_t *)0x7fff0fd3e100, std::tstring_t(xT("0x7fff0fd3e100"))},
            {(cvoid_t *)xPTR_NULL,      std::tstring_t(xT("null"))}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

    xTEST_CASE("std::ctstring_t")
    {
        std::ctstring_t value(xT("aaa"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("aaa")));
    }

    xTEST_CASE("ctchar_t *")
    {
        ctchar_t * value = xT("bbb");

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("bbb")));
    }

    xTEST_CASE("std::vec_tstring_t")
    {
        std::vec_tstring_t value;
        value.push_back(xT("aa"));
        value.push_back(xT("bbb"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{aa, bbb}")));
    }

    xTEST_CASE("std::list_tstring_t")
    {
        std::list_tstring_t value;
        value.push_back(xT("aa"));
        value.push_back(xT("bbb"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{aa, bbb}")));
    }

    xTEST_CASE("std::map_tstring_t")
    {
        std::map_tstring_t value;
        value[xT("0")] = xT("aa");
        value[xT("1")] = xT("bbb");

        m_sRv = Format::str(xT("{}"), value);
        // xTEST_EQ(m_sRv, std::tstring_t(xT("{aa, bbb}")));

        Trace() << xTRACE_VAR(m_sRv);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
