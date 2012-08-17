/**
 * \file  CxCompletionPort.h
 * \brief completion port
 */


#ifndef xLib_Sync_CxCompletionPortH
#define xLib_Sync_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCompletionPort :
    private CxNonCopyable
    /// completion port
{
    public:
                 CxCompletionPort();
        virtual ~CxCompletionPort();

        bool     bCreate         (ulong_t ulThreadsNum /*= 0*/);
        bool     bAssociate      (HANDLE hFile, ULONG_PTR pulCompletionKey);
        bool     bGetStatus      (LPDWORD lpNumberOfBytes, PULONG_PTR lpCompletionKey, LPOVERLAPPED *lpOverlapped, ulong_t ulMilliseconds);
        bool     bPostStatus     (ulong_t ulNumberOfBytesTransferred, ULONG_PTR ulCompletionKey, LPOVERLAPPED lpOverlapped);

    private:
        CxHandle _m_hCP;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxCompletionPortH
