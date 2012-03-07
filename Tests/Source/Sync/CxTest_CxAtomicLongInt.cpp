/**
 * \file   CxTest_CxAtomicLongInt.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAtomicLongInt.h>


//---------------------------------------------------------------------------
CxTest_CxAtomicLongInt::CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
CxTest_CxAtomicLongInt::~CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxAtomicLongInt::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //operator += (const CxAtomicLongInt &cRight);
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 += alLong2;
        xTEST_EQ(17L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator += (const long_t cliRight);
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 += 10L;
        xTEST_EQ(17L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator -= (const CxAtomicLongInt &cRight);
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 -= alLong2;
        xTEST_EQ(- 3L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator -= (const long_t cliRight);
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 -= 10L;
        xTEST_EQ(- 3L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator = (const CxAtomicLongInt &cRight);
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        alLong1 = alLong2;
        xTEST_EQ(10L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator = (const long_t cliRight)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 = 10L;
        xTEST_EQ(10L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator == (const CxAtomicLongInt &cRight)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRes = ( alLong1 == alLong2 );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator == (const long_t cliRight)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRes = ( alLong1 == 7L );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator != (const CxAtomicLongInt &cRight)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 7L;

        m_bRes = ( alLong1 != alLong2 );
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //operator != (const long_t cliRight)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRes = ( alLong1 != 7L );
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //operator < (const long_t &cliValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRes = ( alLong1 < 10L );
        xTEST_EQ(true, m_bRes);
    }
    //--------------------------------------------------
    //operator < (const CxAtomicLongInt &calValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRes = ( alLong1 < alLong2 );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator <= (const long_t &cliValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        m_bRes = ( alLong1 <= 10L );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator <= (const CxAtomicLongInt &calValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        m_bRes = ( alLong1 <= alLong2 );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator > (const long_t &cliValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRes = ( alLong1 > 7L );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator > (const CxAtomicLongInt &calValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRes = ( alLong1 > alLong2 );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator >= (const long_t &cliValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 10L;

        m_bRes = ( alLong1  >= 7L);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator >= (const CxAtomicLongInt &calValue)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 10L;
        alLong2 = 7L;

        m_bRes = ( alLong1 >= alLong2 );
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //operator ++ (const int ciPos)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 ++;
        xTEST_EQ(8L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //operator -- (const int ciPos)
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;

        alLong1 = 7L;

        alLong1 --;
        xTEST_EQ(6L, alLong1.liGetValue());
    }

    //--------------------------------------------------
    //liGetValue
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 7L;
        alLong2 = 10L;

        xTEST_EQ(7L,  alLong1.liGetValue());
        xTEST_EQ(10L, alLong2.liGetValue());
    }

    //--------------------------------------------------
    //common
    xTEST_CASE(cullCaseLoops)
    {
        CxAtomicLongInt alLong1;
        CxAtomicLongInt alLong2;

        alLong1 = 1L;
        alLong2 = 2L;

        alLong1 += alLong2;
        xTEST_EQ(alLong1.liGetValue(), 3L);

        alLong1 -= alLong2;
        xTEST_EQ(alLong1.liGetValue(), 1L);

        alLong1  = alLong2;
        xTEST_EQ(alLong1.liGetValue(), 2L);

        alLong1 += 10L;
        xTEST_EQ(alLong1.liGetValue(), 12L);

        alLong1 -= 10L;
        xTEST_EQ(alLong1.liGetValue(), 2L);

        alLong1  = 10L;
        xTEST_EQ(alLong1.liGetValue(), 10L);

        m_liRes = alLong1.liGetValue();
        xTEST_EQ(10L, m_liRes);
    }

    return true;
}
//---------------------------------------------------------------------------
