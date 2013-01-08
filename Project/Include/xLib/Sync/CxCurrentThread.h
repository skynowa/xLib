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
    static bool               isCurrent      (const CxThread::id_t &culId) xWARN_UNUSED_RESULT;
        ///< is current id
    static CxThread::id_t     id             () xWARN_UNUSED_RESULT;
        ///< get the thread identifier of the calling thread
    static CxThread::handle_t handle         () xWARN_UNUSED_RESULT;
        ///< get pseudo handle for the calling thread
    static void               yield          ();
        ///< yield
    static void               sleep          (const ulong_t &culMsec);
        ///< sleep
private:
                              CxCurrentThread();
        ///< constructor
    virtual                  ~CxCurrentThread();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_CxCurrentThreadH
