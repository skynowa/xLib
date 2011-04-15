/****************************************************************************
* Class name:  CxMimeMessage
* Description: �������� ��������� (RFC 822)
* File name:   CxMimeMessage.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     06.07.2009 19:09:16
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Net_CxMimeMessageH
#define xLib_Net_CxMimeMessageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>
//---------------------------------------------------------------------------
class CxMimeMessage : public CxNonCopyable {
	public:
				CxMimeMessage();
			   ~CxMimeMessage(); 
		static BOOL bParse          (const tString &csRawMessage, CxMimeHeader &Header, CxMimeBody &Body); 
		static BOOL	bLoadFromRawFile(const tString &csFilePath);	   //csFilePath - raw msg
		static BOOL bSaveToRawFile  (const tString &csFilePath);       //csFilePath - raw msg
	   
	private:
		tString _m_csRawMessage;
};
//---------------------------------------------------------------------------
#endif	//xLib_Net_CxMimeMessageH
