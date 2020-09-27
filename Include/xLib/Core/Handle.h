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
#include <xLib/Interface/IHandle.h>
#include <xLib/Core/HandlePolicy.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T, HandlePolicyType valueT>
class Handle :
    public IHandle<T>
    /// handle
{
public:
                Handle();
    explicit    Handle(const T &handle);
    explicit    Handle(const Handle &handle);
    virtual    ~Handle();

    Handle &    operator = (const T &handle);
    Handle &    operator = (const Handle &handle);

    static
    T           null();
        ///< get
    static
    std::size_t openMax();
		///< maximum open handles

    T           get() const;
        ///< get
    void_t      set(const T &handle);
        ///< set
    T           clone() const;
        ///< duplicate handle
    void_t      setCloseOnExec(cbool_t flag);
		///< duplicate file descriptors from sub-processes

    bool_t      isValid() const;
        ///< is valid
    void_t      attach(const T &handle);
        ///< attach
    T           detach();
        ///< detach
    void_t      close();
        ///< close

#if xENV_WIN
    ulong_t     info() const;
        ///< get certain properties of an object handle
    void_t      setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

private:
    using handle_policy_t = HandlePolicy<T, valueT>;

    T           _handle {};    ///< handle

xPLATFORM_IMPL:
    void_t      _setCloseOnExec_impl(cbool_t flag);
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Handle.inl"

#if xENV_WIN
    #include "Platform/Win/Handle_win.inl"
#endif
