/****************************************************************************
* Class name:  CxAutoCriticalSection
* Description: auto critical section
* File name:   CxAutoCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 21:16:33
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
