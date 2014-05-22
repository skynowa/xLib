/**
 * \file  CxIpcMutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxIpcMutex
    /// mutex
{
public:
#if   xENV_WIN
    typedef CxHandle handle_t;
#elif xENV_UNIX
    typedef sem_t *  handle_t;
#endif

                     CxIpcMutex() {}
    virtual         ~CxIpcMutex() {}

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create(std::ctstring_t &name);
        ///< create
    void_t           open(std::ctstring_t &name);
        ///< open
    void_t           lock(culong_t &timeoutMsec) const;
        ///< unlock by timeout in msec
    void_t           unlock() const;
        ///< lock

private:
    handle_t         _handle;   ///< mutex native handle
    std::tstring_t   _name;     ///< mutex name

    xNO_COPY_ASSIGN(CxIpcMutex)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxIpcMutex.inl"
