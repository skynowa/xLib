/**
 * \file   CxTracer.h
 * \brief  tracer
 */


#ifndef xLib_Debug_CxTracerH
#define xLib_Debug_CxTracerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxTracer :
    private CxNonCopyable
    /// tracing
{
    public:
        virtual           ~CxTracer    ();
		    ///< destructor

        template<class T>
        CxTracer &         operator << (const T &cValueT);
            ///< operator <<
        static CxTracer &  Write       ();
            ///< get CxTracer object for tracing
        static bool        bWrite      (const tchar_t *pcszFormat, ...);
            ///< tracing to debugger, std::cout
        static bool        bWrite      (const std::tstring_t &csMsg);
            ///< tracing to debugger, std::cout

    private:
        std::ostringstream _m_ossStream;    ///< string stream

				           CxTracer    ();
            ///< constructor


};
//---------------------------------------------------------------------------
template<class T>
CxTracer &
CxTracer::operator << (const T &cValueT) {
    _m_ossStream << cValueT;

    return *this;
}
//---------------------------------------------------------------------------
#endif //xLib_CxTracerH
