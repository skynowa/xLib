/**
 * \file   CxTest_CxAutoCriticalSection.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoCriticalSection.h>

#include <xLib/Sync/CxCriticalSection.h>


//---------------------------------------------------------------------------
CxTest_CxAutoCriticalSection::CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoCriticalSection::~CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxAutoCriticalSection::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //CxAutoCriticalSection
    xTEST_CASE(cullCaseLoops)
    {
        size_t            uiCounter = 0;
        CxCriticalSection csCS;

        {
            CxAutoCriticalSection acsCS(csCS);

            m_bRes = acsCS.bIsLocked();
            xTEST_EQ(true, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = acsCS.bIsLocked();
                xTEST_EQ(true, m_bRes);

                ++ uiCounter;
            }

            m_bRes = acsCS.bIsLocked();
            xTEST_EQ(true, m_bRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
