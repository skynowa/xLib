/****************************************************************************
* Class name:  CxTest_bGetUsbInfo
* Description: test bGetUsbInfo
* File name:   CxTest_bGetUsbInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_bGetUsbInfoH
#define CxTest_bGetUsbInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Units/bGetUsbInfo.h>
//---------------------------------------------------------------------------
class CxTest_bGetUsbInfo : public CxTest {
	public:
		CxTest_bGetUsbInfo();
		virtual     ~CxTest_bGetUsbInfo();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_bGetUsbInfo (constructor)
CxTest_bGetUsbInfo::CxTest_bGetUsbInfo() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_bGetUsbInfo (destructor)
CxTest_bGetUsbInfo::~CxTest_bGetUsbInfo() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_bGetUsbInfo::bUnit() {
	//-------------------------------------
	//bGetUsbInfo
	{
		const tstring        csDrive = _T("I:");
		std::vector<tstring> vecsInfo;

		g_bRes = bGetUsbInfo(csDrive, &vecsInfo);
		XASSERT(TRUE == g_bRes);

		XASSERT(_T("\\??\\USB")                              == vecsInfo.at(0));
		XASSERT(_T("Vid_058f&Pid_6387")                      == vecsInfo.at(1));
		XASSERT(_T("3DH5R5EL")                               == vecsInfo.at(2));
		XASSERT(_T("{a5dcbf10-6530-11d2-901f-00c04fb951ed}") == vecsInfo.at(3));

		//assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
		//std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
	}

	{
		////const tstring        csDrive = _T("Y:");
		////std::vector<tstring> vecsInfo;

		////g_bRes = bGetUsbInfo(csDrive, &vecsInfo);
		////XASSERT(TRUE == g_bRes);

		////XASSERT(_T("\\??\\USB")                              == vecsInfo.at(0));
		////XASSERT(_T("Vid_058f&Pid_6387")                      == vecsInfo.at(1));
		////XASSERT(_T("3DH5R5EL")                               == vecsInfo.at(2));
		////XASSERT(_T("{a5dcbf10-6530-11d2-901f-00c04fb951ed}") == vecsInfo.at(3));

		//////assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
		//////std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
	}


    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_bGetUsbInfoH

