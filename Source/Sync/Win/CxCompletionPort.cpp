/**
 * \file  CxCompletionPort.cpp
 * \brief completion port
 */


#include <xLib/Sync/Win/CxCompletionPort.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCompletionPort
CxCompletionPort::CxCompletionPort() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
//DONE: ~CxCompletionPort
/*virtual*/
CxCompletionPort::~CxCompletionPort() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
//DONE: bCreate (Creates an input/output (I/O) completion port and associates it with a specified file handle, or creates an I/O completion port that is not yet associated with a file handle, allowing association at a later time.)
BOOL
CxCompletionPort::bCreate(
    ULONG ulThreadsNum
)
{
    /*DEBUG*/// _m_hCP       - n/a
    /*DEBUG*/// ulThreadsNum - n/a

    _m_hCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, ulThreadsNum);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hCP.bIsValid(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bAssociate
BOOL
CxCompletionPort::bAssociate(
    HANDLE    hFile,
    ULONG_PTR pulCompletionKey
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hCP.bIsValid(), FALSE);
    /*DEBUG*/// hFile
    /*DEBUG*/xASSERT_RET(NULL  != pulCompletionKey,  FALSE);

    HANDLE hRes = ::CreateIoCompletionPort(hFile, _m_hCP, pulCompletionKey, 0);
    /*DEBUG*/xASSERT_RET(NULL   != hRes, FALSE);
    /*DEBUG*/xASSERT_RET(_m_hCP == hRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetStatus (Attempts to dequeue an I/O completion packet from the specified I/O completion port.)
BOOL
CxCompletionPort::bGetStatus(
    LPDWORD       lpNumberOfBytes,
    PULONG_PTR    lpCompletionKey,
    LPOVERLAPPED *lpOverlapped,
    ULONG         ulMilliseconds
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hCP.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != lpNumberOfBytes,   FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != lpCompletionKey,   FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != lpOverlapped,      FALSE);
    /*DEBUG*/// ulMilliseconds - n/a

    BOOL bRes = ::GetQueuedCompletionStatus(_m_hCP, lpNumberOfBytes, lpCompletionKey, lpOverlapped, ulMilliseconds);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPostStatus (Posts an I/O completion packet to an I/O completion port.)
BOOL
CxCompletionPort::bPostStatus(
    ULONG        ulNumberOfBytesTransferred,
    ULONG_PTR    ulCompletionKey,
    LPOVERLAPPED lpOverlapped
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hCP.bIsValid(), FALSE);
    /*DEBUG*/// ulNumberOfBytesTransferred - n/a
    /*DEBUG*/// ulCompletionKey            - n/a
    /*DEBUG*/xASSERT_RET(NULL  != lpOverlapped,      FALSE);

    BOOL bRes = ::PostQueuedCompletionStatus(_m_hCP, ulNumberOfBytesTransferred, ulCompletionKey, lpOverlapped);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
