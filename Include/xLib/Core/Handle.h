/**
 * \file  Handle.h
 * \brief handle
 */


#pragma once

//-------------------------------------------------------------------------------------------------
namespace xl::core
{

namespace debug
{

class NativeError;
class StackTrace;
class ErrorReport;
class Debugger;

}

} // namespace
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/HandlePolicy.h>
#include <xLib/Interface/IHandle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T, HandlePolicyType valueT>
class Handle :
    public IHandle<T>
    /// handle
{
public:
///\name ctors, dtor
///\{
              Handle();
    explicit  Handle(const T &handle);
    explicit  Handle(const Handle &handle);
    virtual  ~Handle();
///\}

///\name operators
///\{
	Handle & operator = (const T &handle);
	Handle & operator = (const Handle &handle);
///\}

    T      get() const override;
        ///< get
    void_t set(const T &handle) override;
        ///< set
    T      clone() const override;
        ///< duplicate handle
    void_t setCloseOnExec(cbool_t flag);
		///< duplicate file descriptors from sub-processes

    bool_t isValid() const override;
        ///< is valid
    void_t attach(const T &handle) override;
        ///< attach
    T      detach() override;
        ///< detach
    void_t close() override;
        ///< close

#if xENV_WIN
    ulong_t info() const;
        ///< get certain properties of an object handle
    void_t  setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

xPUBLIC_STATIC:
	static T           null();
		///< get "null" value
	static std::size_t openMax();
		///< maximum open handles

private:
    using handle_policy_t = HandlePolicy<T, valueT>;
    xUSING_CONST(handle_policy_t);

    T               _handle {}; ///< handle
    handle_policy_t _policy;    ///< handle policy

xPLATFORM_IMPL:
    void_t _setCloseOnExec_impl(cbool_t flag);
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Handle.inl"

#if xENV_WIN
    #include "Platform/Win/Handle_win.inl"
#endif
//-------------------------------------------------------------------------------------------------
