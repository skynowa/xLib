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

    void_t   setOnSignals(const std::vector<int_t> &signalNums, sighandler_t callback) const;
        ///< set signal handle
    void_t   setOnExit(void_t (*callback)()) const;
        ///< set exit handle
    void_t   setOnTerminate(void_t (*callback)()) const;
        ///< set terminate handle (by default, the terminate handler calls abort)

    int_t    raise(cint_t &signal) const;
        ///< sends signal to the current executing program

private:
    xNO_COPY_ASSIGN(Signal)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Signal.cpp"
#endif
