/**
 * \file  CxCompletionPort.cpp
 * \brief completion port
 */


#include <xLib/Sync/Win/CxCompletionPort.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCompletionPort::CxCompletionPort() :
    _m_hHandle()
{

}
//---------------------------------------------------------------------------
/* virtual */
CxCompletionPort::~CxCompletionPort() {

}
//---------------------------------------------------------------------------
void
CxCompletionPort::vCreate(
    const ulong_t &a_culThreadsNum
)
{
    // _m_hCP       - n/a
    // ulThreadsNum - n/a

    _m_hHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, a_culThreadsNum);
    xTEST_EQ(true, _m_hHandle.isValid());
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vAssociate(
    const HANDLE  &a_chFile,
    ULONG_PTR      a_pulCompletionKey
)
{
    xTEST_EQ(true, _m_hHandle.isValid());
    // hFile

#if xARCH_X86
    xTEST_DIFF(0UL, a_pulCompletionKey);
#else
    xTEST_PTR(a_pulCompletionKey);
#endif

    HANDLE hRv = ::CreateIoCompletionPort(a_chFile, _m_hHandle.get(), a_pulCompletionKey, 0);
    xTEST_EQ(xNATIVE_HANDLE_INVALID, hRv);
    xTEST_EQ(_m_hHandle.get(), hRv);
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vStatus(
    LPDWORD        a_lpNumberOfBytes,
    PULONG_PTR     a_lpCompletionKey,
    LPOVERLAPPED  *a_lpOverlapped,
    const ulong_t &a_culMilliseconds
)
{
    xTEST_EQ(true, _m_hHandle.isValid());
    xTEST_PTR(a_lpNumberOfBytes);
    xTEST_PTR(a_lpCompletionKey);
    xTEST_PTR(a_lpOverlapped);
    // ulMilliseconds - n/a

    BOOL blRes = ::GetQueuedCompletionStatus(_m_hHandle.get(), a_lpNumberOfBytes, a_lpCompletionKey, a_lpOverlapped, a_culMilliseconds);
    xTEST_DIFF(FALSE, blRes);
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vPostStatus(
    const ulong_t &a_culNumberOfBytesTransferred,
    ULONG_PTR      a_ulCompletionKey,
    LPOVERLAPPED   a_lpOverlapped
)
{
    xTEST_EQ(true, _m_hHandle.isValid());
    // ulNumberOfBytesTransferred - n/a
    // ulCompletionKey            - n/a
    xTEST_PTR(a_lpOverlapped);

    BOOL blRes = ::PostQueuedCompletionStatus(_m_hHandle.get(), a_culNumberOfBytesTransferred, a_ulCompletionKey, a_lpOverlapped);
    xTEST_DIFF(FALSE, blRes);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
