/**
 * \file   CxTest_CxRandom.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxRandom.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxRandom::unit(
    culonglong_t &a_caseLoops
)
{
    // TEST: CxRandom

#if xTODO
    CxRandom rndR;

    //--------------------------------------------------
    //bSetSeed
    {
        m_bRv = rndR.bSetSeed( static_cast<ulong_t>( time(NULL) ) );
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //nextInt
    {
        m_iRv = rndR.nextInt();
        xTEST_LESS(0, m_iRv);
    }

    //--------------------------------------------------
    //nextInt
    {
        m_iRv = rndR.nextInt(100);
        xTEST_LESS_EQ(0, m_iRv);
    }

    //--------------------------------------------------
    //nextInt
    {
        m_iRv = rndR.nextInt(100, 200);
        xTEST_EQ(true, 100 <= m_iRv && 200 >= m_iRv);
    }

    //--------------------------------------------------
    //nextLong
    {
        m_liRv = rndR.nextLong();
        xTEST_LESS(0L, m_liRv);
    }

    //--------------------------------------------------
    //nextBool
    {
        m_blRes = rndR.nextBool();
        xTEST_EQ(true, m_blRes || !m_blRes);
    }

    //--------------------------------------------------
    //nextFloat
    {
        m_fRv = rndR.nextFloat();
        //
    }

    //--------------------------------------------------
    //nextDouble
    {
        m_dRv = rndR.nextDouble();
        //
    }

    //--------------------------------------------------
    //nextChar
    {
        m_chRv = rndR.nextChar();
        //
    }

    //--------------------------------------------------
    //nextFigure
    {
        m_chRv = rndR.nextFigure();
        //
    }

    //--------------------------------------------------
    //nextGaussian
    {
        m_dRv = rndR.nextGaussian();
        //
    }
#endif

    xTEST_CASE("CxRandom::next", a_caseLoops)
    {
        cint_t data[][2] = {
            {0, 100},
            {500, 1000},
            {50000, 100000},
            {-100, 0},
            {-1000, 500},
            {-100000, 50000}
        };

        CxRandom random;
        random.setSeed();

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            clong_t min = data[i][0];
            clong_t max = data[i][1];

            m_liRv = random.next(min, max);
            xTEST_EQ(true, m_liRv >= min && m_liRv <= max);
        }
    }

#if xTODO
    xTEST_CASE("CxRandom::sGetString", a_caseLoops)
    {
        std::csize_t cuiStrSize = 10;

        for (size_t i = 0; i < 10; ++ i) {
            CxRandom::setSeed();

            m_sRv = CxRandom::nextString(cuiStrSize);
            xTEST_EQ(cuiStrSize, m_sRv.size());
            //xTRACEV(xT("\ti: %s"), m_sRv.c_str());
        }
    }
#endif
}
//------------------------------------------------------------------------------
