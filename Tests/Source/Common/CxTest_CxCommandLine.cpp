/**
 * \file   CxTest_CxCommandLine.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxCommandLine.h>


//---------------------------------------------------------------------------
CxTest_CxCommandLine::CxTest_CxCommandLine() {

}
//---------------------------------------------------------------------------
CxTest_CxCommandLine::~CxTest_CxCommandLine() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCommandLine::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxCommandLine::argsMax", cullCaseLoops)
    {
        m_liRv = CxCommandLine::argsMax();
        xTEST_LESS(0L, m_liRv);
        //xTRACEV(xT("\tCxCommandLine::liArgsMax() = %li"), m_liRv);
    }

    xTEST_CASE("CxCommandLine::get", cullCaseLoops)
    {
        m_sRv = CxCommandLine::get();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxCommandLine::sGet(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxCommandLine::args", cullCaseLoops)
    {
        CxCommandLine::args(&m_vsRv);
        xTEST_EQ(false, m_vsRv.empty());
    }

    xTEST_CASE("CxCommandLine::setArgs", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxCommandLine::setArgs(0, NULL);
        #endif
    }
}
//---------------------------------------------------------------------------
