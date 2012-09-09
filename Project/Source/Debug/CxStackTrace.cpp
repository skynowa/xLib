/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
 */


#include <xLib/Debug/CxStackTrace.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if xOS_ENV_WIN
    #ifdef xUNICODE
        #define DBGHELP_TRANSLATE_TCHAR 1
    #endif

    #if   xCOMPILER_MINGW32
        //
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        #include <DbgHelp.h>
        #pragma comment(lib, "DbgHelp.Lib")
    #endif
#elif xOS_ENV_UNIX
    #include <execinfo.h>   // lib: -lexecinfo (FreeBSD)
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxStackTrace::CxStackTrace(
    const std::tstring_t &csLinePrefix,         /* = xT("\t") */
    const std::tstring_t &csLinesSeparator,     /* = xT("\n") */
    const bool           &cbIsWrapFilePathes,   /* = true */
    const bool           &cbIsFuncParamsEnable  /* = false */
) :
    _m_csLinePrefix        (csLinePrefix),
    _m_csLineSeparator     (csLinesSeparator),
    _m_cbIsWrapFilePathes  (cbIsWrapFilePathes),
    _m_cbIsFuncParamsEnable(cbIsFuncParamsEnable)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxStackTrace::~CxStackTrace() {

}
//---------------------------------------------------------------------------
bool
CxStackTrace::bGet(
    std::vec_tstring_t *pvsStack
) const
{
    xCHECK_RET(NULL == pvsStack, false);

    std::vec_tstring_t vsStack;

#if xOS_ENV_WIN
    #if   xCOMPILER_MINGW32
        //TODO: CxStackTrace::bGet
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        void        *pvStack[xSTACK_TRACE_FRAMES_MAX] = {0};
        SYMBOL_INFO *psiSymbol                        = NULL;
        HANDLE       hProcess                         = NULL;

        hProcess = CxCurrentProcess::hGetHandle();

        BOOL blRes = ::SymInitialize(hProcess, NULL, TRUE);
        xCHECK_RET(FALSE == blRes, false);

        ushort_t usFramesNum = ::CaptureStackBackTrace(0UL, xSTACK_TRACE_FRAMES_MAX, pvStack, NULL);
        xCHECK_RET(usFramesNum == 0U, false);

        psiSymbol               = new (std::nothrow) SYMBOL_INFO[ sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t) ];\
        /*DEBUG*/
        psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        psiSymbol->MaxNameLen   = 255UL;

        for (ushort_t i = 1U; i < usFramesNum; ++ i) {
            std::tstring_t sStackLine;

            blRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);
            if (FALSE == blRes) {
                sStackLine = CxConst::xUNKNOWN_STRING;
            } else {
                /*
                std::tstring_t sModulePath;
                std::tstring_t sFilePath;
                std::tstring_t sFunctionName;
                std::tstring_t sFileLine;
                std::tstring_t sByteOffset;
                */

                const ptrdiff_t      ullAddress = static_cast<ptrdiff_t>( psiSymbol->Address );
                const std::tstring_t csName     = std::tstring_t(psiSymbol->Name);

                sStackLine = CxString::sFormat(xT("%s%u: %p  %s%s"),
                                                _m_csLinePrefix.c_str(),
                                                usFramesNum - i - 1U,
                                                ullAddress,
                                                csName.c_str(),
                                                _m_csLineSeparator.c_str());
            }

            vsStack.push_back(sStackLine);
        }

        xARRAY_DELETE(psiSymbol);

        (void)::SymCleanup(hProcess);   hProcess = NULL;
    #endif
#elif xOS_ENV_UNIX
    void *pvStack[xSTACK_TRACE_FRAMES_MAX] = {0};

    int iFramesNum = ::backtrace(pvStack, xSTACK_TRACE_FRAMES_MAX);
    xCHECK_RET(iFramesNum <= 0, false);

    tchar_t **ppszSymbols = ::backtrace_symbols(pvStack, iFramesNum);
    xCHECK_RET(NULL == ppszSymbols, false);

    for (int i = 0; i < iFramesNum; ++ i) {
        std::tstring_t sStackLine;

        int            iStackLineNum = 0;
        std::tstring_t sModulePath;
        std::tstring_t sFilePath;
        std::tstring_t sFunctionName;
        std::tstring_t sFileLine;
        std::tstring_t sByteOffset;

        Dl_info dlinfo = {0};

        int iRv = ::dladdr(pvStack[i], &dlinfo);
        if (0 == iRv) {
            iStackLineNum = i;
            sModulePath   = (NULL == dlinfo.dli_fname) ? xT("[???]") : dlinfo.dli_fname;
            sFilePath     = xT("[???]");
            sFunctionName = (NULL == ppszSymbols[i])   ? xT("[???]") : ppszSymbols[i];
            sFileLine     = xT("[???]");
            sByteOffset   = CxString::sFormat(xT("%p"), ptrdiff_t(0));
        } else {
            const tchar_t *pcszSymbolName = NULL;
            int            iStatus        = - 1;

            tchar_t *pszDemangleName = abi::__cxa_demangle(dlinfo.dli_sname, NULL, NULL, &iStatus);
            if (NULL != pszDemangleName && 0 == iStatus) {
                pcszSymbolName = pszDemangleName;
            } else {
                pcszSymbolName = dlinfo.dli_sname;
            }


            std::tstring_t _sFilePath;
            std::tstring_t _sFunctionName;
            ulong_t        _ulSourceLine = 0;

            bool bRv = _bAddr2Line(dlinfo.dli_saddr, &_sFilePath, &_sFunctionName, &_ulSourceLine);
            assert(true == bRv);
            xUNUSED(_sFunctionName);

            iStackLineNum = i;
            sModulePath   = (NULL == dlinfo.dli_fname) ? xT("[???]") : dlinfo.dli_fname;
            sFilePath     = _sFilePath.empty()         ? xT("[???]") : _sFilePath;
            sFunctionName = (NULL == pcszSymbolName)   ? xT("[???]") : pcszSymbolName;
            sFileLine     = CxString::lexical_cast(_ulSourceLine);
            sByteOffset   = CxString::sFormat(xT("%p"), ptrdiff_t(dlinfo.dli_saddr));

            xBUFF_FREE(pszDemangleName);
        }


        if (true == _m_cbIsWrapFilePathes) {
            sModulePath = CxPath::sGetFileName(sModulePath);
            sFilePath   = CxPath::sGetFileName(sFilePath);
        }

        if (false == _m_cbIsFuncParamsEnable) {
            size_t uiPos1 = sFunctionName.find(xT("("));
            size_t uiPos2 = sFunctionName.find(xT(")"));

            if (std::tstring_t::npos != uiPos1 &&
                std::tstring_t::npos != uiPos2)
            {
                assert(uiPos1 < uiPos2);
                sFunctionName = sFunctionName.substr(0, uiPos1 + 1) +
                                sFunctionName.substr(uiPos2);
            }
        }

        sStackLine = CxString::sFormat(xT("%s%u: %s  %s  %s  %s  %s%s"),
                                _m_csLinePrefix.c_str(),
                                iStackLineNum,
                                sModulePath.c_str(),
                                sFilePath.c_str(),
                                sByteOffset.c_str(),
                                sFunctionName.c_str(),
                                sFileLine.c_str(),
                                _m_csLineSeparator.c_str());

        vsStack.push_back(sStackLine);
    }
#endif

    std::swap(*pvsStack, vsStack);

    return true;
}
//---------------------------------------------------------------------------
std::tstring_t
CxStackTrace::sGet() const {
    std::tstring_t sRv;

    std::vec_tstring_t vsStack;

    bool bRv = bGet(&vsStack);
    xCHECK_RET(false == bRv, std::tstring_t());

    sRv = CxString::sJoin(vsStack, std::tstring_t());

    return sRv;
}
//---------------------------------------------------------------------------
std::tstring_t
CxStackTrace::sFormat() const {
    std::tstring_t sRv;




    return sRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

/*static*/
bool
CxStackTrace::_bAddr2Line(
    const void     *pvSymbolAddress,
    std::tstring_t *psFilePath,
    std::tstring_t *psFunctionName,
    ulong_t        *pulSourceLine
)
{
    tchar_t szCmdLine[1024 + 1] = {0};

   /**
    * MAN: addr2line
    *   @<file>                Read options from <file>
    *   -b --target=<bfdname>  Set the binary file format
    *   -e --exe=<executable>  Set the input file name (default is a.out)
    *   -i --inlines           Unwind inlined functions
    *   -j --section=<name>    Read section-relative offsets instead of addresses
    *   -s --basenames         Strip directory names
    *   -f --functions         Show function names
    *   -C --demangle[=style]  Demangle function names
    *   -h --help              Display this information
    *   -v --version           Display the program's version
    */

    snprintf(szCmdLine, xARRAY_SIZE(szCmdLine) - 1,
             xT("addr2line -C -e %s -f %lx"),   /* xT("addr2line -C -e %s -f -i %lx") */
             CxPath::sGetExe().c_str(), (ulong_t)pvSymbolAddress);

    FILE *pflFile = ::popen(szCmdLine, xT("r"));
    assert(NULL != pflFile);

    // get function name
    {
        tchar_t szBuff[1024 + 1] = {0};

        const tchar_t *pcszFunctionName = std::fgets(szBuff, xARRAY_SIZE(szBuff), pflFile);
        assert(NULL != pcszFunctionName);

        (*psFunctionName).assign(pcszFunctionName);
    }

    // get file and line
    {
        tchar_t szBuff[1024 + 1] = {0};

        const tchar_t *pcszFileAndLine = std::fgets(szBuff, xARRAY_SIZE(szBuff), pflFile);
        assert(NULL != pcszFileAndLine);

       /*
        * Parse that variants of pcszFileAndLine string:
        *   - /home/skynowa/Projects/xLib/Build/Tests/GCC_linux/Debug/../../../../Tests/Source/./Test.cpp:108
        *   - ??:0
        *
        */
        std::vec_tstring_t vsLine;

        bool bRv = CxString::bSplit(pcszFileAndLine, xT(":"), &vsLine);
        assert(true == bRv);
        assert(2U   == vsLine.size());

        // out
        assert(0 == std::feof(pflFile));

        *psFilePath    = vsLine.at(0);
        *pulSourceLine = CxString::lexical_cast<ulong_t>( vsLine.at(1) );
    }

    int iRv =::pclose(pflFile);    pflFile = NULL;
    assert(- 1 != iRv);

    return true;
}

#endif  // xOS_ENV_UNIX
//---------------------------------------------------------------------------


xNAMESPACE_END(NxLib)
