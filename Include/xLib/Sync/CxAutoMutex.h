/****************************************************************************
* Class name:  CxMutexScopeLock
* Description: ������� � �����
* File name:   CxAutoMutex.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     16.12.2009 10:06:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxAutoMutexH
#define xLib_Sync_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxMutex.h>
//---------------------------------------------------------------------------
class CxAutoMutex : public CxNonCopyable {
	public:
				 CxAutoMutex(CxMutex &mtMutex);
		virtual ~CxAutoMutex();

	private:
		CxMutex &_m_mtMutex;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxAutoMutexH
