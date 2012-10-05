/**
 * \file   CxTest_CxSocket.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSocket.h>

#include <xLib/Patterns/CxSingleton.h>
#include <xLib/Net/CxSocketInit.h>


//---------------------------------------------------------------------------
CxTest_CxSocket::CxTest_CxSocket() {

}
//---------------------------------------------------------------------------
CxTest_CxSocket::~CxTest_CxSocket() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSocket::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    CxSocketInit siInit22(2, 2);
}
//---------------------------------------------------------------------------
