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
        std::size_t    v1 = 777;
        std::tstring_t v2 = "sss";
        cint_t         v3 = 3;

        m_sRv = Format(xT("***[{}]=[{}]=[{}]***"), v1, v2, v3);
        xTEST_EQ(m_sRv, std::tstring_t(xT("***[777]=[sss]=[3]***")));

        Trace() << xTRACE_VAR(m_sRv);

        // std::exit(0);
    }
}
//-------------------------------------------------------------------------------------------------
