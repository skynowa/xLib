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

    xTEST_CASE("CxRandom::nextBool", a_caseLoops)
    {
        CxRandom random;
        random.setSeed();

        m_bRv = random.nextBool();
        xTEST_NA(m_bRv);
    }

    xTEST_CASE("CxRandom::nextChar", a_caseLoops)
    {
        CxRandom random;
        random.setSeed();

        m_chRv = random.nextChar<char>();
        xTEST_NA(m_chRv);

        m_chRv = random.nextChar<tchar_t>();
        xTEST_NA(m_chRv);

        m_ucRv = random.nextChar<uchar_t>();
        xTEST_NA(m_ucRv);
    }

    xTEST_CASE("CxRandom::nextInt", a_caseLoops)
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

            m_liRv = random.nextInt(min, max);
            xTEST_EQ(true, m_liRv >= min && m_liRv <= max);
        }
    }

    xTEST_CASE("CxRandom::nextFloat", a_caseLoops)
    {
        cfloat_t data[][2] = {
            {0.0, 100.0},
            {500.0, 1000.0},
            {50000.0, 100000.0},
            {-100.0, 0.0},
            {-1000.0, 500.0},
            {-100000.0, 50000.0}
        };

        CxRandom random;
        random.setSeed();

        // float
        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            cfloat_t min = data[i][0];
            cfloat_t max = data[i][1];

            m_fRv = random.nextFloat(min, max);
            xTEST_EQ(true, m_liRv >= min && m_liRv <= max);
        }

        // double
        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            cdouble_t min = data[i][0];
            cdouble_t max = data[i][1];

            m_dRv = random.nextFloat(min, max);
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
