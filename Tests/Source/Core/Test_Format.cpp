/**
 * \file   Test_Format.cpp
 * \brief  test Format
 */


#include <Test/Core/Test_Format.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Format)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Format::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Format", a_caseLoops)
    {
        cbool_t         v1  = false;
        ctchar_t        v2  = xT('a');
        cuchar_t        v3  = 'b';
        cshort_t        v4  = -10;
        cushort_t       v5  = 10;
        cint_t          v6  = -111;
        cuint_t         v7  = 111U;
        clong_t         v8  = -222L;
        culong_t        v9  = 222UL;
        clonglong_t     v10 = -333LL;
        culonglong_t    v11 = 333ULL;
        cfloat_t        v12 = 444.0f;
        cdouble_t       v13 = 555.0f;
        clongdouble_t   v14 = 666.0L;
        cvoid_t *       v15 = (cvoid_t *)777;

        std::ctstring_t v16 = std::ctstring_t(xT("aaa"));
        ctchar_t *      v17 = xT("bbb");

        m_sRv += Format::format(
            xT("{}_{}_{}_{}_{}_{}_{}_{}_{}_{}"),
            v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);

        m_sRv += Format::format(
            xT("_{}_{}_{}_{}_{}_{}_{}"),
            v11, v12, v13, v14, v15, v16, v17);

        xTEST_EQ(m_sRv, std::tstring_t(xT("0_a_b_-10_10_-111_111_-222_222_-333_333_444_555_666_0x309_aaa_bbb")));
        // Trace() << xTRACE_VAR(m_sRv);

        std::exit(0);
    }
}
//-------------------------------------------------------------------------------------------------
