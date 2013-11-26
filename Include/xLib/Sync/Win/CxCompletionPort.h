/**
 * \file  CxCompletionPort.h
 * \brief completion port
 */


#pragma once

#ifndef xLib_CxCompletionPortH
#define xLib_CxCompletionPortH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCompletionPort
    /// completion port
{
public:
             CxCompletionPort();
    virtual ~CxCompletionPort();

    void_t   create(culong_t &threadsNum /* = 0UL */);
    void_t   associate(const HANDLE &file, ULONG_PTR completionKey) const;
    void_t   status(LPDWORD numberOfBytes, PULONG_PTR completionKey, LPOVERLAPPED *overlapped,
                culong_t &msec) const;
    void_t   postStatus(culong_t &numOfBytesTransferred, ULONG_PTR completionKey,
                LPOVERLAPPED overlapped) const;

private:
    CxHandle _handle;

xNO_COPY_ASSIGN(CxCompletionPort)
};

xNAMESPACE_END(NxLib)

#endif
//-------------------------------------------------------------------------------------------------
#include "CxCompletionPort.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxCompletionPortH
