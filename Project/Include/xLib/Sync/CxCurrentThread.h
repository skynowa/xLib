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
    private CxNonCopyable
{
    public:
        static bool               bIsCurrent     (const CxThread::id_t &culId);
            ///< is current id
        static CxThread::id_t     ulGetId        ();
            ///< get the thread identifier of the calling thread
        static CxThread::handle_t hGetHandle     ();
            ///< get pseudo handle for the calling thread
        static bool               bYield         ();
            ///< yield
        static bool               bSleep         (const ulong_t culMsec);
            ///< sleep
    private:
                                  CxCurrentThread();
            ///< constructor
        virtual                  ~CxCurrentThread();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxCurrentThreadH
