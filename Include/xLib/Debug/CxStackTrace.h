/**
 * \file   CxStackTrace.h
 * \brief  get stack backtrace of the caller function
 *         http://idlebox.net/
 */


#ifndef xLib_Debug_CxStackTraceH
#define xLib_Debug_CxStackTraceH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxConst.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxStackTrace :
    public CxNonCopyable
    /// stack trace
{
    public:
        explicit     CxStackTrace();
            ///< constructor
        virtual     ~CxStackTrace();
            ///< destructor

        bool         bGet        (std::vector<std::tstring> *pvsStack);
            ///< get stack trace
        std::tstring sGet        (const std::tstring &csLinesSeparator = xT("\n"));
            ///< get stack trace

    private:
    #if xOS_ENV_WIN
        static const ULONG _m_culMaxFrames = 62UL;    //from MSDN, ::CaptureStackBackTrace
    #elif xOS_ENV_UNIX
        static const int   _m_culMaxFrames = 256;     //this should be enough
    #endif
            ///< maximum frames for report
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStackTraceH
