/**
 * \file   CxTest_CxRandom.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxRandom.h>


//---------------------------------------------------------------------------
CxTest_CxRandom::CxTest_CxRandom() {

}
//---------------------------------------------------------------------------
CxTest_CxRandom::~CxTest_CxRandom() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxRandom::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    #if xTODO
        CxRandom rndR;

        //--------------------------------------------------
        //bSetSeed
        {
            m_bRv = rndR.bSetSeed( static_cast<ulong_t>( time(NULL) ) );
            xTEST_EQ(true, m_bRv);
        }

        //--------------------------------------------------
        //iNextInt
        {
            m_iRv = rndR.iNextInt();
            xTEST_LESS(0, m_iRv);
        }

        //--------------------------------------------------
        //iNextInt
        {
            m_iRv = rndR.iNextInt(100);
            xTEST_LESS_EQ(0, m_iRv);
        }

        //--------------------------------------------------
        //iNextInt
        {
            m_iRv = rndR.iNextInt(100, 200);
            xTEST_EQ(true, 100 <= m_iRv && 200 >= m_iRv);
        }

        //--------------------------------------------------
        //liNextLong
        {
            m_liRv = rndR.liNextLong();
            xTEST_LESS(0L, m_liRv);
        }

        //--------------------------------------------------
        //bNextBoolean
        {
            m_blRes = rndR.bNextBoolean();
            xTEST_EQ(true, true == m_blRes || false == m_blRes);
        }

        //--------------------------------------------------
        //fNextFloat
        {
            m_fRv = rndR.fNextFloat();
            //
        }

        //--------------------------------------------------
        //bNextDouble
        {
            m_dRv = rndR.bNextDouble();
            // 
        }

        //--------------------------------------------------
        //chNextChar
        {
            m_chRv = rndR.chNextChar();
            //
        }

        //--------------------------------------------------
        //chNextFigure
        {
            m_chRv = rndR.chNextFigure();
            //
        }

        //--------------------------------------------------
        //dNextGaussian
        {
            m_dRv = rndR.dNextGaussian();
            //
        }
    #endif

    xTEST_CASE(CxRandom::vSetSeed liGetInt liGetIntEx, cullCaseLoops)
    {
        const long_t caliData[][2] = {
            {0, 100},
            {500, 1000},
            {50000, 100000},
            {-100, 0},
            {-1000, 500},
            {-100000, 50000}
        };

        for (size_t i = 0; i < xARRAY_SIZE(caliData); ++ i) {
            const long_t cliMin = caliData[i][0];
            const long_t cliMax = caliData[i][1];

            CxRandom::vSetSeed();

            m_liRv = CxRandom::liInt(cliMin, cliMax);
            xTEST_EQ(true, m_liRv >= cliMin && m_liRv <= cliMax);

            m_liRv = CxRandom::liIntEx(cliMin, cliMax);
            xTEST_EQ(true, m_liRv >= cliMin && m_liRv <= cliMax);
        }
    }

    xTEST_CASE(CxRandom::sGetString, cullCaseLoops)
    {
        const size_t cuiStrSize = 10;

        for (size_t i = 0; i < 10; ++ i) {
            CxRandom::vSetSeed();

            m_sRv = CxRandom::sString(cuiStrSize);
            xTEST_EQ(cuiStrSize, m_sRv.size());
            //xTRACEV(xT("\ti: %s"), m_sRv.c_str());
        }
    }
}
//---------------------------------------------------------------------------
