/**
 * \file   Test_Thread.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Thread)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Thread::unit()
{
     xTEST_CASE("isCurrent")
    {
        const Data2<Thread::id_t, bool_t> datas []
        {
            {ThreadCurrent::id(), true},
            {(ulong_t)ThreadCurrent::id() - 1, false},
            {0,   false},
            {- 1, false},
            {- 1, false}
        };

        for (const auto &[it_test, it_expect] : datas) {
            m_bRv = ThreadCurrent::isCurrent(it_test);
            xTEST_EQ(m_bRv, it_expect);
        }
    }

    xTEST_CASE("id")
    {
        Thread::id_t idRes = ThreadCurrent::id();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("handle")
    {
        Thread::handle_t hRv = ThreadCurrent::handle();
        xTEST_DIFF((ulonglong_t)hRv, 0ULL);
    }

    xTEST_CASE("id")
    {
        Thread::id_t idRes = ThreadCurrent::id();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("handle")
    {
        Thread::handle_t hRv = ThreadCurrent::handle();
        xTEST_LESS(0ULL, (ulonglong_t)hRv);
    }

    xTEST_CASE("yield")
    {
        ThreadCurrent::yield();
    }

    xTEST_CASE("sleep")
    {
        culong_t caulData[]
        {
            0,
            1
            // ULONG_MIN,
            // ULONG_MAX
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t cuiMsec = caulData[i];

            DateTime dtTime1;
            dtTime1 = DateTime::current();

            ThreadCurrent::sleep(cuiMsec);

            DateTime dtTime2;
            dtTime2 = DateTime::current();

            xTEST_GR_EQ(dtTime2.toMsec(), dtTime1.toMsec());
            // xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sormat(DateTime::ftTime).c_str(),
            //    dtTime2.format(DateTime::ftTime).c_str());
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
