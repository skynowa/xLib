/**
 * \file  CxDll.h
 * \brief dynamic linking loader
 */


#pragma once

#ifndef xLib_CxDllH
#define xLib_CxDllH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDll
    /// dynamic linking loader
{
public:
#if   xOS_ENV_WIN
    typedef FARPROC  proc_address_t;
#else xOS_ENV_UNIX
    typedef void_t * proc_address_t;
#endif
                    CxDll();
        ///< constructor
    virtual        ~CxDll();
        ///< destructor

    bool_t          isLoaded() const xWARN_UNUSED_RV;
        ///< is loaded
    void_t          load(std::ctstring_t &dllPath);
        ///< load
    bool_t          isProcExists(std::ctstring_t &procName) const xWARN_UNUSED_RV;
        ///< is function exists
    proc_address_t  procAddress(std::ctstring_t &procName) const xWARN_UNUSED_RV;
        ///< get address of an exported function or variable

private:
#if   xOS_ENV_WIN
    typedef HMODULE  handle_t;
#else xOS_ENV_UNIX
    typedef void_t * handle_t;
#endif

    handle_t        _dll;   ///< dll module handle

    void_t          _destruct();
        ///< free

    xNO_COPY_ASSIGN(CxDll)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxDll.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxDllH
