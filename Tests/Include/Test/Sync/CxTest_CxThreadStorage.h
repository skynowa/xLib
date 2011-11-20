/**
 * \file   CxTest_CxThreadStorage.h
 * \brief
 */


#ifndef CxTest_CxThreadStorageH
#define CxTest_CxThreadStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxThreadStorage.h>
//---------------------------------------------------------------------------
class CxTest_CxThreadStorage :
    public CxTest
{
    public:
                     CxTest_CxThreadStorage();
        virtual     ~CxTest_CxThreadStorage();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadStorageH
