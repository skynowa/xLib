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
    std::vector<std::string> *pvsStack
)
{
    std::vector<std::string> vsStack;

#if defined(xOS_ENV_WIN)
    VOID        *pvStack[_m_culMaxFrames] = {0};
    SYMBOL_INFO *psiSymbol                = NULL;
    HANDLE       hProcess                 = NULL;

    hProcess = ::GetCurrentProcess();

    BOOL bRes = ::SymInitialize(hProcess, NULL, TRUE);
    xCHECK_RET(FALSE == bRes, FALSE);

    USHORT usFramesNum      = ::CaptureStackBackTrace(0UL, _m_culMaxFrames, pvStack, NULL);
    xCHECK_RET(usFramesNum == 0U, FALSE);

    psiSymbol               = new SYMBOL_INFO [ sizeof( SYMBOL_INFO ) + (255UL + 1) * sizeof(TCHAR) ];
    psiSymbol->MaxNameLen   = 255UL;
    psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    for (USHORT i = 1U; i < usFramesNum; ++ i) {
        bRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);

        const ULONG64      ullAddress = psiSymbol->Address;
        const std::tstring csName     = std::tstring(psiSymbol->Name);

        //std::tstring sStackLine = CxString::sFormat(xT("%i: %s - 0x%0X"), usFramesNum - i - 1, psiSymbol->Name, psiSymbol->Address);
        std::tstring sStackLine = CxString::sFormat(xT("%u: %p\t%s"), usFramesNum - i - 1U, csName.c_str(), ullAddress);

        vsStack.push_back(sStackLine);
    }

    xARRAY_DELETE(psiSymbol);
#elif defined(xOS_ENV_UNIX)
    VOID *pvStack[_m_culMaxFrames] = {0};

    INT iFramesNum  = backtrace(pvStack, _m_culMaxFrames);
    xCHECK_RET(iFramesNum <= 0, FALSE);

    TCHAR **ppszSymbols = backtrace_symbols(pvStack, iFramesNum);
    xCHECK_RET(NULL == ppszSymbols, FALSE);

    for (INT i = 1; i < iFramesNum; ++ i) {
        std::tstring sStackLine;

        #if 1
            Dl_info dlinfo = {0};

            INT iRes = dladdr(pvStack[i], &dlinfo);
            if (0 == iRes) {
                sStackLine = CxString::sFormat(xT("%u: %s"), iFramesNum - i - 1, ppszSymbols[i]);
            } else {
                const TCHAR *pcszSymName     = NULL;
                TCHAR       *pszDemangleName = NULL;
                INT          iStatus         = - 1;

                pszDemangleName = abi::__cxa_demangle(dlinfo.dli_sname, NULL, NULL, &iStatus);
                if (NULL != pszDemangleName && 0 == iStatus) {
                    pcszSymName = pszDemangleName;
                } else {
                    pcszSymName = dlinfo.dli_sname;
                }

                sStackLine = CxString::sFormat(xT("%u: %p\t%s\t%s"), iFramesNum - i - 1, pvStack[i], dlinfo.dli_fname, pcszSymName);

                xBUFF_FREE(pszDemangleName);
            }
        #else
            sStackLine = CxString::sFormat(xT("%u: %p\t%s"), iFramesNum - i - 1, pvStack[i], ppszSymbols[i]);
        #endif

        vsStack.push_back(sStackLine);
    }
#endif

    std::reverse(vsStack.begin(), vsStack.end());

    std::swap(*pvsStack, vsStack);

    return TRUE;
}
//---------------------------------------------------------------------------
std::tstring
CxStackTrace::sGet(
    const std::tstring &csLinesSeparator /* = xT("\n") */
)
{
    std::tstring sRes;

    std::vector<std::string> vsStack;

    BOOL bRes = bGet(&vsStack);
    if (FALSE == bRes) {
        sRes.clear();
    } else {
        sRes = CxString::sJoin(vsStack, csLinesSeparator);
    }

    return sRes;
}
//---------------------------------------------------------------------------
