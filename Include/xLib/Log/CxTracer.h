/**
 * \file   CxTracer.h
 * \brief  tracer
 */


#pragma once

#ifndef xLib_CxTracerH
#define xLib_CxTracerH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString;

class CxTracer
    /// tracing
{
public:
                          CxTracer() {}
        ///< constructor
    virtual              ~CxTracer();
        ///< destructor

    template<class T>
    CxTracer &            operator << (const T &valueT)
    {
        _oss << valueT;

        return *this;
    }
        ///< operator <<

    void_t                write(ctchar_t *format, ...) const;
        ///< tracing to debugger, std::cout
    void_t                write(std::ctstring_t &msg) const;
        ///< tracing to debugger, std::cout

private:
    std::tostringstream_t _oss; ///< string stream

    xNO_COPY_ASSIGN(CxTracer)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxTracer.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTracerH
