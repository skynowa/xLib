/**
 * \file  Handle.h
 * \brief handle
 */


#pragma once

//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

namespace debug
{

class NativeError;
class StackTrace;
class ErrorReport;
class Debugger;

}

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Interface/IHandle.h>
#include <xLib/Core/HandlePolicy.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T, HandlePolicyType valueT>
class Handle :
    public IHandle<T>
    /// handle
{
public:
                Handle();
        ///< constructor
    explicit    Handle(const T &handle);
        ///< constructor
    explicit    Handle(const Handle &handle);
        ///< constructor
    virtual    ~Handle();
        ///< destructor

    Handle &    operator = (const T &handle);
        ///< operator =
    Handle &    operator = (const Handle &handle);
        ///< operator =

    static
    T           null() xWARN_UNUSED_RV;
        ///< get
    static
    std::size_t openMax() xWARN_UNUSED_RV;
		///< maximum open handles

    T           get() const xWARN_UNUSED_RV;
        ///< get
    void_t      set(const T &handle);
        ///< set
    T           clone() const xWARN_UNUSED_RV;
        ///< duplicate handle
    void_t      setCloExec(cbool_t flag);
		///< duplicate file descriptors from sub-processes

    bool_t      isValid() const xWARN_UNUSED_RV;
        ///< is valid
    void_t      attach(const T &handle);
        ///< attach
    T           detach() xWARN_UNUSED_RV;
        ///< detach
    void_t      close();
        ///< close

#if xENV_WIN
    ulong_t     info() const xWARN_UNUSED_RV;
        ///< get certain properties of an object handle
    void_t      setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

private:
    typedef HandlePolicy<T, valueT> handle_policy_t;

    T           _handle;    ///< handle

xPLATFORM_IMPL:
    void_t      _setCloExec_impl(cbool_t flag);
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Handle.inl"

#if xENV_WIN
    #include "Platform/Win/Handle_win.inl"
#endif
