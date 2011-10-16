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

        BOOL         bGet        (std::vector<std::string> *pvsStack, const size_t cuiMaxFrames = 62);
        std::tstring sGet        (const std::tstring &csSeparator = xT("\r\n"), const size_t cuiMaxFrames = 62);

    private:

};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStackTraceH
