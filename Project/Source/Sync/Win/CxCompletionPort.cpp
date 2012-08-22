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
bool
CxCompletionPort::bCreate(
    ulong_t ulThreadsNum
)
{
    /*DEBUG*/// _m_hCP       - n/a
    /*DEBUG*/// ulThreadsNum - n/a

    _m_hCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, ulThreadsNum);
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bAssociate
bool
CxCompletionPort::bAssociate(
    HANDLE    hFile,
    ULONG_PTR pulCompletionKey
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);
    /*DEBUG*/// hFile
    /*DEBUG*/xASSERT_RET(NULL  != pulCompletionKey,  false);

    HANDLE hRv = ::CreateIoCompletionPort(hFile, _m_hCP.hGet(), pulCompletionKey, 0);
    /*DEBUG*/xASSERT_RET(NULL          != hRv, false);
    /*DEBUG*/xASSERT_RET(_m_hCP.hGet() == hRv, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bGetStatus (Attempts to dequeue an I/O completion packet from the specified I/O completion port.)
bool
CxCompletionPort::bGetStatus(
    LPDWORD       lpNumberOfBytes,
    PULONG_PTR    lpCompletionKey,
    LPOVERLAPPED *lpOverlapped,
    ulong_t       ulMilliseconds
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != lpNumberOfBytes,   false);
    /*DEBUG*/xASSERT_RET(NULL  != lpCompletionKey,   false);
    /*DEBUG*/xASSERT_RET(NULL  != lpOverlapped,      false);
    /*DEBUG*/// ulMilliseconds - n/a

    BOOL blRes = ::GetQueuedCompletionStatus(_m_hCP.hGet(), lpNumberOfBytes, lpCompletionKey, lpOverlapped, ulMilliseconds);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bPostStatus (Posts an I/O completion packet to an I/O completion port.)
bool
CxCompletionPort::bPostStatus(
    ulong_t      ulNumberOfBytesTransferred,
    ULONG_PTR    ulCompletionKey,
    LPOVERLAPPED lpOverlapped
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);
    /*DEBUG*/// ulNumberOfBytesTransferred - n/a
    /*DEBUG*/// ulCompletionKey            - n/a
    /*DEBUG*/xASSERT_RET(NULL  != lpOverlapped,      false);

    BOOL blRes = ::PostQueuedCompletionStatus(_m_hCP.hGet(), ulNumberOfBytesTransferred, ulCompletionKey, lpOverlapped);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
