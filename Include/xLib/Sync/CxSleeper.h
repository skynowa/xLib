/**
 * \file  CxSleeper.h
 * \brief sleeper
 */


#ifndef xLib_Sync_CxSleeperH
#define xLib_Sync_CxSleeperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxEvent.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
    class CxSleeper :
        public CxNonCopyable
        /// sleeper
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
