/**
 * \file   Test_Units.cpp
 * \brief  test Units
 */


#include <Test/Core/Test_Units.h>

#include <xLib/Core/String.h>


#define xARGTYPES_1  class T1
#define xARGTYPES_2  class T1, class T2
#define xARGTYPES_3  class T1, class T2, class T3
#define xARGTYPES_4  class T1, class T2, class T3, class T4
#define xARGTYPES_5  class T1, class T2, class T3, class T4, class T5
#define xARGTYPES_6  class T1, class T2, class T3, class T4, class T5, class T6
#define xARGTYPES_7  class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define xARGTYPES_8  class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define xARGTYPES_9  class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9
#define xARGTYPES_10 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10

#define xVARARGS_1  const T1& a_t1
#define xVARARGS_2  const T1& a_t1, const T2& a_t2
#define xVARARGS_3  const T1& a_t1, const T2& a_t2, const T3& a_t3
#define xVARARGS_4  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4
#define xVARARGS_5  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5
#define xVARARGS_6  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6
#define xVARARGS_7  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7
#define xVARARGS_8  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7, const T8& a_t8
#define xVARARGS_9  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7, const T8& a_t8, const T9& a_t9
#define xVARARGS_10 const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7, const T8& a_t8, const T9& a_t9, const T10& a_t10
//-------------------------------------------------------------------------------------------------
template<xARGTYPES_3>
std::tstring_t
xformat(
    std::ctstring_t &a_format, xVARARGS_3
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
            ss << a_t3;
            break;
        case 3:
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
        cint_t         v3 = 3;

        m_sRv = ::xformat("***[{}]=[{}]=[{}]***", v1, v2, v3);
        xTEST_EQ(m_sRv, std::tstring_t(xT("***[777]=[sss]=[3]***")));

        Trace() << xTRACE_VAR(m_sRv);

        std::exit(0);
    }
}
//-------------------------------------------------------------------------------------------------
