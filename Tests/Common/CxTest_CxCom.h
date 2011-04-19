/****************************************************************************
* Class name:  CxTest_CxCom
* Description: test CxCom
* File name:   CxTest_CxCom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxComH
#define CxTest_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxCom.h>
//---------------------------------------------------------------------------
class CxTest_CxCom : public CxTest {
	public:
		CxTest_CxCom();
	   ~CxTest_CxCom();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: - CxTest_CxCom (comment)
CxTest_CxCom::CxTest_CxCom() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: - ~CxTest_CxCom (comment)
CxTest_CxCom::~CxTest_CxCom() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxCom::bUnit() {
	/*DEBUG*/

	//-------------------------------------
	//bIsInit
	{
		{
			CxCom cmCom(CxCom::cmMultiThreaded);

			m_bRes = CxCom::bIsInit();
			xASSERT(FALSE != m_bRes);
		}

		m_bRes = CxCom::bIsInit();
		xASSERT(FALSE == m_bRes);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxComH
