/****************************************************************************
* Class name:  CxAsyncSocket
* Description: async socket
* File name:   CxAsyncSocket.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     16.11.2010 15:25:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Net_CxAsyncSocketH
#define xLib_Net_CxAsyncSocketH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxAsyncSocket : public CxNonCopyable {
	public:
				 CxAsyncSocket();
		virtual ~CxAsyncSocket();

	private:
		BOOL     _m_bRes;

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxAsyncSocketH
