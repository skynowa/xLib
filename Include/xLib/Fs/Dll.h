/**
 * \file  Dll.h
 * \brief dynamic linking loader
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Interface/IValid.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Dll :
    public xl::interface_::IValid
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

///\name Overrides
///\{
	bool_t isOk() const final;
///\}

    void_t load();
        ///< load

	template<typename ProcAddressT>
	ProcAddressT
	symbol(std::ctstring_t &procName) const
	{
		static_assert(
			std::is_pointer_v<ProcAddressT> && std::is_function_v<std::remove_pointer_t<ProcAddressT>>,
			"symbol<T>: T must be a pointer to function type (e.g. Return (__stdcall *)(Args...))");

		proc_address_t paRv = _procAddress_impl(procName);

		return reinterpret_cast<ProcAddressT>(paRv);
	}

private:
    std::ctstring_t _dllPath; ///< file path
    HandleDll       _handle;  ///< dll module handle

xPLATFORM_IMPL:
    void_t         _load_impl();
        ///< load
    proc_address_t _procAddress_impl(std::ctstring_t &procName) const;
        ///< get address of an exported function or variable
};

} // namespace
//-------------------------------------------------------------------------------------------------
