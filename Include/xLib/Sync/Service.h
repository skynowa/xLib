/**
 * \file   Service.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Service
    ///<
{
public:
             Service() {}
        ///< constructor
    virtual ~Service() {}
        ///< destructor

    void_t   create();
        ///< create
    void_t   start();
        ///< start
    void_t   stop();
        ///< stop
    void_t   restart();
        ///< restart
    void_t   close();
        ///< restart

private:
    xNO_COPY_ASSIGN(Service)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Service.cpp"
#endif
