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
    explicit             CxStackTrace(std::ctstring_t &csLinePrefix          = xT("\t\t"),
                                      std::ctstring_t &csElementSeparator    = xT("  "),
                                      std::ctstring_t &csLinesSeparator      = xT("\n"),
                                      cbool_t           &cbIsWrapFilePathes    = true,
                                      cbool_t           &cbIsFuncParamsDisable = true);
        ///< constructor
    virtual             ~CxStackTrace();
        ///< destructor

    void                 get         (std::vector<std::vec_tstring_t> *pvvsStack);
        ///< get stack trace
    std::tstring_t       toString    () xWARN_UNUSED_RV;
        ///< get stack trace with format output

private:
    std::ctstring_t _m_csLinePrefix;
    std::ctstring_t _m_csElementSeparator;
    std::ctstring_t _m_csLineSeparator;
    cbool_t           _m_cbIsWrapFilePathes;
    cbool_t           _m_cbIsFuncParamsDisable;

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
