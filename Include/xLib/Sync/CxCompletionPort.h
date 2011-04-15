/****************************************************************************
* Class name:  CCompletionPort
* Description: ���� ����������
* File name:   CCompletionPort.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.02.2010 14:28:40
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxCompletionPortH
#define xLib_Sync_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxCompletionPort : public CxNonCopyable  {
	public:
		                CxCompletionPort();
	    virtual        ~CxCompletionPort();

		BOOL            bCreate         (ULONG ulThreadsNum /*= 0*/);
		BOOL            bAssociate      (HANDLE hFile, ULONG_PTR pulCompletionKey);
		BOOL            bGetStatus      (LPDWORD lpNumberOfBytes, PULONG_PTR lpCompletionKey, LPOVERLAPPED *lpOverlapped, ULONG ulMilliseconds);
		BOOL            bPostStatus     (ULONG ulNumberOfBytesTransferred, ULONG_PTR ulCompletionKey, LPOVERLAPPED lpOverlapped);

	private:
		BOOL            _m_bRes;
		CxHandleT<NULL> _m_hCP;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxCompletionPortH
