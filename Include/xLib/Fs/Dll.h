/**
 * \file  Dll.h
 * \brief dynamic linking loader
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Dll
    /// dynamic linking loader
{
public:
#if   xENV_WIN
    using proc_address_t = FARPROC;
#elif xENV_UNIX
    using proc_address_t = void_t *;
#endif

///\name ctors, dtor
///\{
	explicit  Dll(std::ctstring_t &dllPath);
	virtual  ~Dll() = default;

	xNO_DEFAULT_CONSTRUCT(Dll);
	xNO_COPY_ASSIGN(Dll);
///\}

    HandleDll     &get();
        ///< get handle
    void_t         load();
        ///< load

    template<typename ProcAddressT>
    ProcAddressT
    proc(std::ctstring_t &procName) const
    {
        proc_address_t paRv = procAddress(procName);
        xCHECK_RET(paRv == nullptr, ProcAddressT{});

        return reinterpret_cast<ProcAddressT>(paRv);
    }

private:
    std::ctstring_t _dllPath; ///< file path
    HandleDll       _handle;  ///< dll module handle

    bool_t         isProcExists(std::ctstring_t &procName) const;
        ///< is function exists
    proc_address_t procAddress(std::ctstring_t &procName) const;
        ///< get address of an exported function or variable

xPLATFORM_IMPL:
    void_t         _load_impl();
        ///< load
    bool_t         _isProcExists_impl(std::ctstring_t &procName) const;
        ///< is function exists
    proc_address_t _procAddress_impl(std::ctstring_t &procName) const;
        ///< get address of an exported function or variable
};

} // namespace
//-------------------------------------------------------------------------------------------------
