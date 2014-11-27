/**
 * \file   Test_Units.cpp
 * \brief  test Units
 */


#include <Test/Core/Test_Units.h>

#include <xLib/Core/Format.h>


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

    xTEST_CASE("Format", a_caseLoops)
    {
        std::size_t    v1 = 777;
        std::tstring_t v2 = "sss";
        cint_t         v3 = 3;

        m_sRv = Format("***[{}]=[{}]=[{}]***", v1, v2, v3);
        xTEST_EQ(m_sRv, std::tstring_t(xT("***[777]=[sss]=[3]***")));

        Trace() << xTRACE_VAR(m_sRv);

        std::exit(0);
    }
}
//-------------------------------------------------------------------------------------------------
