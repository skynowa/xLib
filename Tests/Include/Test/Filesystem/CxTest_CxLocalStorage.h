/**
 * \file   CxTest_CxLocalStorage.h
 * \brief
 */


#ifndef CxTest_CxLocalStorageH
#define CxTest_CxLocalStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxLocalStorage.h>
//---------------------------------------------------------------------------
class CxTest_CxLocalStorage :
    public CxTest
{
    public:
                      CxTest_CxLocalStorage();
        virtual      ~CxTest_CxLocalStorage();

        virtual  void vUnit(const ulonglong_t &cullCaseLoops) xOVERRIDE;

    private:
};
//---------------------------------------------------------------------------
#endif // CxTest_CxLocalStorageH
