/****************************************************************************
* Class name:  CxSleeper
* Description: like ::Sleep()
* File name:   CxSleeper.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.07.2009 12:54:38
*
*****************************************************************************/


#ifndef xLib_Sync_CxSleeperH
#define xLib_Sync_CxSleeperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxEvent.h>
//---------------------------------------------------------------------------
#if xTEMP_DISABLED
    class CxSleeper :
        public CxNonCopyable
    {
        public:
                     CxSleeper  ();
            virtual ~CxSleeper  ();

            BOOL     bSleep     (const ULONG culTimeout) const;
            BOOL     bWakeUp    () const;
            BOOL     bIsSleeping() const;

        private:
            CxEvent  _m_objEvent;
    };
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSleeperH
