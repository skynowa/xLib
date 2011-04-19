/****************************************************************************
* Class name:  CxAsyncSocket
* Description: async socket
* File name:   CxAsyncSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     16.11.2010 15:25:38
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
