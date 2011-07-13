/****************************************************************************
* Class name:  CxTest_CxCriticalSection
* Description: test CxCriticalSection
* File name:   CxTest_CxCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Sync/CxTest_CxCriticalSection.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCriticalSection (constructor)
CxTest_CxCriticalSection::CxTest_CxCriticalSection() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCriticalSection (destructor)
CxTest_CxCriticalSection::~CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxCriticalSection::bUnit() {
#if defined(xOS_WIN)
    //-------------------------------------
    //
    {
        CxCriticalSection objCriticalSection;

        objCriticalSection.vEnter();
        //xASSERT - not need

        objCriticalSection.vLeave();
        //xASSERT - not need

        g_ulRes = objCriticalSection.ulSetSpinCount(10000);
        xASSERT(0 <= g_ulRes);

        g_bRes = objCriticalSection.bTryEnter();
        xASSERT(FALSE != g_bRes);
    }

    //-------------------------------------
    //
    {
        CxCriticalSection objCriticalSection(1000);

        objCriticalSection.vEnter();
        //xASSERT - not need

        objCriticalSection.vLeave();
        //xASSERT - not need

        g_ulRes = objCriticalSection.ulSetSpinCount(10000);
        xASSERT(0 <= g_ulRes);

        g_bRes = objCriticalSection.bTryEnter();
        xASSERT(FALSE != g_bRes);
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
