/**
 * \file   CxTest_CxTracer.cpp
 * \brief  test CxTracer
 */


#include <Test/Log/CxTest_CxTracer.h>


//---------------------------------------------------------------------------
CxTest_CxTracer::CxTest_CxTracer() {

}
//---------------------------------------------------------------------------
CxTest_CxTracer::~CxTest_CxTracer() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxTracer::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // all
    xTEST_CASE(cullCaseLoops)
    {
        CxTracer::Write() << xT("Msg: ") << 12345 << xT(' ') << CxConst::x3DOT;
        CxTracer::Write() << xT("Msg: ") << 12345 << xT(' ') << CxConst::x3DOT;
    }

    return true;
}
//---------------------------------------------------------------------------
