/****************************************************************************
* Class name:  CxMimeBody
* Description: ���� ��������� ������ (RFC 822)
* File name:   CxMimeBody.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     06.07.2009 19:11:02
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxMimeBodyH
#define CxMimeBodyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxMimeBody {
	public:
						CxMimeBody();
					   ~CxMimeBody();
	
	private:
		TStringMultiMap _m_mmsBody;
};
//---------------------------------------------------------------------------
#endif
