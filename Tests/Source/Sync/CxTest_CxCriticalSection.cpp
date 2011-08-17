/****************************************************************************
* Class name:  CxTest_CxCriticalSection
* Description: test CxCriticalSection
* File name:   CxTest_CxCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxCriticalSection.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCriticalSection
CxTest_CxCriticalSection::CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCriticalSection
CxTest_CxCriticalSection::~CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxCriticalSection::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
    //-------------------------------------
    //
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection objCriticalSection;

        objCriticalSection.vEnter();
        //xASSERT - not need

        objCriticalSection.vLeave();
        //xASSERT - not need

        m_ulRes = objCriticalSection.ulSetSpinCount(10000);
        xASSERT_LESS_EQ(0UL, m_ulRes);

        m_bRes = objCriticalSection.bTryEnter();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection objCriticalSection(1000);

        objCriticalSection.vEnter();
        //xASSERT - not need

        objCriticalSection.vLeave();
        //xASSERT - not need

        m_ulRes = objCriticalSection.ulSetSpinCount(10000);
        xASSERT_LESS_EQ(0UL, m_ulRes);

        m_bRes = objCriticalSection.bTryEnter();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
