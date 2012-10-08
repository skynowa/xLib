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
CxTest_CxCommandLine::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxCommandLine::liGetArgsMax, cullCaseLoops)
    {
        m_liRv = CxCommandLine::liGetArgsMax();
        xTEST_LESS(0L, m_liRv);
        //xTRACEV(xT("\tCxCommandLine::liGetArgsMax() = %li"), m_liRv);
    }

    xTEST_CASE(CxCommandLine::sGet, cullCaseLoops)
    {
        m_sRv = CxCommandLine::sGet();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxCommandLine::sGet(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE(CxCommandLine::vGetArgs, cullCaseLoops)
    {
        CxCommandLine::vGetArgs(&m_vsRv);
        xTEST_EQ(false, m_vsRv.empty());
    }

    xTEST_CASE(CxCommandLine::vSetArgs, cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxCommandLine::vSetArgs(ciArgsCount, paszArgs);
        #endif
    }
}
//---------------------------------------------------------------------------
