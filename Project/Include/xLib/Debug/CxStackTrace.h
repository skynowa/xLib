/**
 * \file   CxStackTrace.h
 * \brief  get stack backtrace of the caller function
 */


#ifndef xLib_Debug_CxStackTraceH
#define xLib_Debug_CxStackTraceH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxStackTrace :
    private CxNonCopyable
    /// stack trace
{
public:
    explicit             CxStackTrace(const std::tstring_t &csLinePrefix          = xT("\t\t"),
                                      const std::tstring_t &csElementSeparator    = xT("  "),
                                      const std::tstring_t &csLinesSeparator      = xT("\n"),
                                      const bool           &cbIsWrapFilePathes    = true,
                                      const bool           &cbIsFuncParamsDisable = true);
        ///< constructor
    virtual             ~CxStackTrace();
        ///< destructor

    void                 get         (std::vector<std::vec_tstring_t> *pvvsStack);
        ///< get stack trace
    std::tstring_t       toString    () xWARN_UNUSED_RV;
        ///< get stack trace with format output

private:
    const std::tstring_t _m_csLinePrefix;
    const std::tstring_t _m_csElementSeparator;
    const std::tstring_t _m_csLineSeparator;
    const bool           _m_cbIsWrapFilePathes;
    const bool           _m_cbIsFuncParamsDisable;

    std::tstring_t       _format     (std::vector<std::vec_tstring_t> *pvvsStack) xWARN_UNUSED_RV;
        ///< format stack trace
#if xOS_ENV_UNIX
    static void          _addr2Line  (const void *pvSymbolAddress, std::tstring_t *psFilePath,
                                      std::tstring_t *psFunctionName, ulong_t *pulSourceLine);
#endif
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxStackTraceH
