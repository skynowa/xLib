/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
 *         http://idlebox.net/
 */


#include <xLib/Debug/CxStackTrace.h>

#include <xLib/Sync/CxProcess.h>

#if defined(xOS_ENV_WIN)
    #include <DbgHelp.h>
    #pragma comment(lib, "DbgHelp.Lib")
#elif defined(xOS_ENV_UNIX)
    #include <execinfo.h>
    #include <cxxabi.h>
#endif


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*explicit*/
CxStackTrace::CxStackTrace() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxStackTrace::~CxStackTrace() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxStackTrace::bGet(
    std::vector<std::string> *pvsStack,
    const size_t              cuiMaxFrames
)
{
////#if defined(xOS_ENV_WIN)
////    const ULONG _culMaxFrames = 63UL;
////
////    if (cuiMaxFrames > _culMaxFrames) {
////        _m_uiMaxFrames = _culMaxFrames;
////    } else {
////        _m_uiMaxFrames = cuiMaxFrames;
////    }
////#elif defined(xOS_ENV_UNIX)
////    _m_uiMaxFrames = cuiMaxFrames;
////#endif


    std::vector<std::string> vsStack;

#if defined(xOS_ENV_WIN)
    ////const size_t cuiMaxFrames          = cuiMaxFrames;

    VOID        *pvStack[62/*cuiMaxFrames*/] = {0};
    SYMBOL_INFO *psiSymbol             = NULL;
    HANDLE       hProcess              = NULL;

    hProcess = ::GetCurrentProcess();

    BOOL bRes = ::SymInitialize(hProcess, NULL, TRUE);

    USHORT usFramesNum      = ::CaptureStackBackTrace(0UL, cuiMaxFrames, pvStack, NULL);
    psiSymbol               = new SYMBOL_INFO [ sizeof( SYMBOL_INFO ) + (255UL + 1) * sizeof(TCHAR) ];
    psiSymbol->MaxNameLen   = 255UL;
    psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    for (USHORT i = 0U; i < usFramesNum; ++ i) {
        bRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);

        const ULONG64      ullAddress = psiSymbol->Address;
        const std::tstring csName     = std::tstring(psiSymbol->Name);

        //std::tstring sStackLine = CxString::sFormat(xT("%i: %s - 0x%0X"), usFramesNum - i - 1, psiSymbol->Name, psiSymbol->Address);
        std::tstring sStackLine = CxString::sFormat(xT("%u: 0x%0X  %s"), usFramesNum - i - 1U, ullAddress, csName.c_str());

        vsStack.push_back(sStackLine);
    }

    xARRAY_DELETE(psiSymbol);    
#elif defined(xOS_ENV_UNIX)
    #if 1
        // storage array for stack trace address data
        void *ppvAddressList[cuiMaxFrames + 1];

        // retrieve current stack addresses
        int iAddressesSize = backtrace(ppvAddressList, sizeof(ppvAddressList) / sizeof(void *));
        if (0 == iAddressesSize) {
            std::tcerr << "  <empty, possibly corrupt>" << std::endl;

            return;
        }

        // resolve addresses into strings containing "filename(function+address)",
        // this array must be free()-ed
        char **ppSymbolList = backtrace_symbols(ppvAddressList, iAddressesSize);

        // allocate string which will be filled with the demangled function name
        size_t      uiFuncNameSize = 256;
        std::string sFuncName;

        sFuncName.resize(uiFuncNameSize);

        // iterate over the returned symbol lines. skip the first, it is the
        // address of this function.
        for (int i = 1; i < iAddressesSize; ++ i) {
            #if 1
                std::tstring sStackLine;

                char *pszNameBegin   = NULL;
                char *pszOffsetBegin = NULL;
                char *pszOffsetEnd   = NULL;

                // find parentheses and +address offset surrounding the mangled name:
                // ./module(function+0x15c) [0x8048a6d]
                for (char *p = ppSymbolList[i]; *p; ++ p) {
                    if      ('(' == *p) {
                        pszNameBegin = p;
                    }
                    else if ('+' == *p) {
                        pszOffsetBegin = p;
                    }
                    else if (')' == *p && pszOffsetBegin) {
                        pszOffsetEnd = p;

                        break;
                    }
                }

                if (pszNameBegin && pszOffsetBegin && pszOffsetEnd && pszNameBegin < pszOffsetBegin) {
                    *pszNameBegin   ++ = '\0';
                    *pszOffsetBegin ++ = '\0';
                    *pszOffsetEnd      = '\0';

                    // mangled name is now in [pszNameBegin, pszOffsetBegin) and caller
                    // offset in [pszOffsetBegin, pszOffsetEnd). now apply __cxa_demangle():
                    int   iStatus = - 1;
                    char *pszRes  = abi::__cxa_demangle(pszNameBegin, &sFuncName.at(0), &uiFuncNameSize, &iStatus);
                    if (0 == iStatus) {
                        sFuncName.assign(pszRes); // use possibly realloc()-ed string

                        sStackLine = CxString::sFormat("\t%s : %s +%s",   ppSymbolList[i], sFuncName.c_str(), pszOffsetBegin);
                    } else {
                        // demangling failed. Output function name as a C function with  no arguments.
                        sStackLine = CxString::sFormat("\t%s : %s() +%s", ppSymbolList[i], pszNameBegin,      pszOffsetBegin);
                    }
                } else {
                        // couldn't parse the line? print the whole line.
                        sStackLine = CxString::sFormat("\t%s",            ppSymbolList[i]);
                }

                vsStack.push_back(sStackLine);
            #else
                vsStack.push_back(ppSymbolList[i]);
            #endif
        }

        free(ppSymbolList); ppSymbolList = NULL;
    #else
        enum {
            MAX_DEPTH = 10
        };

        void *paszTrace[MAX_DEPTH];

        int trace_size = backtrace(paszTrace, MAX_DEPTH);

        printf("Call stack: \n");

        for (int i = 0; i < trace_size; ++ i) {\
            Dl_info dlinfo = {0};

            if (!dladdr(paszTrace[i], &dlinfo)) {
                continue;
            }

            const char *symname = dlinfo.dli_sname;

            int   status;
            char *demangled = abi::__cxa_demangle(symname, NULL, 0, &status);
            if (status == 0 && demangled) {
                symname = demangled;
            }

            printf("\tfile: %s, address: %llX, function: %s\n", dlinfo.dli_fname, (long long)dlinfo.dli_fbase, symname);

            if (demangled) {
                free(demangled);
            }
        }
    #endif
#endif

    std::reverse(vsStack.begin(), vsStack.end());

    std::swap(*pvsStack, vsStack);

    return TRUE;
}
//---------------------------------------------------------------------------
std::tstring 
CxStackTrace::sGet(
    const std::tstring &csSeparator /* = CxConst::xNL*/,
    const size_t        cuiMaxFrames
)
{
    std::tstring sRes;

    std::vector<std::string> vsStack;

    BOOL bRes = bGet(&vsStack, cuiMaxFrames);
    if (FALSE == bRes) {
        sRes.clear();
    } else {
        sRes = CxString::sJoin(vsStack, csSeparator);
    }

    return sRes;
}
//---------------------------------------------------------------------------