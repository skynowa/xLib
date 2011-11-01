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
class CxStackTrace :
    public CxNonCopyable
    /// stack trace
{
	public:
		explicit     CxStackTrace();
            ///< constructor
		virtual     ~CxStackTrace();
		    ///< destructor

        BOOL         bGet        (std::vector<std::tstring> *pvsStack);
            ///< get stack trace
        std::tstring sGet        (const std::tstring &csLinesSeparator = xT("\n"));
            ///< get stack trace

    private:
    #if defined(xOS_ENV_WIN)
        static const ULONG _m_culMaxFrames = 62UL;    //from MSDN, ::CaptureStackBackTrace
    #elif defined(xOS_ENV_UNIX)
        static const INT   _m_culMaxFrames = 256;     //this should be enough
    #endif
        ///< maximum frames for report
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStackTraceH
