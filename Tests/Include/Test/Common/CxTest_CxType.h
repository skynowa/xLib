/****************************************************************************
* Class name:  CxTest_CxType
* Description: test CxType
* File name:   CxType.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     30.07.2011
*
*****************************************************************************/


#ifndef CxTest_CxTypeH
#define CxTest_CxTypeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxType.h>
//---------------------------------------------------------------------------
class CxTest_CxType :
    public CxTest
{
    public:
                      CxTest_CxType();
        virtual      ~CxTest_CxType();

        virtual BOOL  bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTypeH
