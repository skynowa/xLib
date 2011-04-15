/****************************************************************************
* Class name:  CxCom
* Description: COM
* File name:   CxCom.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2009 15:27:35
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxComH
#define xLib_Common_Win_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <Objbase.h>
//---------------------------------------------------------------------------
class CxCom : public CxNonCopyable {
	public:
		//concurrency model 
		//the COINIT_APARTMENTTHREADED and COINIT_MULTITHREADED flags cannot both be set
		enum EConcurrencyModel {
			cmApartmentThreaded = COINIT_APARTMENTTHREADED,
			cmMultiThreaded     = COINIT_MULTITHREADED,
			cmDisableOleIdde    = COINIT_DISABLE_OLE1DDE,
			cmSpeedOverMemory   = COINIT_SPEED_OVER_MEMORY
		};

				    CxCom  (EConcurrencyModel cmCoModel/* = cmMultiThreaded*/);
		virtual    ~CxCom  ();
		
		//static
		static BOOL bIsInit();
	
	private:	
		ULONG       _m_ulConModel;
		static LONG _ms_lInitCount;
};
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxComH
