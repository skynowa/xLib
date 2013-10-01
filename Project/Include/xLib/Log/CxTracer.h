/**
 * \file   CxTracer.h
 * \brief  tracer
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString;

class CxTracer :
    private CxNonCopyable
    /// tracing
{
public:
                          CxTracer    ();
        ///< constructor
    virtual              ~CxTracer    ();
        ///< destructor

    template<typename T>
    CxTracer &            operator << (const T &cValueT);
        ///< operator <<

    static void_t         write       (ctchar_t *pcszFormat, ...);
        ///< tracing to debugger, std::cout
    static void_t         write       (std::ctstring_t &csMsg);
        ///< tracing to debugger, std::cout

private:
    std::tostringstream_t _m_ossStream;    ///< string stream
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<typename T>
CxTracer &
CxTracer::operator << (const T &cValueT) {
    _m_ossStream << cValueT;

    return *this;
}

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
