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

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxTracerH
