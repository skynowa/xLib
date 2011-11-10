/**
 * \file   CxTest_CxCom.cpp
 * \brief
 */


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

#if defined(xOS_ENV_WIN)
    //-------------------------------------
    //bIsInit
    xTEST_BLOCK(cullBlockLoops)
    {
        {
            CxCom cmCom(CxCom::cmMultiThreaded);

            m_bRes = CxCom::bIsInit();
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxCom::bIsInit();
        xTEST_EQ(FALSE, m_bRes);
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
