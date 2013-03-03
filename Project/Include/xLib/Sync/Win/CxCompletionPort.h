/**
 * \file  CxCompletionPort.h
 * \brief completion port
 */


#ifndef xLib_Sync_CxCompletionPortH
#define xLib_Sync_CxCompletionPortH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCompletionPort :
    private CxNonCopyable
    /// completion port
{
public:
             CxCompletionPort();
    virtual ~CxCompletionPort();

    void_t     create          (culong_t &culThreadsNum /* = 0UL */);
    void_t     associate       (const HANDLE &chFile, ULONG_PTR pulCompletionKey);
    void_t     status          (LPDWORD lpNumberOfBytes, PULONG_PTR lpCompletionKey,
                              LPOVERLAPPED *lpOverlapped, culong_t &culMilliseconds);
    void_t     postStatus      (culong_t &culNumberOfBytesTransferred,
                              ULONG_PTR ulCompletionKey, LPOVERLAPPED lpOverlapped);

private:
    CxHandle _m_hHandle;
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxCompletionPortH
