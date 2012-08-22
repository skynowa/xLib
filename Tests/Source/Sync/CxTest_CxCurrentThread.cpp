/**
 * \file   CxTest_CxCurrentThread.cpp
 * \brief  test CxCurrentThread
 */


#include <Test/Sync/CxTest_CxCurrentThread.h>

#include <xLib/Common/CxDateTime.h>


//---------------------------------------------------------------------------
CxTest_CxCurrentThread::CxTest_CxCurrentThread() {

}
//---------------------------------------------------------------------------
CxTest_CxCurrentThread::~CxTest_CxCurrentThread() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxCurrentThread::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //bIsCurrent
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxId aulData[5][2] = {{0}};

        aulData[0][0] = (CxThread::TxId)CxCurrentThread::ulGetId();
        aulData[0][1] = (CxThread::TxId)true;

        aulData[1][0] = (CxThread::TxId)((ulong_t)CxCurrentThread::ulGetId() - 1);
        aulData[1][1] = (CxThread::TxId)false;

        aulData[2][0] = (CxThread::TxId)0;
        aulData[2][1] = (CxThread::TxId)false;

        aulData[3][0] = (CxThread::TxId) - 1;
        aulData[3][1] = (CxThread::TxId)false;

        aulData[4][0] = (CxThread::TxId)- 1;
        aulData[4][1] = (CxThread::TxId)false;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const CxThread::TxId culId = aulData[i][0];
            const bool           cbRes = xINT_TO_BOOL( (ulong_t)aulData[i][1] );

            m_bRv = CxCurrentThread::bIsCurrent(culId);
            xTEST_EQ(cbRes, m_bRv);
        }
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxId idRes = CxCurrentThread::ulGetId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    //--------------------------------------------------
    //hGetHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxHandle hRv = CxCurrentThread::hGetHandle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxId idRes = CxCurrentThread::ulGetId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    //--------------------------------------------------
    //hGetHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxHandle hRv = CxCurrentThread::hGetHandle();
        xTEST_LESS((ulong_t)0, (ulong_t)hRv);
    }

    //--------------------------------------------------
    //bYield
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxCurrentThread::bYield();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_CASE(cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0,
            1,
            (std::numeric_limits<ulong_t>::min)(),
            //(std::numeric_limits<ulong_t>::max)()
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const uint_t cuiMsec = caulData[i];

            CxDateTime dtTime1;
            
            dtTime1 = CxDateTime::dtGetCurrent();

            m_bRv = CxCurrentThread::bSleep(cuiMsec);
            xTEST_EQ(true, m_bRv);

            CxDateTime dtTime2;
            
            dtTime2 = CxDateTime::dtGetCurrent();

            xTEST_GREATER_EQ(dtTime2.ullToMilliseconds(), dtTime1.ullToMilliseconds());
            //xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sFormat(CxDateTime::ftTime).c_str(), dtTime2.sFormat(CxDateTime::ftTime).c_str());
        }
    }

    return true;
}
//---------------------------------------------------------------------------
