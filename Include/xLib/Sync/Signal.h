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

private:
    xNO_COPY_ASSIGN(Signal)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Signal.cpp"
#endif
