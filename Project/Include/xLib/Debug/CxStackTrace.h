/**
 * \file   CxStackTrace.h
 * \brief  get stack backtrace of the caller function
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
        explicit       CxStackTrace(const std::tstring_t &csLinePrefix = xT("\t"), const std::tstring_t &csLinesSeparator = xT("\n"));
            ///< constructor
        virtual       ~CxStackTrace();
            ///< destructor

        bool           bGet        (std::vec_tstring_t *pvsStack);
            ///< get stack trace
        std::tstring_t sGet        ();
            ///< get stack trace

    private:
        const std::tstring_t _m_csLinePrefix;
        const std::tstring_t _m_csLineSeparator;   

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxStackTraceH
    