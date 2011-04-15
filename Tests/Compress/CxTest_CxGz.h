/****************************************************************************
* Class name:  CxTest_CxGz
* Description: test CxGz
* File name:   CxTest_CxGz.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxGzH
#define CxTest_CxGzH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Compress/Linux/CxGz.h>
//---------------------------------------------------------------------------
class CxTest_CxGz : public CxTest {
	public:
		CxTest_CxGz();
	   ~CxTest_CxGz();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxGz (constructor)
CxTest_CxGz::CxTest_CxGz() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxGz (destructor)
CxTest_CxGz::~CxTest_CxGz() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
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

