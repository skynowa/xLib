/****************************************************************************
* Class name:  CxTest_CxLocale
* Description: test CxLocale
* File name:   CxTest_CxLocale.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxLocaleH
#define CxTest_CxLocaleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxLocale.h>
//---------------------------------------------------------------------------
class CxTest_CxLocale : public CxTest {
    public:
        CxTest_CxLocale();
        virtual     ~CxTest_CxLocale();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: CxTest_CxLocale (constructor)
CxTest_CxLocale::CxTest_CxLocale() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: ~CxTest_CxLocale (destructor)
CxTest_CxLocale::~CxTest_CxLocale() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxLocale::bUnit() {
    //-------------------------------------
    //sGetCurrent (don't change current locale)
    tString sCurrLocale;

    {
        m_sRes = CxLocale::sGetCurrent();
    #if defined(xOS_WIN)
        xASSERT_MSG(xT("Russian") == m_sRes, m_sRes.c_str());
    #elif defined(xOS_LINUX)
        xASSERT_MSG(xT("C") == m_sRes, m_sRes.c_str());
    #endif

        sCurrLocale = m_sRes; //(don't change current locale)
    }

    //-------------------------------------
    //bSetCurrent
    {
    #if defined(xOS_WIN)
        m_bRes = CxLocale::bSetCurrent(xT("English"));
        xASSERT(FALSE != m_bRes);
        //xTRACE(xT("Не должен быть русский текст"));
    #elif defined(xOS_LINUX)
        m_bRes = CxLocale::bSetCurrent(xT("ru_RU.UTF-8"));
        xASSERT(FALSE != m_bRes);
    #endif
    }

    //-------------------------------------
    //bSetCurrent
    {
        m_bRes = CxLocale::bSetDefault();
        xASSERT(FALSE != m_bRes);
        //xTRACE(xT("Должен быть русский текст"));
    }

    //-------------------------------------
    //bSetCurrent (don't change current locale)
    {
        m_bRes = CxLocale::bSetCurrent(sCurrLocale);
        xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxLocaleH

