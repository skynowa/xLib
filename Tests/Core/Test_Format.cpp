/**
 * \file   Test_Format.cpp
 * \brief  test Format
 */


#include "Test_Format.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Format)
//-------------------------------------------------------------------------------------------------
enum EnumTest
{
    etUnknown,
    etOne,
    etTwo
};

inline std::ostream &
operator << (
    std::ostream   &a_out,
    const EnumTest &a_value
)
{
    switch (a_value) {
    case etUnknown:
        a_out << xLEX_TO_STR(EnumTest::etUnknown);
        break;
    case etOne:
        a_out << xLEX_TO_STR(EnumTest::etOne);
        break;
    case etTwo:
        a_out << xLEX_TO_STR(EnumTest::etTwo);
        break;
    default:
        a_out << xT("???");
        xTEST(false);
        break;
    }

    return a_out;
}
//-------------------------------------------------------------------------------------------------
struct StructTest
{
    std::size_t a;
    std::string b;
    const char *c;
};

inline std::ostream &
operator << (
    std::ostream     &a_out,
    const StructTest &a_value
)
{
    a_out << xT("{");
    a_out << a_value.a << xT(", ") << a_value.b << xT(", ") << a_value.c;
    a_out << xT("}");

    return a_out;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Format::unit()
{
    xTEST_CASE("c_str")
    {
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

        std::ctstring_t data = xT("0A string2344565600");
        m_sRv = Format::c_str(xT("%s"), data.c_str());
        xTEST_EQ(m_sRv, data);

        std::ctstring_t big_data(4000, xT('q'));
        m_sRv = Format::c_str(xT("%s"), big_data.c_str());
        xTEST_EQ(m_sRv, big_data);

        // various string size
        for (size_t i = 1; i < 1024 * 2; ++ i) {
            std::ctstring_t data(i, xT('s'));

            m_sRv = Format::c_str(xT("%s"), data.c_str());
            xTEST_EQ(m_sRv.size(), data.size());
            xTEST_EQ(m_sRv,        data);
        }
    }

    xTEST_CASE("c_strV")
    {
        // TEST: Format::c_strV()
    }

    xTEST_CASE("bool")
    {
        cbool_t value1 = false;
        cbool_t value2 = true;

        m_sRv = Format::str(xT("{},{}"), value1, value2);
        xTEST_EQ(m_sRv, std::tstring_t(xT("false,true")));
    }

    xTEST_CASE("char")
    {
        const char value = 'a';

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("a")));
    }

    xTEST_CASE("wchar_t")
    {
        Data2<wchar_t, std::tstring_t> data[] =
        {
            {L'\n', xT("?")},
            {L'a',  xT("a")},
            {L'聞', xT("?")}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

    xTEST_CASE("unsigned char")
    {
        cuchar_t value = 'b';

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("b")));
    }

    xTEST_CASE("short")
    {
        cshort_t value = -10;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-10")));
    }

    xTEST_CASE("unsigned short")
    {
        cushort_t value = 10;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("10")));
    }

    xTEST_CASE("int")
    {
        cint_t value = -111;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-111")));
    }

    xTEST_CASE("unsigned int")
    {
        cuint_t value = 111U;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("111")));
    }

    xTEST_CASE("long")
    {
        clong_t value = -222L;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-222")));
    }

    xTEST_CASE("unsigned long")
    {
        culong_t value = 222UL;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("222")));
    }

    xTEST_CASE("long long")
    {
        clonglong_t value = -333LL;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("-333")));
    }

    xTEST_CASE("unsigned long long")
    {
        culonglong_t value = 333ULL;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("333")));
    }

    xTEST_CASE("float")
    {
        cfloat_t value = 444.01f;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("444.01")));
    }

    xTEST_CASE("double")
    {
        cdouble_t value = 555.0202f;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("555.0202")));
    }

    xTEST_CASE("long double")
    {
        clongdouble_t value = 666.0L;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("666.0")));
    }

    xTEST_CASE("void *")
    {
        Data2<cvoid_t *, std::tstring_t> data[] =
        {
            {(cvoid_t *)0x7fff0fd3e100, xT("0x7fff0fd3e100")},
            {(cvoid_t *)xPTR_NULL,      xT("null")}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

#if xOPTION_CPP11
    xTEST_CASE("std::nullptr_t")
    {
        std::nullptr_t value = nullptr;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("nullptr")));
    }
#endif

    xTEST_CASE("std::ptrdiff_t")
    {
        Data2<std::ptrdiff_t, std::tstring_t> data[] =
        {
            {123, xT("123")},
            {0,   xT("0")}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

    xTEST_CASE("char *")
    {
        Data2<const char *, std::tstring_t> data[] =
        {
            {"bbb",                   xT("bbb")},
            {(const char *)xPTR_NULL, xT("null")}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

    xTEST_CASE("wchar_t *")
    {
        Data2<const wchar_t *, std::tstring_t> data[] =
        {
            {L"bbb",                     xT("bbb")},
            {(const wchar_t *)xPTR_NULL, xT("null")}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

    xTEST_CASE("std::wstring")
    {
        Data2<std::wstring, std::tstring_t> data[] =
        {
            {L"dddфывff", xT("ddd???ff")},
            {L"\n",       xT("?")},
            {L"a",        xT("a")},
            {L"聞",       xT("?")}
        };

        xFOR_ARRAY(i, data) {
            m_sRv = Format::str(xT("{}"), data[i].test);
            xTEST_EQ(m_sRv, data[i].expect);
        }
    }

    xTEST_CASE("std::string_t")
    {
        const std::string value("aaa");

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("aaa")));
    }

    xTEST_CASE("std::ustring_t")
    {
        std::custring_t value(10, 'z');

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("zzzzzzzzzz")));
    }

    xTEST_CASE("std::pair")
    {
        std::pair<int, std::tstring_t> value(999, xT("ddd???FF"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{999, ddd???FF}")));
    }

    xTEST_CASE("std::vector")
    {
        std::vec_tstring_t value;
        value.push_back(xT("aa"));
        value.push_back(xT("bbb"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{aa, bbb}")));
    }

    xTEST_CASE("std::list")
    {
        std::list_tstring_t value;
        value.push_back(xT("aa"));
        value.push_back(xT("bbb"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{aa, bbb}")));
    }

    xTEST_CASE("std::set")
    {
        std::set<long_t> value;
        value.insert(0);
        value.insert(1);
        value.insert(1);
        value.insert(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{0, 1, 2}")));
    }

    xTEST_CASE("std::multiset")
    {
        std::multiset<long_t> value;
        value.insert(0);
        value.insert(1);
        value.insert(1);
        value.insert(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{0, 1, 1, 2}")));
    }

    xTEST_CASE("std::map")
    {
        std::map<std::tstring_t, int> value;
        value[xT("0")] = 3;
        value[xT("1")] = 4;
        value[xT("1")] = 5;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{{0, 3}, {1, 5}}")));
    }

    xTEST_CASE("std::multimap")
    {
        std::pair<int, std::tstring_t> p1(0, xT("aa"));
        std::pair<int, std::tstring_t> p2(1, xT("bbb"));
        std::pair<int, std::tstring_t> p3(1, xT("bbb"));

        std::multimap<int, std::tstring_t> value;
        value.insert(p1);
        value.insert(p2);
        value.insert(p3);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{{0, aa}, {1, bbb}, {1, bbb}}")));
    }

    xTEST_CASE("enum")
    {
        EnumTest value0 = etUnknown;
        EnumTest value1 = etOne;
        EnumTest value2 = etTwo;

        m_sRv = Format::str(xT("{}, {}, {}"), etUnknown, etOne, etTwo);
        xTEST_EQ(m_sRv, std::tstring_t(xT("EnumTest::etUnknown, EnumTest::etOne, EnumTest::etTwo")));
    }

    xTEST_CASE("struct")
    {
        StructTest value = {7, xT("std::string"), xT("c_str")};
        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{7, std::string, c_str}")));
    }

    xTEST_CASE("all")
    {
        bool               bValue = true;
        char               chValue = 'q';
        wchar_t            wcValue = 'w';
        unsigned char      ucValue = 'e';
        short              shValue = 2;
        unsigned short     usiValue = 3;
        int                iValue = 4;
        unsigned int       uiValue = 5;
        long               liValue = 6;
        unsigned long      ulValue = 7;
        long long          llValue = 8;
        unsigned long long ullValue = 9;
        float              fValue = 0.0f;
        double             dValue = 0.1f;
        long double        ldValue = 0.02f;
        void *             pvValue = (void *)0x7fff0fd3e100;
    #if xOPTION_CPP11
        std::nullptr_t     pValue = nullptr;
    #endif
        char *             pszValue = "aaa";
        wchar_t *          pwszValue = L"bbb";
        std::string        asValue = "ccc";
        std::wstring       wsValue = L"ddd";
        std::ustring_t     usValue = std::ustring_t(3, 'z');

        m_sRv = Format::str(xT("{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}"),
            bValue,
            chValue,
            wcValue,
            ucValue,
            shValue,
            usiValue,
            iValue,
            uiValue,
            liValue,
            ulValue,
            llValue,
            ullValue,
            fValue,
            dValue,
            ldValue,
            pvValue,
        #if xOPTION_CPP11
            pValue,
        #endif
            pszValue,
            pwszValue,
            asValue,
            wsValue,
            usValue);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{true, q, w, e, 2, 3, 4, 5, 6, 7, 8, 9, 0.0, 0.1, 0.02, 0x7fff0fd3e100, aaa, bbb, ccc, ddd, zzz}")));
    }

    xTEST_CASE("check params")
    {
        m_sRv = Format::str(xT("{}{}{}"), 1, 35L);
        xTEST_EQ(m_sRv, std::tstring_t(xT("135")));
    }
    return true;
}
//-------------------------------------------------------------------------------------------------
