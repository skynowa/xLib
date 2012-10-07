/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
 */


#include <xLib/Debug/CxStackTrace.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW32
        // TODO:
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        #ifdef xUNICODE
            #define DBGHELP_TRANSLATE_TCHAR 1
        #endif

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
    const std::tstring_t &a_csLinePrefix,         /* = xT("\t") */
    const std::tstring_t &a_csElementSeparator,   /* = xT("  ") */
    const std::tstring_t &a_csLinesSeparator,     /* = xT("\n") */
    const bool           &a_cbIsWrapFilePathes,   /* = true */
    const bool           &a_cbIsFuncParamsDisable /* = true */
) :
    _m_csLinePrefix         (a_csLinePrefix),
    _m_csElementSeparator   (a_csElementSeparator),
    _m_csLineSeparator      (a_csLinesSeparator),
    _m_cbIsWrapFilePathes   (a_cbIsWrapFilePathes),
    _m_cbIsFuncParamsDisable(a_cbIsFuncParamsDisable)
{

}
//---------------------------------------------------------------------------
/* virtual */
CxStackTrace::~CxStackTrace() {

}
//---------------------------------------------------------------------------
void
CxStackTrace::vGet(
    std::vector<std::vec_tstring_t> *a_pvvsStack
)
{
    xCHECK_DO(NULL == a_pvvsStack, return /* false */);

    const std::tstring_t            csDataNotFound = xT("[???]");
    std::vector<std::vec_tstring_t> vvsStack;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW32
        // TODO: CxStackTrace::bGet
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        void        *pvStack[xSTACK_TRACE_FRAMES_MAX] = {0};
        SYMBOL_INFO *psiSymbol                        = NULL;
        HANDLE       hProcess                         = NULL;

        hProcess = CxCurrentProcess::hGetHandle();

        BOOL blRes = ::SymInitialize(hProcess, NULL, TRUE);
        xCHECK_DO(FALSE == blRes, return /* false */);

        ushort_t usFramesNum = ::CaptureStackBackTrace(0UL, xSTACK_TRACE_FRAMES_MAX, pvStack, NULL);
        xCHECK_DO(usFramesNum == 0U, return /* false */);

        psiSymbol               = new (std::nothrow) SYMBOL_INFO[ sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t) ];
        /*DEBUG*/xSTD_VERIFY(NULL != psiSymbol);
        psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        psiSymbol->MaxNameLen   = 255UL;

        for (ushort_t i = 1U; i < usFramesNum; ++ i) {
            int            iStackLineNum = 0;
            std::tstring_t sModulePath;
            std::tstring_t sFilePath;
            std::tstring_t sFileLine;
            std::tstring_t sByteOffset;
            std::tstring_t sFunctionName;

            // iStackLineNum
            {
                iStackLineNum = i;
            }

            // sModulePath
            {
                IMAGEHLP_MODULE64 miModuleInfo = {0};   miModuleInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

                blRes = ::SymGetModuleInfo64(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), &miModuleInfo);
                if (FALSE == blRes) {
                    sModulePath   = csDataNotFound;
                } else {
                    sModulePath   = miModuleInfo.ImageName;
                }
            }

            // sFilePath, sFileLine
            {
                DWORD           dwDisplacement  = 0UL;
                IMAGEHLP_LINE64 ihlImagehlpLine = {0};    ihlImagehlpLine.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

                blRes = ::SymGetLineFromAddr64(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), &dwDisplacement, &ihlImagehlpLine);
                if (FALSE == blRes) {
                    sFilePath     = csDataNotFound;
                    sFileLine     = csDataNotFound;
                } else {
                    sFilePath     = ihlImagehlpLine.FileName;
                    sFileLine     = CxString::string_cast(ihlImagehlpLine.LineNumber);
                }
            }

            // iStackLineNum, sByteOffset, sFunctionName
            {
                blRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);
                if (FALSE == blRes) {
                    sByteOffset   = CxString::sFormat(xT("%p"), ptrdiff_t(0));
                    sFunctionName = csDataNotFound;
                } else {
                    sByteOffset   = CxString::sFormat(xT("%p"), static_cast<ptrdiff_t>( psiSymbol->Address ) );
                    sFunctionName = std::tstring_t(psiSymbol->Name);
                }
            }

            // swap file pathes
            if (true == _m_cbIsWrapFilePathes) {
                sModulePath = CxPath::sGetFileName(sModulePath);
                sFilePath   = CxPath::sGetFileName(sFilePath);
            }

            // disable function params
            if (true == _m_cbIsFuncParamsDisable) {
                const size_t cuiPos1 = sFunctionName.find(xT("("));
                const size_t cuiPos2 = sFunctionName.find(xT(")"));

                if (std::tstring_t::npos != cuiPos1 && std::tstring_t::npos != cuiPos2) {
                    xSTD_VERIFY(cuiPos1 < cuiPos2);

                    sFunctionName = sFunctionName.substr(0, cuiPos1 + 1) +
                                    sFunctionName.substr(cuiPos2);
                }
            }

            // out
            {
                std::vec_tstring_t vsStackLine;

                vsStackLine.push_back( CxString::string_cast(iStackLineNum) );
                vsStackLine.push_back(sModulePath);
                vsStackLine.push_back(sFilePath);
                vsStackLine.push_back(sFileLine);
                vsStackLine.push_back(sByteOffset);
                vsStackLine.push_back(sFunctionName);

                vvsStack.push_back(vsStackLine);
            }
        }

        xARRAY_DELETE(psiSymbol);

        (void)::SymCleanup(hProcess);   hProcess = NULL;
    #endif
#elif xOS_ENV_UNIX
    void *pvStack[xSTACK_TRACE_FRAMES_MAX] = {0};

    int iFramesNum = ::backtrace(pvStack, xSTACK_TRACE_FRAMES_MAX);
    xCHECK_DO(iFramesNum <= 0, return /* false */);

    tchar_t **ppszSymbols = ::backtrace_symbols(pvStack, iFramesNum);
    xCHECK_DO(NULL == ppszSymbols, return /* false */);

    for (int i = 0; i < iFramesNum; ++ i) {
        int            iStackLineNum = 0;
        std::tstring_t sModulePath;
        std::tstring_t sFilePath;
        std::tstring_t sFileLine;
        std::tstring_t sByteOffset;
        std::tstring_t sFunctionName;

        Dl_info dlinfo = {0};

        int iRv = ::dladdr(pvStack[i], &dlinfo);
        if (0 == iRv) {
            iStackLineNum = i;
            sModulePath   = (NULL == dlinfo.dli_fname) ? csDataNotFound : dlinfo.dli_fname;
            sFilePath     = csDataNotFound;
            sFileLine     = csDataNotFound;
            sByteOffset   = CxString::sFormat(xT("%p"), ptrdiff_t(0));
            sFunctionName = (NULL == ppszSymbols[i])   ? csDataNotFound : ppszSymbols[i];
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
            ulong_t        _ulSourceLine = 0U;

            bool bRv = _bAddr2Line(dlinfo.dli_saddr, &_sFilePath, &_sFunctionName, &_ulSourceLine);
            xSTD_VERIFY(true == bRv);
            xUNUSED(_sFunctionName);

            iStackLineNum = i;
            sModulePath   = (NULL == dlinfo.dli_fname) ? csDataNotFound : dlinfo.dli_fname;
            sFilePath     = _sFilePath.empty()         ? csDataNotFound : _sFilePath;
            sFileLine     = CxString::string_cast(_ulSourceLine);
            sByteOffset   = CxString::sFormat(xT("%p"), ptrdiff_t(dlinfo.dli_saddr));
            sFunctionName = (NULL == pcszSymbolName)   ? csDataNotFound : pcszSymbolName;

            xBUFF_FREE(pszDemangleName);
        }

        // swap file pathes
        if (true == _m_cbIsWrapFilePathes) {
            sModulePath = CxPath::sGetFileName(sModulePath);
            sFilePath   = CxPath::sGetFileName(sFilePath);
        }

        // disable function params
        if (true == _m_cbIsFuncParamsDisable) {
            const size_t cuiPos1 = sFunctionName.find(xT("("));
            const size_t cuiPos2 = sFunctionName.find(xT(")"));

            if (std::tstring_t::npos != cuiPos1 && std::tstring_t::npos != cuiPos2) {
                xSTD_VERIFY(cuiPos1 < cuiPos2);

                sFunctionName = sFunctionName.substr(0, cuiPos1 + 1) +
                                sFunctionName.substr(cuiPos2);
            }
        }

        // out
        {
            std::vec_tstring_t vsStackLine;

            vsStackLine.push_back( CxString::string_cast(iStackLineNum) );
            vsStackLine.push_back(sModulePath);
            vsStackLine.push_back(sFilePath);
            vsStackLine.push_back(sFileLine);
            vsStackLine.push_back(sByteOffset);
            vsStackLine.push_back(sFunctionName);

            vvsStack.push_back(vsStackLine);
        }
    } // for
#endif

    std::swap(*a_pvvsStack, vvsStack);
}
//---------------------------------------------------------------------------
std::tstring_t
CxStackTrace::sGet()  {
    std::tstring_t sRv;

    std::vector<std::vec_tstring_t> vvsStack;

    vGet(&vvsStack);

    sRv = _sFormat(&vvsStack);
    xCHECK_RET(true == sRv.empty(), CxConst::xUNKNOWN_STRING);

    return sRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/


//---------------------------------------------------------------------------
std::tstring_t
CxStackTrace::_sFormat(
    std::vector<std::vec_tstring_t> *a_pvvsStack
)
{
    std::tstring_t      sRv;

    const size_t        cuiElementsNum = 6U;
    std::vector<size_t> vuiMaxs(cuiElementsNum, 0U);

    // get elements max sizes
    for (size_t i = 0; i < cuiElementsNum; ++ i) {
        xFOREACH_CONST(std::vector<std::vec_tstring_t>, it, *a_pvvsStack) {
            const size_t uiCurr = it->at(i).size();

            xCHECK_DO(uiCurr > vuiMaxs[i], vuiMaxs[i] = uiCurr);
        }
    }

    // formating
    xFOREACH_CONST(std::vector<std::vec_tstring_t>, it, *a_pvvsStack) {
        std::tstringstream_t ssStackLine;

        ssStackLine << _m_csLinePrefix
                    << std::setw(vuiMaxs[0]) << std::right << it->at(0) << _m_csElementSeparator
                    << std::setw(vuiMaxs[1]) << std::left  << it->at(1) << _m_csElementSeparator
                    << std::setw(vuiMaxs[2]) << std::left  << it->at(2) << _m_csElementSeparator
                    << std::setw(vuiMaxs[3]) << std::right << it->at(3) << _m_csElementSeparator
                    << std::setw(vuiMaxs[4]) << std::left  << it->at(4) << _m_csElementSeparator
                    << std::setw(vuiMaxs[5]) << std::left  << it->at(5)
                    << _m_csLineSeparator;

        sRv.append(ssStackLine.str());
    }

    return sRv;
}
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

/* static */
bool
CxStackTrace::_bAddr2Line(
    const void     *a_pvSymbolAddress,
    std::tstring_t *a_psFilePath,
    std::tstring_t *a_psFunctionName,
    ulong_t        *a_pulSourceLine
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
             CxPath::sGetExe().c_str(), (ulong_t)a_pvSymbolAddress);

    FILE *pflFile = ::popen(szCmdLine, xT("r"));
    xSTD_VERIFY(NULL != pflFile);

    // get function name
    {
        tchar_t szBuff[1024 + 1] = {0};

        const tchar_t *pcszFunctionName = std::fgets(szBuff, xARRAY_SIZE(szBuff), pflFile);
        xSTD_VERIFY(NULL != pcszFunctionName);

        (*a_psFunctionName).assign(pcszFunctionName);
    }

    // get file and line
    {
        tchar_t szBuff[1024 + 1] = {0};

        const tchar_t *pcszFileAndLine = std::fgets(szBuff, xARRAY_SIZE(szBuff), pflFile);
        xSTD_VERIFY(NULL != pcszFileAndLine);

       /*
        * Parse that variants of pcszFileAndLine string:
        *   - /home/skynowa/Projects/xLib/Build/Tests/GCC_linux/Debug/../../../../Tests/Source/./Test.cpp:108
        *   - ??:0
        *
        */
        std::vec_tstring_t vsLine;

        CxString::vSplit(pcszFileAndLine, xT(":"), &vsLine);
        xSTD_VERIFY(2U == vsLine.size());

        // out
        xSTD_VERIFY(0 == std::feof(pflFile));

        *a_psFilePath    = vsLine.at(0);
        *a_pulSourceLine = CxString::string_cast<ulong_t>( vsLine.at(1) );
    }

    int iRv =::pclose(pflFile);    pflFile = NULL;
    xSTD_VERIFY(- 1 != iRv);

    return true;
}

#endif  // xOS_ENV_UNIX
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
