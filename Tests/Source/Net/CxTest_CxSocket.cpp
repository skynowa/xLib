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
/*virtual*/
bool
CxTest_CxSocket::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    CxSocketInit siInit22(2, 2);

    return true;
}
//---------------------------------------------------------------------------
