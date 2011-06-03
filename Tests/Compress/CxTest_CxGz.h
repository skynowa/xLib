/****************************************************************************
* Class name:  CxTest_CxGz
* Description: test CxGz
* File name:   CxTest_CxGz.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxGzH
#define CxTest_CxGzH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Compress/Linux/CxGz.h>
//---------------------------------------------------------------------------
class CxTest_CxGz :
    public CxTest
{
	public:
		CxTest_CxGz();
		virtual     ~CxTest_CxGz();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxGz (constructor)
CxTest_CxGz::CxTest_CxGz() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxGz (destructor)
CxTest_CxGz::~CxTest_CxGz() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxGz::bUnit() {
    CxGz gzGz;

//    INT   iFileIn,
//    INT   iFileOut,
//    const tString csOriginName = xT("OriginName");
//
//    m_bRes = gzGz.bCompress(INT iFileIn, INT iFileOut, const tString &csOriginName);
//    xASSERT(FALSE != m_bRes);
//
//
//
//
//
//
//    m_bRes = gzGz.bUncompress(INT iFileIn, INT iFileOut);
//    xASSERT(FALSE != m_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxGzH

