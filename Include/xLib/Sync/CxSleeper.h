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
xNAMESPACE_BEGIN(NxLib)

class CxSleeper :
    public CxNonCopyable
    /// sleeper
{
    public:
                 CxSleeper  ();
            ///< constructor
        virtual ~CxSleeper  ();
            ///< destructor

        BOOL     bSleep     (const ULONG culTimeout);
            ///< sleep
        BOOL     bWakeUp    ();
            ///< wake up
        BOOL     bIsSleeping();
            ///< check for sleeping

    private:
        CxEvent  _m_objEvent;    ///< event object
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSleeperH
