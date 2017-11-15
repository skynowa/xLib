/**
 * \file  Dll.h
 * \brief dynamic linking loader
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Dll
    /// dynamic linking loader
{
public:
#if   xENV_WIN
    typedef FARPROC  proc_address_t;
#elif xENV_UNIX
    typedef void_t * proc_address_t;
#endif
                   Dll();
        ///< constructor
    virtual       ~Dll();
        ///< destructor

    HandleDll     &get() xWARN_UNUSED_RV;
        ///< get handle
    bool_t         isLoaded() const xWARN_UNUSED_RV;
        ///< is loaded
    void_t         load(std::ctstring_t &dllPath);
        ///< load
    bool_t         isProcExists(std::ctstring_t &procName) const xWARN_UNUSED_RV;
        ///< is function exists
    proc_address_t procAddress(std::ctstring_t &procName) const xWARN_UNUSED_RV;
        ///< get address of an exported function or variable
    void_t         close();
        ///< close

private:
    HandleDll      _handle;   ///< dll module handle

    xNO_COPY_ASSIGN(Dll)

xPLATFORM_IMPL:
    void_t         _load_impl(std::ctstring_t &dllPath);
        ///< load
    bool_t         _isProcExists_impl(std::ctstring_t &procName) const xWARN_UNUSED_RV;
        ///< is function exists
    proc_address_t _procAddress_impl(std::ctstring_t &procName) const xWARN_UNUSED_RV;
        ///< get address of an exported function or variable
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Dll.cpp"
#endif
