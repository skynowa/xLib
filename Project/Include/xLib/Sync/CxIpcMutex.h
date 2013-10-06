/**
 * \file  CxIpcMutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcMutex :
    private CxNonCopyable
    /// mutex
{
public:
#if xOS_ENV_WIN
    typedef CxHandle handle_t;
#else
    typedef sem_t *  handle_t;
#endif

                     CxIpcMutex();
    virtual         ~CxIpcMutex();

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create(std::ctstring_t &csName);
        ///< create
    void_t           open(std::ctstring_t &csName);
        ///< open
    void_t           lock(culong_t &culTimeoutMsec) const;
        ///< unlock by timeout in msec
    void_t           unlock() const;
        ///< lock

private:
    handle_t         _m_hHandle;   ///< mutex native handle
    std::tstring_t   _m_sName;     ///< mutex name
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
