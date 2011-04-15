/****************************************************************************
* Class name:  CxSleeper
* Description: ������ ::Sleep()
* File name:   CxSleeper.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.07.2009 12:54:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxSleeperH
#define xLib_Sync_CxSleeperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxEvent.h>
//---------------------------------------------------------------------------
class CxSleeper : public CxNonCopyable {
	public:
         	     CxSleeper  ();
		virtual ~CxSleeper  ();

		BOOL     bSleep     (ULONG ulTimeout) const;
		BOOL     bWakeUp    () const;
		BOOL     bIsSleeping() const;

	private:
        CxEvent _m_objEvent; 
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxSleeperH
