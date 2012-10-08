/**
 * \file   CxTest_CxMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxMutex.h>


//---------------------------------------------------------------------------
CxTest_CxMutex::CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxMutex::~CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxMutex::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    size_t uiVal = 0;

    xTEST_CASE(CxMutex::vLock CxMutex::vUnlock, cullCaseLoops)
    {
        CxMutex csCS;

        csCS.vCreate();
        csCS.vLock();

        ++ uiVal;

        csCS.vUnlock();
    }

    xTEST_CASE(CxMutex::vTryLock CxMutex::vUnlock, cullCaseLoops)
    {
        CxMutex csCS;

        csCS.vCreate();

        m_bRv = csCS.bTryLock();
        xTEST_EQ(true, m_bRv);

        ++ uiVal;

        csCS.vUnlock();
    }

    xTEST_CASE(CxMutex::vLock CxMutex::vUnlock, cullCaseLoops)
    {
        CxMutex csCS;

        const size_t cuiLocks = 10;

        csCS.vCreate();

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.vLock();
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.vUnlock();
        }
    }

    xTEST_CASE(CxMutex::vTryLock CxMutex::vUnlock, cullCaseLoops)
    {
        CxMutex csCS;

        const size_t cuiLocks = 10;

        csCS.vCreate();

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.bTryLock();
            xTEST_EQ(true, m_bRv);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.vUnlock();
        }
    }
}
//---------------------------------------------------------------------------
