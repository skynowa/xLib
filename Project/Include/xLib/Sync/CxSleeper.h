/**
 * \file  CxSleeper.h
 * \brief sleeper
 */


#ifndef xLib_Sync_CxSleeperH
#define xLib_Sync_CxSleeperH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxEvent.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSleeper :
    private CxNonCopyable
    /// sleeper
{
public:
             CxSleeper ();
        ///< constructor
    virtual ~CxSleeper ();
        ///< destructor

    void_t   sleep     (culong_t &culTimeout);
        ///< sleep
    void_t   wakeUp    ();
        ///< wake up
    bool_t   isSleeping() xWARN_UNUSED_RV;
        ///< check for sleeping

private:
    CxEvent  _m_objEvent;    ///< event object
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxSleeperH
