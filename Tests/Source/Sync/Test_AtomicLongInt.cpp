/**
 * \file   Test_AtomicLongInt.cpp
 * \brief
 */


#include <Test/Sync/Test_AtomicLongInt.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_AtomicLongInt::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("AtomicLongInt::operator += (const AtomicLongInt &cRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 += alLong2;
        xTEST_EQ(17L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator += (clong_t &cliRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 += 10L;
        xTEST_EQ(17L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator -= (const AtomicLongInt &cRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 -= alLong2;
        xTEST_EQ(- 3L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator -= (clong_t &cliRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 -= 10L;
        xTEST_EQ(- 3L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator = (const AtomicLongInt &cRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 = alLong2;
        xTEST_EQ(10L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator = (clong_t &cliRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 = 10L;
        xTEST_EQ(10L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator == (const AtomicLongInt &cRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRv = ( alLong1 == alLong2 );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator == (clong_t &cliRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 == 7L );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator != (const AtomicLongInt &cRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRv = ( alLong1 != alLong2 );
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("AtomicLongInt::operator != (clong_t &cliRight)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 != 7L );
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("AtomicLongInt::operator < (clong_t &cliValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 < 10L );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator < (const AtomicLongInt &calValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRv = ( alLong1 < alLong2 );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator <= (clong_t &cliValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 <= 10L );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator <= (const AtomicLongInt &calValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRv = ( alLong1 <= alLong2 );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator > (clong_t &cliValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRv = ( alLong1 > 7L );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator > (const AtomicLongInt &calValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRv = ( alLong1 > alLong2 );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator >= (clong_t &cliValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRv = ( alLong1  >= 7L);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator >= (const AtomicLongInt &calValue)", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRv = ( alLong1 >= alLong2 );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("AtomicLongInt::operator ++ (cint_t ciPos)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 ++;
        xTEST_EQ(8L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::operator -- (cint_t ciPos)", a_caseLoops)
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 --;
        xTEST_EQ(6L, alLong1.value());
    }

    xTEST_CASE("AtomicLongInt::value", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        xTEST_EQ(7L,  alLong1.value());
        xTEST_EQ(10L, alLong2.value());
    }

    xTEST_CASE("AtomicLongInt::all", a_caseLoops)
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 1L;
        alLong2 = 2L;

        alLong1 += alLong2;
        xTEST_EQ(alLong1.value(), 3L);

        alLong1 -= alLong2;
        xTEST_EQ(alLong1.value(), 1L);

        alLong1  = alLong2;
        xTEST_EQ(alLong1.value(), 2L);

        alLong1 += 10L;
        xTEST_EQ(alLong1.value(), 12L);

        alLong1 -= 10L;
        xTEST_EQ(alLong1.value(), 2L);

        alLong1  = 10L;
        xTEST_EQ(alLong1.value(), 10L);

        m_liRv = alLong1.value();
        xTEST_EQ(10L, m_liRv);
    }
}
//-------------------------------------------------------------------------------------------------
