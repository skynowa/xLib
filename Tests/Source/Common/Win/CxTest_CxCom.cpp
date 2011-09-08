/****************************************************************************
* Class name:  CxTest_CxCom
* Description: test CxCom
* File name:   CxTest_CxCom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/Win/CxTest_CxCom.h>


//---------------------------------------------------------------------------
CxTest_CxCom::CxTest_CxCom() {

}
//---------------------------------------------------------------------------
CxTest_CxCom::~CxTest_CxCom() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxCom::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

#if defined(xOS_WIN)
    //-------------------------------------
    //bIsInit
    xTEST_BLOCK(cullBlockLoops)
    {
        {
            CxCom cmCom(CxCom::cmMultiThreaded);

            m_bRes = CxCom::bIsInit();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxCom::bIsInit();
        xASSERT_EQ(FALSE, m_bRes);
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
