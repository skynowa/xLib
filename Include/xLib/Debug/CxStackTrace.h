/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
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

        BOOL         bGet        (std::vector<std::string> *pvsStack);
            ///< get stack trace
        std::tstring sGet        (const std::tstring &csLinesSeparator = xT("\n"));
            ///< get stack trace

    private:
        const ULONG _m_culMaxFrames;   ///< maximum frames for report
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStackTraceH
