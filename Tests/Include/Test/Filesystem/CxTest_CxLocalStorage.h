/****************************************************************************
* Class name:  CxTest_CxLocalStorage
* Description: test CxLocalStorage
* File name:   CxLocalStorage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#ifndef CxTest_CxLocalStorageH
#define CxTest_CxLocalStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxLocalStorage.h>
//---------------------------------------------------------------------------
class CxTest_CxLocalStorage :
    public CxTest
{
    public:
                      CxTest_CxLocalStorage();
        virtual      ~CxTest_CxLocalStorage();

        virtual  BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxLocalStorageH
