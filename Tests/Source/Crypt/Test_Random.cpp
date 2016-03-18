/**
 * \file   Test_Random.cpp
 * \brief
 */


#include <Test/Crypt/Test_Random.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Random)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Random::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("nextBool", a_caseLoops)
    {
        StdRandom random;

        m_bRv = random.nextBool();
        xTEST_NA(m_bRv);
    }

    xTEST_CASE("nextChar", a_caseLoops)
    {
        StdRandom random;

        m_chRv = random.nextChar<char>();
        xTEST_NA(m_chRv);

        m_chRv = random.nextChar<tchar_t>();
        xTEST_NA(m_chRv);

        m_ucRv = random.nextChar<uchar_t>();
        xTEST_NA(m_ucRv);
    }

    xTEST_CASE("nextInt", a_caseLoops)
    {
        cint_t data[][2] = {
            {0, 100},
            {500, 1000},
            {50000, 100000},
            {-100, 0},
            {-1000, 500},
            {-100000, 50000}
        };

        StdRandom random;

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            clong_t min = data[i][0];
            clong_t max = data[i][1];

            m_liRv = random.nextInt(min, max);
            xTEST_EQ(true, m_liRv >= min && m_liRv <= max);
        }
    }

    xTEST_CASE("nextFloat", a_caseLoops)
    {
        // float
        {
            cfloat_t data[][2] = {
                {0.0, 100.0},
                {500.0, 1000.0},
                {50000.0, 100000.0},
                {-100.0, 0.0},
                {-1000.0, 500.0},
                {-100000.0, 50000.0}
            };

            StdRandom random;

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                cfloat_t min = data[i][0];
                cfloat_t max = data[i][1];

                m_fRv = random.nextFloat(min, max);
                xTEST_EQ(true, m_fRv >= min && m_fRv <= max);
            }
        }

        // double
        {
            cdouble_t data[][2] = {
                {0.0, 100.0},
                {500.0, 1000.0},
                {50000.0, 100000.0},
                {-100.0, 0.0},
                {-1000.0, 500.0},
                {-100000.0, 50000.0}
            };

            StdRandom random;

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                cdouble_t min = data[i][0];
                cdouble_t max = data[i][1];

                m_dRv = random.nextFloat(min, max);
                xTEST_EQ(true, m_dRv >= min && m_dRv <= max);
            }
        }
    }

#if xTODO
    xTEST_CASE("nextString", a_caseLoops)
    {
        std::csize_t cuiStrSize = 10;

        for (size_t i = 0; i < 10; ++ i) {
            Random::setSeed();

            m_sRv = Random::nextString(cuiStrSize);
            xTEST_EQ(cuiStrSize, m_sRv.size());
            //xTRACEV(xT("\ti: %s"), m_sRv.c_str());
        }
    }
#endif
}
//-------------------------------------------------------------------------------------------------
