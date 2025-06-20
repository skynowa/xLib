/**
 * \file   Test_Format.cpp
 * \brief  test Format
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Format)
//-------------------------------------------------------------------------------------------------
enum class EnumTest
{
    etUnknown,
    etOne,
    etTwo
};

template<class T>
T &
operator << (
    T              &a_out,
    const EnumTest &a_value
)
{
    switch (a_value) {
    case EnumTest::etUnknown:
        a_out << xLEX_TO_STR(etUnknown);
        break;
    case EnumTest::etOne:
        a_out << xLEX_TO_STR(etOne);
        break;
    case EnumTest::etTwo:
        a_out << xLEX_TO_STR(etTwo);
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

    void print(xl::core::OStream &a_os) const
    {
        a_os << xT("{");
        a_os << a << xT(", ") << b << xT(", ") << c;
        a_os << xT("}");
    }
};

std::ostream &
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
struct StructTest2
{
    std::size_t a;
    std::string b;
    const char *c;

    template<class T>
    void print(T &a_os) const
    {
		a_os << xT("{");
		a_os << a << xT(", ") << b << xT(", ") << c;
		a_os << xT("}");
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Format::unit()
{
#if 0
	#define Format Format_v1
#else
	#define Format Format
#endif

	std::ios_base::sync_with_stdio(false);

    xTEST_CASE("FormatC::str")
    {
        m_sRv = FormatC::str(xT("qqqq-wwww [%i]"), 1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = FormatC::str(xT("qqqq-wwww [%f]"), 1000.0);
        xTEST(!m_sRv.empty());

        m_sRv = FormatC::str(xT("qqqq-wwww [%s]"), xT("1000"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = FormatC::str(xT("qqqq-wwww [%i]"), -1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [-1000]")));

        m_sRv = FormatC::str(xT("Characters: %c %c"), xT('a'), 65);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Characters: a A")));

        m_sRv = FormatC::str(xT("Decimals: %d %ld"), 1977, 650000L);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Decimals: 1977 650000")));

        m_sRv = FormatC::str(xT("Preceding with blanks: %10d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with blanks:       1977")));

        m_sRv = FormatC::str(xT("Preceding with zeros: %010d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with zeros: 0000001977")));

        m_sRv = FormatC::str(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Some different radixes: 100 64 144 0x64 0144")));

        m_sRv = FormatC::str(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xTEST(!m_sRv.empty());

        m_sRv = FormatC::str(xT("Width trick: %*d"), 5, 10);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Width trick:    10")));

        std::ctstring_t data = xT("0A string2344565600");
        m_sRv = FormatC::str(xT("%s"), data.c_str());
        xTEST_EQ(m_sRv, data);

        std::ctstring_t big_data(4000, xT('q'));
        m_sRv = FormatC::str(xT("%s"), big_data.c_str());
        xTEST_EQ(m_sRv, big_data);

        // various string size
        for (size_t i = 1; i < 1024 * 2; ++ i) {
            std::ctstring_t data_(i, xT('s'));

            m_sRv = FormatC::str(xT("%s"), data_.c_str());
            xTEST_EQ(m_sRv.size(), data_.size());
            xTEST_EQ(m_sRv,        data_);
        }
    }

    xTEST_CASE("FormatC::strV")
    {
        // TEST: FormatC::strV()
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
            {L'\n', xT("<LF>")},
            {L'a',  xT("a")}
        #if xENV_WIN
        #if xUNICODE
            ,
            {L'聞', xT("<?>")}
        #endif
        #endif
        };

       for (const auto &i : data) {
            m_sRv = Format::str(xT("{}"), i.test);
            xTEST_EQ(m_sRv, i.expect);
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
        m_sRv.resize( std::tstring_t(xT("444.01")).size() );
        xTEST_EQ(m_sRv, std::tstring_t(xT("444.01")));
    }

    xTEST_CASE("double")
    {
        cdouble_t value = 555.0202f;

        m_sRv = Format::str(xT("{}"), value);
        m_sRv.resize( std::tstring_t(xT("555.0202")).size() );
        xTEST_EQ(m_sRv, std::tstring_t(xT("555.0202")));
    }

    xTEST_CASE("long double")
    {
        clongdouble_t value1 = 666.0010L;

        m_sRv = Format::str(xT("{}"), value1);
        m_sRv.resize( std::tstring_t(xT("666.001")).size() );
        xTEST_EQ(m_sRv, std::tstring_t(xT("666.001")));

        clongdouble_t value2 = 666.0;

        m_sRv = Format::str(xT("{}"), value2);
        m_sRv.resize( std::tstring_t(xT("666.0")).size() );
        xTEST_EQ(m_sRv, std::tstring_t(xT("666.0")));
    }

    xTEST_CASE("void *")
    {
        Data2<cptr_cvoid_t, std::tstring_t> data[] =
        {
            {(cptr_cvoid_t)0x7fff0fd3e100, xT("0x7fff0fd3e100")},
            {(cptr_cvoid_t)nullptr,      xT("null")}
        };

       for (const auto &i : data) {
            m_sRv = Format::str(xT("{}"), i.test);
            xTEST_EQ(m_sRv, i.expect);
        }
    }

    xTEST_CASE("std::ptrdiff_t")
    {
        Data2<std::ptrdiff_t, std::tstring_t> data[] =
        {
            {123, xT("123")},
            {0,   xT("0")}
        };

       for (const auto &i : data) {
            m_sRv = Format::str(xT("{}"), i.test);
            xTEST_EQ(m_sRv, i.expect);
        }
    }

    xTEST_CASE("char *")
    {
        Data2<const char *, std::tstring_t> data[] =
        {
            {"bbb",                 xT("bbb")},
            {(const char *)nullptr, xT("null")}
        };

       for (const auto &i : data) {
            m_sRv = Format::str(xT("{}"), i.test);
            xTEST_EQ(m_sRv, i.expect);
        }
    }

    xTEST_CASE("wchar_t *")
    {
        Data2<cptr_cwchar_t, std::tstring_t> data[] =
        {
            {L"bbb",                   xT("bbb")},
            {(cptr_cwchar_t)nullptr, xT("null")}
        };

       for (const auto &i : data) {
            m_sRv = Format::str(xT("{}"), i.test);
            xTEST_EQ(m_sRv, i.expect);
        }
    }

    xTEST_CASE("std::wstring")
    {
        Data2<std::wstring, std::tstring_t> data[] =
        {
            {L"dddфывff", xT("ddd<?><?><?>ff")},
            {L"\n",       xT("<LF>")},
            {L"a",        xT("a")},
            {L"聞",       xT("<?>")}
        };

       for (const auto &i : data) {
            m_sRv = Format::str(xT("{}"), i.test);
            xTEST_EQ(m_sRv, i.expect);
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
        {
            std::custring_t value(10, 'z');

            m_sRv = Format::str(xT("{}"), value);
            xTEST_EQ(m_sRv, std::tstring_t(xT("zzzzzzzzzz")));
        }

        {
            std::ustring_t value;
            value.push_back('z');
            value.push_back( static_cast<uchar_t>('\xa0') );
            value.push_back('\t');
            value.push_back('\n');
            value.push_back('\v');
            value.push_back('\f');
            value.push_back('\r');  // int: -96
            value.push_back(0x7F);  // int: 127
            value.push_back('x');

            m_sRv = Format::str(xT("{}"), value);
            xTEST_EQ(m_sRv, std::tstring_t(xT("z<?><HT><LF><VT><FF><CR><?>x")));
        }
    }

    xTEST_CASE("std::array")
    {
        std::array<int_t, 5> value = {{2, 16, 77, 34, 50}};

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{2, 16, 77, 34, 50}")));
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

    xTEST_CASE("std::deque")
    {
        std::deque<long_t> value;
        value.push_back(0);
        value.push_back(1);
        value.push_back(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{0, 1, 2}")));

        value.pop_back();
        value.pop_front();

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{1}")));
    }

    xTEST_CASE("std::queue")
    {
        std::queue<long_t> value;
        value.push(0);
        value.push(1);
        value.push(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{0, 1, 2}")));

        value.pop();

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{1, 2}")));
    }

    xTEST_CASE("std::priority_queue")
    {
        std::priority_queue<long_t> value;
        value.push(123);
        value.push(10);
        value.push(456);
        value.push(789);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{789, 456, 123, 10}")));

        value.pop();

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{456, 10, 123}")));
    }

    xTEST_CASE("std::stack")
    {
        std::stack<long_t> value;
        value.push(0);
        value.push(1);
        value.push(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{0, 1, 2}")));
    }

    xTEST_CASE("std::map")
    {
        std::map<std::tstring_t, int> value;
        value[xT("0")] = 3;
        value[xT("1")] = 4;
        value[xT("3")] = 5;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{{0, 3}\n{1, 4}\n{3, 5}}")));
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
        xTEST_EQ(m_sRv, std::tstring_t(xT("{{0, aa}\n{1, bbb}\n{1, bbb}}")));
    }

    xTEST_CASE("std::nullptr_t")
    {
        std::nullptr_t value = nullptr;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("nullptr")));
    }

    xTEST_CASE("std::array")
    {
        std::array<int_t, 5> value {{2, 16, 77, 34, 50}};

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{2, 16, 77, 34, 50}")));
    }

    xTEST_CASE("std::forward_list")
    {
        std::forward_list<std::tstring_t> value;
        value.push_front(xT("aa"));
        value.push_front(xT("bbb"));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{bbb, aa}")));
    }

    xTEST_CASE("std::unordered_map")
    {
        std::unordered_map<std::tstring_t, int> value;
        value[xT("0")] = 3;
        value[xT("1")] = 4;
        value[xT("1")] = 5;

        m_sRv = Format::str(xT("{}"), value);
        xTEST_DIFF(m_sRv.find("{1, 5}"),  std::tstring_t::npos);
        xTEST_DIFF(m_sRv.find("{0, 3}"),  std::tstring_t::npos);
    }

    xTEST_CASE("std::unordered_multimap")
    {
        std::pair<int, std::tstring_t> p1(0, xT("aa"));
        std::pair<int, std::tstring_t> p2(1, xT("bbb"));
        std::pair<int, std::tstring_t> p3(1, xT("bbb"));

        std::unordered_multimap<int, std::tstring_t> value;
        value.insert(p1);
        value.insert(p2);
        value.insert(p3);

        m_sRv = Format::str(xT("{}"), value);
		xTEST_DIFF(m_sRv.find("{0, aa}"),  std::tstring_t::npos);
		xTEST_DIFF(m_sRv.find("{1, bbb}"), std::tstring_t::npos);
		xTEST_DIFF(m_sRv.find("{1, bbb}"), std::tstring_t::npos);
    }

    xTEST_CASE("std::unordered_set")
    {
        std::unordered_set<long_t> value;
        value.insert(0);
        value.insert(1);
        value.insert(1);
        value.insert(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_DIFF(m_sRv.find("0"), std::tstring_t::npos);
        xTEST_DIFF(m_sRv.find("1"), std::tstring_t::npos);
        xTEST_DIFF(m_sRv.find("2"), std::tstring_t::npos);
    }

    xTEST_CASE("std::unordered_multiset")
    {
        std::unordered_multiset<long_t> value;
        value.insert(0);
        value.insert(1);
        value.insert(1);
        value.insert(2);

        m_sRv = Format::str(xT("{}"), value);
        xTEST_DIFF(m_sRv.find("0"), std::tstring_t::npos);
        xTEST_DIFF(m_sRv.find("1"), std::tstring_t::npos);
        xTEST_DIFF(m_sRv.find("2"), std::tstring_t::npos);
    }

    xTEST_CASE("std::tuple")
    {
		auto value = std::make_tuple(xT("test"), 3ULL, 14, xT('y'));

        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{test, 3, 14, y}")));
    }

    xTEST_CASE("QString")
    {
    #if xLIB_QT
        QString value0 = "abcde";
        QString value1 = "zxcv";

        m_sRv = Format::str(xT("{}-{}"), value0, value1);
        xTEST_EQ(m_sRv, std::tstring_t(xT("abcde-zxcv")));
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("enum")
    {
	#if 0
		EnumTest value0 = EnumTest::etUnknown;
		EnumTest value1 = EnumTest::etOne;
		EnumTest value2 = EnumTest::etTwo;
	#endif

        m_sRv = Format::str(xT("{}, {}, {}"), EnumTest::etUnknown, EnumTest::etOne, EnumTest::etTwo);
        xTEST_EQ(m_sRv, std::tstring_t(xT("etUnknown, etOne, etTwo")));
    }

    xTEST_CASE("struct")
    {
        StructTest value = {7, xT("std::string"), xT("c_str")};
        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{7, std::string, c_str}")));
    }

    xTEST_CASE("struct/print")
    {
        StructTest2 value = {7, xT("std::string"), xT("c_str")};
        m_sRv = Format::str(xT("{}"), value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("{7, std::string, c_str}")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
