/****************************************************************************
* Class name:  CxTest_CxLocale
* Description: test CxLocale
* File name:   CxTest_CxLocale.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxLocale.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxLocale
CxTest_CxLocale::CxTest_CxLocale() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxLocale
CxTest_CxLocale::~CxTest_CxLocale() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxLocale::bUnit() {
    //-------------------------------------
    //sGetCurrent
    {
        m_sRes = CxLocale::sGetCurrent();
        xASSERT(false == m_sRes.empty());
    }

    //-------------------------------------
    //bSetCurrent
    {
        m_bRes = CxLocale::bSetCurrent( CxLocale::sGetCurrent() );
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetDefault
    {
        m_bRes = CxLocale::bSetDefault();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetCurrent
    {
        m_bRes = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
        xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
