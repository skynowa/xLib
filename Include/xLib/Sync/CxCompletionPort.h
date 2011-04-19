/****************************************************************************
* Class name:  CCompletionPort
* Description: completion port
* File name:   CCompletionPort.h

* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.02.2010 14:28:40
*
*****************************************************************************/


#ifndef xLib_Sync_CxCompletionPortH
#define xLib_Sync_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandle.h>
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
		CxHandle _m_hCP;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxCompletionPortH
