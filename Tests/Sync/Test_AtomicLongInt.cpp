/**
 * \file   Test_AtomicLongInt.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AtomicLongInt)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AtomicLongInt::unit()
{
    xTEST_CASE("(const AtomicLongInt &value)")
    {
        AtomicLongInt alLong1;
        alLong1 = 13L;

        AtomicLongInt alLong2(alLong1);
        xTEST_EQ(alLong1.value(), 13L);
    }

    xTEST_CASE("operator += (const AtomicLongInt &cRight)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 += alLong2;
        xTEST_EQ(17L, alLong1.value());
    }

    xTEST_CASE("operator += (clong_t &cliRight)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 += 10L;
        xTEST_EQ(17L, alLong1.value());
    }

    xTEST_CASE("operator -= (const AtomicLongInt &cRight)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 -= alLong2;
        xTEST_EQ(- 3L, alLong1.value());
    }

    xTEST_CASE("operator -= (clong_t &cliRight)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 -= 10L;
        xTEST_EQ(- 3L, alLong1.value());
    }

    xTEST_CASE("operator = (const AtomicLongInt &cRight)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 = alLong2;
        xTEST_EQ(10L, alLong1.value());
    }

    xTEST_CASE("operator = (clong_t &cliRight)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 = 10L;
        xTEST_EQ(10L, alLong1.value());
    }

    xTEST_CASE("operator == (const AtomicLongInt &cRight)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRv = ( alLong1 == alLong2 );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator == (clong_t &cliRight)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 == 7L );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator != (const AtomicLongInt &cRight)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRv = ( alLong1 != alLong2 );
        xTEST(!m_bRv);
    }

    xTEST_CASE("operator != (clong_t &cliRight)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 != 7L );
        xTEST(!m_bRv);
    }

    xTEST_CASE("operator < (clong_t &cliValue)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 < 10L );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator < (const AtomicLongInt &calValue)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRv = ( alLong1 < alLong2 );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator <= (clong_t &cliValue)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 <= 10L );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator <= (const AtomicLongInt &calValue)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRv = ( alLong1 <= alLong2 );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator > (clong_t &cliValue)")
    {
        AtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRv = ( alLong1 > 7L );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator > (const AtomicLongInt &calValue)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRv = ( alLong1 > alLong2 );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator >= (clong_t &cliValue)")
    {
        AtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRv = ( alLong1  >= 7L);
        xTEST(m_bRv);
    }

    xTEST_CASE("operator >= (const AtomicLongInt &calValue)")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRv = ( alLong1 >= alLong2 );
        xTEST(m_bRv);
    }

    xTEST_CASE("operator ++ (cint_t ciPos)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 ++;
        xTEST_EQ(8L, alLong1.value());
    }

    xTEST_CASE("operator -- (cint_t ciPos)")
    {
        AtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 --;
        xTEST_EQ(6L, alLong1.value());
    }

    xTEST_CASE("value")
    {
        AtomicLongInt alLong1;
        AtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        xTEST_EQ(7L,  alLong1.value());
        xTEST_EQ(10L, alLong2.value());
    }

    xTEST_CASE("all")
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

    return true;
}
//-------------------------------------------------------------------------------------------------
