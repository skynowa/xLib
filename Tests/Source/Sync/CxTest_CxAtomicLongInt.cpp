/**
 * \file   CxTest_CxAtomicLongInt.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAtomicLongInt.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxAtomicLongInt::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxAtomicLongInt::operator += (const CxAtomicLongInt &cRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 += alLong2;
        xTEST_EQ(17L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator += (clong_t &cliRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 += 10L;
        xTEST_EQ(17L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator -= (const CxAtomicLongInt &cRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 -= alLong2;
        xTEST_EQ(- 3L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator -= (clong_t &cliRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 -= 10L;
        xTEST_EQ(- 3L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator = (const CxAtomicLongInt &cRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 = alLong2;
        xTEST_EQ(10L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator = (clong_t &cliRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 = 10L;
        xTEST_EQ(10L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator == (const CxAtomicLongInt &cRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRv = ( alLong1 == alLong2 );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator == (clong_t &cliRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 == 7L );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator != (const CxAtomicLongInt &cRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRv = ( alLong1 != alLong2 );
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator != (clong_t &cliRight)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 != 7L );
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator < (clong_t &cliValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 < 10L );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator < (const CxAtomicLongInt &calValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRv = ( alLong1 < alLong2 );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator <= (clong_t &cliValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRv = ( alLong1 <= 10L );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator <= (const CxAtomicLongInt &calValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRv = ( alLong1 <= alLong2 );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator > (clong_t &cliValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRv = ( alLong1 > 7L );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator > (const CxAtomicLongInt &calValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRv = ( alLong1 > alLong2 );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator >= (clong_t &cliValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRv = ( alLong1  >= 7L);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator >= (const CxAtomicLongInt &calValue)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRv = ( alLong1 >= alLong2 );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxAtomicLongInt::operator ++ (cint_t ciPos)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 ++;
        xTEST_EQ(8L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::operator -- (cint_t ciPos)", a_caseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 --;
        xTEST_EQ(6L, alLong1.value());
    }

    xTEST_CASE("CxAtomicLongInt::value", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        xTEST_EQ(7L,  alLong1.value());
        xTEST_EQ(10L, alLong2.value());
    }

    xTEST_CASE("CxAtomicLongInt::all", a_caseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

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
//------------------------------------------------------------------------------
