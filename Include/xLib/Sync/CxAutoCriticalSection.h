/****************************************************************************
* Class name:  CxAutoCriticalSection
* Description: ������ � ������������ �������� � �����
* File name:   CxAutoCriticalSection.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 21:16:33
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxAutoCriticalSectionH
#define xLib_Sync_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
////#include <xLib/Sync/CxSleeper.h>
//---------------------------------------------------------------------------
class CxAutoCriticalSection : public CxNonCopyable {
	public:
						   CxAutoCriticalSection(CxCriticalSection &csCS);
						   ////CxAutoCriticalSection(CxCriticalSection &csCS, BOOL bTry, ULONG ulTimeout = 1000);
   		virtual 	      ~CxAutoCriticalSection();

	private:
		CxCriticalSection &_m_csCS;
		////CxSleeper	   _m_slSleeper;	//������
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxAutoCriticalSectionH
