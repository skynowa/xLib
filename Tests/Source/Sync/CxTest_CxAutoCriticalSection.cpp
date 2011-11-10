/**
 * \file   CxTest_CxAutoCriticalSection.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoCriticalSection.h>


//---------------------------------------------------------------------------
CxTest_CxAutoCriticalSection::CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoCriticalSection::~CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxAutoCriticalSection::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //CxAutoCriticalSection
    xTEST_BLOCK(cullBlockLoops)
    {
        size_t            uiCounter = 0;
        CxCriticalSection csCS;

        {
            CxAutoCriticalSection acsCS(csCS);

            m_bRes = acsCS.bIsLocked();
            xTEST_DIFF(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = acsCS.bIsLocked();
                xTEST_DIFF(FALSE, m_bRes);

                ++ uiCounter;
            }

            m_bRes = acsCS.bIsLocked();
            xTEST_DIFF(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
