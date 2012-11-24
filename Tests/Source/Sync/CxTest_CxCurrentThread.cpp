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
/* virtual */
void
CxTest_CxCurrentThread::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxCurrentThread::bIsCurrent", cullCaseLoops)
    {
        CxThread::id_t aulData[5][2] = {{0}};

        aulData[0][0] = (CxThread::id_t)CxCurrentThread::ulId();
        aulData[0][1] = (CxThread::id_t)true;

        aulData[1][0] = (CxThread::id_t)((ulong_t)CxCurrentThread::ulId() - 1);
        aulData[1][1] = (CxThread::id_t)false;

        aulData[2][0] = (CxThread::id_t)0;
        aulData[2][1] = (CxThread::id_t)false;

        aulData[3][0] = (CxThread::id_t) - 1;
        aulData[3][1] = (CxThread::id_t)false;

        aulData[4][0] = (CxThread::id_t)- 1;
        aulData[4][1] = (CxThread::id_t)false;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const CxThread::id_t culId = aulData[i][0];
            const bool           cbRes = xINT_TO_BOOL( (ulong_t)aulData[i][1] );

            m_bRv = CxCurrentThread::bIsCurrent(culId);
            xTEST_EQ(cbRes, m_bRv);
        }
    }

    xTEST_CASE("CxCurrentThread::ulGetId", cullCaseLoops)
    {
        CxThread::id_t idRes = CxCurrentThread::ulId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("CxCurrentThread::hHandle", cullCaseLoops)
    {
        CxThread::handle_t hRv = CxCurrentThread::hHandle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    xTEST_CASE("CxCurrentThread::ulGetId", cullCaseLoops)
    {
        CxThread::id_t idRes = CxCurrentThread::ulId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("CxCurrentThread::hHandle", cullCaseLoops)
    {
        CxThread::handle_t hRv = CxCurrentThread::hHandle();
        xTEST_LESS((ulong_t)0, (ulong_t)hRv);
    }

    xTEST_CASE("CxCurrentThread::vYield", cullCaseLoops)
    {
        CxCurrentThread::vYield();
    }

    xTEST_CASE("CxCurrentThread::vSleep", cullCaseLoops)
    {
        const ulong_t caulData[] = {
            0,
            1
            // ULONG_MIN,
            // ULONG_MAX
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            const uint_t cuiMsec = caulData[i];

            CxDateTime dtTime1;
            
            dtTime1 = CxDateTime::dtCurrent();

            CxCurrentThread::vSleep(cuiMsec);

            CxDateTime dtTime2;
            
            dtTime2 = CxDateTime::dtCurrent();

            xTEST_GR_EQ(dtTime2.ullToMilliseconds(), dtTime1.ullToMilliseconds());
            //xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sFormat(CxDateTime::ftTime).c_str(), dtTime2.sFormat(CxDateTime::ftTime).c_str());
        }
    }
}
//---------------------------------------------------------------------------
