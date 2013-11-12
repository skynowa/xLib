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

class CxTracer :
    public CxNonCopyable
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

    void_t                write(ctchar_t *format, ...);
        ///< tracing to debugger, std::cout
    void_t                write(std::ctstring_t &msg);
        ///< tracing to debugger, std::cout

private:
    std::tostringstream_t _oss; ///< string stream
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Log/CxTracer.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTracerH
