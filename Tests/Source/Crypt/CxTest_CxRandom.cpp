/****************************************************************************
* Class name:  CxTest_CxRandom
* Description: test CxRandom
* File name:   CxTest_CxRandom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Crypt/CxTest_CxRandom.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxRandom
CxTest_CxRandom::CxTest_CxRandom() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxRandom
CxTest_CxRandom::~CxTest_CxRandom() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxRandom::bUnit() {
#if xTODO
	CxRandom rndR;

    //--------------------------------------------------
    //bSetSeed
    {
        m_bRes = rndR.bSetSeed( static_cast<ULONG>(time(NULL)) );
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //iNextInt
    {
        m_iRes = rndR.iNextInt();
        xASSERT(0 < m_iRes);
    }

    //--------------------------------------------------
    //iNextInt
    {
        m_iRes = rndR.iNextInt(100);
        xASSERT(0 < m_iRes);
    }

    //--------------------------------------------------
    //iNextInt
    {
        m_iRes = rndR.iNextInt(100, 200);
        xASSERT(100 <= m_iRes && 200 >= m_iRes);
    }

    //--------------------------------------------------
    //liNextLong
    {
        m_liRes = rndR.liNextLong();
        xASSERT(0 < m_liRes);
    }

    //--------------------------------------------------
    //bNextBoolean
    {
        m_blRes = rndR.bNextBoolean();
        xASSERT(true == m_blRes || false == m_blRes);
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
    {
        const LONG caliData[][2] = {
            {0, 100},
            {500, 1000},
            {50000, 100000},
            {-100, 0},
            {-1000, 500},
            {-100000, 50000}
        };

        for (size_t i = 0; i < xARRAY_SIZE(caliData); ++ i) {
            const LONG cliMin = caliData[i][0];
            const LONG cliMax = caliData[i][1];

            m_bRes = CxRandom::bSetSeed();
            xASSERT(FALSE != m_bRes);

            m_liRes = CxRandom::liGetInt(cliMin, cliMax);
            xASSERT(m_liRes >= cliMin && m_liRes <= cliMax);

            m_liRes = CxRandom::liGetIntEx(cliMin, cliMax);
            xASSERT(m_liRes >= cliMin && m_liRes <= cliMax);
        }
    }

    //--------------------------------------------------
    //sGetString
    {
        const size_t cuiStrSize = 10;

        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = CxRandom::bSetSeed();
            xASSERT(FALSE != m_bRes);

            m_sRes = CxRandom::sGetString(cuiStrSize);
            //xTRACEV(xT("i: %s"), m_sRes.c_str());
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
