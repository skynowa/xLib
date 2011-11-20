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
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bIsCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxId aulData[5][2] = {{0}};

        aulData[0][0] = (CxThread::TxId)CxCurrentThread::ulGetId();
        aulData[0][1] = (CxThread::TxId)true;

        aulData[1][0] = (CxThread::TxId)((ULONG)CxCurrentThread::ulGetId() - 1);
        aulData[1][1] = (CxThread::TxId)false;

        aulData[2][0] = (CxThread::TxId)0;
        aulData[2][1] = (CxThread::TxId)false;

        aulData[3][0] = (CxThread::TxId) - 1;
        aulData[3][1] = (CxThread::TxId)false;

        aulData[4][0] = (CxThread::TxId)- 1;
        aulData[4][1] = (CxThread::TxId)false;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const CxThread::TxId culId = aulData[i][0];
            const bool           cbRes = xINT_AS_BOOL( (ULONG)aulData[i][1] );

            m_bRes = CxCurrentThread::bIsCurrent(culId);
            xTEST_EQ(cbRes, m_bRes);
        }
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxId idRes = CxCurrentThread::ulGetId();
        xTEST_LESS(0UL, (ULONG)idRes);
    }

    //--------------------------------------------------
    //hGetHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxHandle hRes = CxCurrentThread::hGetHandle();
        xTEST_DIFF(0UL, (ULONG)hRes);
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxId idRes = CxCurrentThread::ulGetId();
        xTEST_LESS(0UL, (ULONG)idRes);
    }

    //--------------------------------------------------
    //hGetHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxHandle hRes = CxCurrentThread::hGetHandle();
        xTEST_LESS((ULONG)0, (ULONG)hRes);
    }

    //--------------------------------------------------
    //bYield
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxCurrentThread::bYield();
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_BLOCK(cullBlockLoops)
    {
        const ULONG caulData[] = {
            0,
            1,
            (std::numeric_limits<ULONG>::min)(),
            //(std::numeric_limits<ULONG>::max)()
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const UINT cuiMsec = caulData[i];

            CxDateTime dtTime1 = CxDateTime::dtGetCurrent();

            m_bRes = CxCurrentThread::bSleep(cuiMsec);
            xTEST_DIFF(false, m_bRes);

            CxDateTime dtTime2 = CxDateTime::dtGetCurrent();

            xTEST_GREATER_EQ(dtTime2.ullToMilliseconds(), dtTime1.ullToMilliseconds());
            //xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sFormat(CxDateTime::ftTime).c_str(), dtTime2.sFormat(CxDateTime::ftTime).c_str());
        }
    }

    return true;
}
//---------------------------------------------------------------------------
