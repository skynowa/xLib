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
/*virtual*/
bool
CxTest_CxRandom::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    #if xTODO
        CxRandom rndR;

        //--------------------------------------------------
        //bSetSeed
        {
            m_bRes = rndR.bSetSeed( static_cast<ulong_t>( time(NULL) ) );
            xTEST_EQ(true, m_bRes);
        }

        //--------------------------------------------------
        //iNextInt
        {
            m_iRes = rndR.iNextInt();
            xTEST_LESS(0, m_iRes);
        }

        //--------------------------------------------------
        //iNextInt
        {
            m_iRes = rndR.iNextInt(100);
            xTEST_LESS_EQ(0, m_iRes);
        }

        //--------------------------------------------------
        //iNextInt
        {
            m_iRes = rndR.iNextInt(100, 200);
            xTEST_EQ(true, 100 <= m_iRes && 200 >= m_iRes);
        }

        //--------------------------------------------------
        //liNextLong
        {
            m_liRes = rndR.liNextLong();
            xTEST_LESS(0L, m_liRes);
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
            m_fRes = rndR.fNextFloat();
            //xASSERT
        }

        //--------------------------------------------------
        //bNextDouble
        {
            m_dRes = rndR.bNextDouble();
            //xASSERT
        }

        //--------------------------------------------------
        //chNextChar
        {
            m_chRes = rndR.chNextChar();
            //xASSERT
        }

        //--------------------------------------------------
        //chNextFigure
        {
            m_chRes = rndR.chNextFigure();
            //xASSERT
        }

        //--------------------------------------------------
        //dNextGaussian
        {
            m_dRes = rndR.dNextGaussian();
            //xASSERT
        }
    #endif

    //-------------------------------------
    //bSetSeed, liGetInt, liGetIntEx
    xTEST_CASE(cullCaseLoops)
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

            m_bRes = CxRandom::bSetSeed();
            xTEST_EQ(true, m_bRes);

            m_liRes = CxRandom::liGetInt(cliMin, cliMax);
            xTEST_EQ(true, m_liRes >= cliMin && m_liRes <= cliMax);

            m_liRes = CxRandom::liGetIntEx(cliMin, cliMax);
            xTEST_EQ(true, m_liRes >= cliMin && m_liRes <= cliMax);
        }
    }

    //--------------------------------------------------
    //sGetString
    xTEST_CASE(cullCaseLoops)
    {
        const size_t cuiStrSize = 10;

        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = CxRandom::bSetSeed();
            xTEST_EQ(true, m_bRes);

            m_sRes = CxRandom::sGetString(cuiStrSize);
            xTEST_EQ(cuiStrSize, m_sRes.size());
            //xTRACEV(xT("\ti: %s"), m_sRes.c_str());
        }
    }

    return true;
}
//---------------------------------------------------------------------------
