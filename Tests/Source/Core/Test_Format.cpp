/**
 * \file   Test_Format.cpp
 * \brief  test Format
 */


#include <Test/Core/Test_Format.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Format::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Format", a_caseLoops)
    {
        std::csize_t    v1 = 777;
        std::ctstring_t v2 = std::ctstring_t(xT("aaa"));
        cint_t          v3 = 333;
        ctchar_t        v4 = xT('a');
        ctchar_t *      v5 = xT("bbb");
        clong_t         v6 = 444L;
        cvoid_t *       v7 = (cvoid_t *)2000;

        m_sRv = Format(xT("***{}={}={}={}={}={}={}***"), v1, v2, v3, v4, v5, v6, v7);
        // xTEST_EQ(m_sRv, std::tstring_t(xT("***777=aaa=333=a=bbb=444=0x7d0***")));

        Trace() << xTRACE_VAR(m_sRv);

        std::exit(0);
    }
}
//-------------------------------------------------------------------------------------------------
