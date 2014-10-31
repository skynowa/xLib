/**
 * \file   Signal.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Signal
    ///<
{
public:
             Signal() {}
        ///< constructor
    virtual ~Signal() {}
        ///< destructor

    std::sig_atomic_t state() const;
        ///< get state flag
    void_t   setState(const std::sig_atomic_t &state);
        ///< set state flag

    void_t   connect(const std::vector<int_t> &signalNums, sighandler_t callback) const;
        ///< set signal handle
    void_t   connectExit(void_t (*callback)()) const;
        ///< set exit handle
    void_t   connectTerminate(void_t (*callback)()) const;
        ///< set terminate handle (by default, the terminate handler calls abort)

    int_t    emit(cint_t &signalNum) const;
        ///< sends signal to the current executing program

private:
    xNO_COPY_ASSIGN(Signal)

    volatile
    std::sig_atomic_t _signal_state;
        ///< Integral type of an object that can be accessed as an atomic entity,
        ///< even in the presence of asynchronous signals.
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Signal.cpp"
#endif
