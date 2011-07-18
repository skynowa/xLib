/****************************************************************************
* Class name:  CxTest_CxCom
* Description: test CxCom
* File name:   CxTest_CxCom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxCom.h>


//---------------------------------------------------------------------------
//TODO: CxTest_CxCom
CxTest_CxCom::CxTest_CxCom() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: ~CxTest_CxCom
CxTest_CxCom::~CxTest_CxCom() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL CxTest_CxCom::bUnit() {
    /*DEBUG*/

#if defined(xOS_WIN)
    //-------------------------------------
    //bIsInit
    {
        {
            CxCom cmCom(CxCom::cmMultiThreaded);

            m_bRes = CxCom::bIsInit();
            xASSERT(FALSE != m_bRes);
        }

        m_bRes = CxCom::bIsInit();
        xASSERT(FALSE == m_bRes);
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
