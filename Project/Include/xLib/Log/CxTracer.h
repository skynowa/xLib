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
                          CxTracer() {}
        ///< constructor
    virtual              ~CxTracer();
        ///< destructor

    template<class T>
    CxTracer &            operator << (const T &valueT);
        ///< operator <<

    void_t                write(ctchar_t *format, ...);
        ///< tracing to debugger, std::cout
    void_t                write(std::ctstring_t &msg);
        ///< tracing to debugger, std::cout

private:
    std::tostringstream_t _oss; ///< string stream
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<class T>
CxTracer &
CxTracer::operator << (const T &valueT)
{
    _oss << valueT;

    return *this;
}

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Log/CxTracer.cpp>
#endif
