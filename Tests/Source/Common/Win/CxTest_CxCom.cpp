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
bool
CxTest_CxCom::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

#if xOS_ENV_WIN

    //-------------------------------------
    // bIsInit
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxCom::bIsInit();
        xTEST_EQ(false, m_bRes);

        {
            CxCom cmCom(CxCom::cmMultiThreaded);

            m_bRes = CxCom::bIsInit();
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxCom::bIsInit();
        xTEST_EQ(false, m_bRes);
    }

#endif

    return true;
}
//---------------------------------------------------------------------------
