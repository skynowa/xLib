/**
 * \file   Signal.h
 * \brief  signal
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Signal
    ///< signal
{
public:
    typedef void_t (*exit_handler_t)();
        ///< handler type

             Signal() {}
        ///< constructor
    virtual ~Signal() {}
        ///< destructor

    std::sig_atomic_t state() const;
        ///< get state flag
    void_t   setState(const std::sig_atomic_t &state);
        ///< set state flag

    void_t   connect(const std::vector<int_t> &signalNums, const sighandler_t &onSignals) const;
        ///< set signal handle
    void_t   connectExit(const exit_handler_t &onExit) const;
        ///< set exit handle
    void_t   connectTerminate(const std::terminate_handler &onTerminate) const;
        ///< set terminate handle (by default, the terminate handler calls abort)
    void_t   connectUnexpected(const std::unexpected_handler &onUnexpected) const;
        ///< Sets unexpected handler
    int_t    emit(cint_t &signalNum) const;
        ///< sends signal to the current executing program

    static
    std::tstring_t decription(cint_t &signalNum);
        ///< string describing signal

private:
    xNO_COPY_ASSIGN(Signal)

    volatile
    std::sig_atomic_t _state;
        ///< Integral type of an object that can be accessed as an atomic entity,
        ///< even in the presence of asynchronous signals.

xPLATFORM_IMPL:
    static
    std::tstring_t _decription_impl(cint_t &signalNum);
        ///< string describing signal
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Signal.cpp"
#endif
