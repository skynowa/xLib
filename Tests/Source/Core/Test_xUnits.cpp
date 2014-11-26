/**
 * \file   Test_Units.cpp
 * \brief  test Units
 */


#include <Test/Core/Test_Units.h>

#include <xLib/Core/String.h>


//-------------------------------------------------------------------------------------------------
template<class T1, class T2>
std::tstring_t
xformat(
    std::ctstring_t &a_format,
    const T1        &a_t1,
    const T2        &a_t2
)
{
    std::tstring_t sRv;

    std::vec_tstring_t vec_format;
    String::split(a_format, "{}", &vec_format);

    for (std::size_t i = 0; i < vec_format.size(); ++ i) {
        sRv += vec_format[i];

        std::tstringstream_t ss;
        switch (i) {
        case 0:
            ss << a_t1;
            break;
        case 1:
            ss << a_t2;
            break;
        case 2:
        default:
            ;
            break;
        }

        sRv += ss.str();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Units::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Bytes", a_caseLoops)
    {
        culonglong_t BYTE = 1ULL;
        culonglong_t KB   = 1024ULL;
        culonglong_t MB   = 1024ULL * 1024;
        culonglong_t GB   = 1024ULL * 1024 * 1024;
        culonglong_t TB   = 1024ULL * 1024 * 1024 * 1024;
        culonglong_t PB   = 1024ULL * 1024 * 1024 * 1024 * 1024;
        culonglong_t EB   = 1024ULL * 1024 * 1024 * 1024 * 1024 * 1024;

        for (size_t i = 0; i < 20; ++ i) {
            xTEST_EQ(xBYTES(1 * i), BYTE * i);
            xTEST_EQ(xKB(1 * i),    KB * i);
            xTEST_EQ(xMB(1 * i),    MB * i);
            xTEST_EQ(xGB(1 * i),    GB * i);
            xTEST_EQ(xTB(1 * i),    TB * i);
            xTEST_EQ(xPB(1 * i),    PB * i);
            xTEST_EQ(xEB(1 * i),    EB * i);
        }
    }

    xTEST_CASE("Datetime", a_caseLoops)
    {
        // TEST: Datetime
    }

    xTEST_CASE("xformat", a_caseLoops)
    {
        std::size_t    v1 = 777;
        std::tstring_t v2 = "sss";

        m_sRv = ::xformat("***[{}]=[{}]***", v1, v2);
        xTEST_EQ(m_sRv, std::tstring_t(xT("***[777]=[sss]***")));

        Trace() << xTRACE_VAR(m_sRv);

        std::exit(0);
    }
}
//-------------------------------------------------------------------------------------------------
