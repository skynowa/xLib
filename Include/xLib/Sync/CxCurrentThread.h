/**
 * \file   CxCurrentThread.h
 * \brief
 */


#ifndef xLib_CxCurrentThreadH
#define xLib_CxCurrentThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxThread.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCurrentThread :
    public CxNonCopyable
{
    public:
                                  CxCurrentThread();
            ///< constructor
        virtual                  ~CxCurrentThread();
            ///< destructor

        static CxThread::TxId     ulGetId        ();
            ///< get the thread identifier of the calling thread
        static BOOL               bIsCurrent     (const CxThread::TxId culId);
            ///< is current id
        static CxThread::TxHandle hGetHandle     ();
            ///< get pseudo handle for the calling thread
        static BOOL               bYield         ();
            ///< yield
        static BOOL               bSleep         (const ULONG culMsec);
            ///< sleep
    private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxCurrentThreadH
