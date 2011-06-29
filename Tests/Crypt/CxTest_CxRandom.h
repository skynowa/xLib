/****************************************************************************
* Class name:  CxTest_CxRandom
* Description: test CxRandom
* File name:   CxTest_CxRandom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxRandomH
#define CxTest_CxRandomH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/CxRandom.h>
//---------------------------------------------------------------------------
class CxTest_CxRandom :
    public CxTest
{
	public:
		CxTest_CxRandom();
		virtual     ~CxTest_CxRandom();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxRandom (constructor)
CxTest_CxRandom::CxTest_CxRandom() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxRandom (destructor)
CxTest_CxRandom::~CxTest_CxRandom() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxRandom::bUnit() {
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

    //--------------------------------------------------
    //sGetString
    {
        const size_t cuiStrSize = 10;

        for (size_t i = 0; i < 10; ++ i) {
            m_sRes = CxRandom::sGetString(cuiStrSize);
            //xTRACEV(xT("i: %s"), m_sRes.c_str());
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxRandomH

