/**
 * \file   CxStackTrace.h
 * \brief  get stack backtrace of the caller function
 *         http://idlebox.net/
 */


#ifndef xLib_Debug_CxStackTraceH
#define xLib_Debug_CxStackTraceH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxStackTrace :
    private CxNonCopyable
    /// stack trace
{
    public:
                       CxStackTrace();
            ///< constructor
        virtual       ~CxStackTrace();
            ///< destructor

        bool           bGet        (std::vec_tstring_t *pvsStack);
            ///< get stack trace
        std::tstring_t sGet        (const std::tstring_t &csLinesSeparator = xT("\n"));
            ///< get stack trace

    private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStackTraceH
