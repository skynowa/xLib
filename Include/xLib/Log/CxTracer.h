/**
 * \file   CxTracer.h
 * \brief  tracer
 */


#ifndef xLib_Debug_CxTracerH
#define xLib_Debug_CxTracerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString;

class CxTracer :
    private CxNonCopyable
    /// tracing
{
    public:
                            CxTracer    ();
            ///< constructor
        virtual            ~CxTracer    ();
		    ///< destructor

        template<class T>
        CxTracer &          operator << (const T &cValueT);
            ///< operator <<

        static bool         bWrite      (const tchar_t *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static bool         bWrite      (const std::tstring_t &csMsg);
            ///< tracing to debugger, std::cout

    private:
        std::ostringstream  _m_ossStream;    ///< string stream

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<class T>
CxTracer &
CxTracer::operator << (const T &cValueT) {
    _m_ossStream << cValueT;

    return *this;
}

#define xTRACE_VAR(v)   std::tstring_t() \
                            .append(xT(#v": ")) \
                            .append(CxString::lexical_cast(v)) \
                            .append(xT(" "))
    ///< trace variable, trace variable and value

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxTracerH
