/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
 *         http://idlebox.net/
 */


#include <xLib/Debug/CxStackTrace.h>

#include <xLib/Sync/CxCurrentProcess.h>

#if defined(xOS_ENV_WIN)
    #ifdef xUNICODE
        #define DBGHELP_TRANSLATE_TCHAR
    #endif

    #include <DbgHelp.h>
    #pragma comment(lib, "DbgHelp.Lib")
#elif defined(xOS_ENV_UNIX)
    #include <execinfo.h>
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

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
    std::vector<std::string_t> *pvsStack
)
{
    std::vector<std::string_t> vsStack;

#if defined(xOS_ENV_WIN)
    void        *pvStack[_m_culMaxFrames] = {0};
    SYMBOL_INFO *psiSymbol                = NULL;
    HANDLE       hProcess                 = NULL;

    hProcess = CxCurrentProcess::hGetHandle();

    BOOL bRes = ::SymInitialize(hProcess, NULL, TRUE);
    xCHECK_RET(FALSE == bRes, FALSE);

    USHORT usFramesNum      = ::CaptureStackBackTrace(0UL, _m_culMaxFrames, pvStack, NULL);
    xCHECK_RET(usFramesNum == 0U, FALSE);

    psiSymbol               = new SYMBOL_INFO [ sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(char_t) ];
    psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    psiSymbol->MaxNameLen   = 255UL;

    for (USHORT i = 1U; i < usFramesNum; ++ i) {
        bRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);

        const ULONG64       ullAddress = psiSymbol->Address;
        const std::string_t csName     = std::string_t(psiSymbol->Name);

        //std::string_t sStackLine = CxString::sFormat(xT("%i: %s - 0x%0X"), usFramesNum - i - 1, psiSymbol->Name, psiSymbol->Address);
        std::string_t sStackLine = CxString::sFormat(xT("%u: %p    %s"), usFramesNum - i - 1U, ullAddress, csName.c_str());

        vsStack.push_back(sStackLine);
    }

    xARRAY_DELETE(psiSymbol);

    (void)::SymCleanup(hProcess);
#elif defined(xOS_ENV_UNIX)
    #if defined(xOS_LINUX)
        void *pvStack[_m_culMaxFrames] = {0};

        int iFramesNum  = backtrace(pvStack, _m_culMaxFrames);
        xCHECK_RET(iFramesNum <= 0, FALSE);

        char_t **ppszSymbols = backtrace_symbols(pvStack, iFramesNum);
        xCHECK_RET(NULL == ppszSymbols, FALSE);

        for (int i = 1; i < iFramesNum; ++ i) {
            std::string_t sStackLine;

            Dl_info dlinfo = {0};

            int iRes = dladdr(pvStack[i], &dlinfo);
            if (0 == iRes) {
                sStackLine = CxString::sFormat(xT("%u: %s"), iFramesNum - i - 1, ppszSymbols[i]);
            } else {
                const char_t *pcszSymName     = NULL;
                char_t       *pszDemangleName = NULL;
                int          iStatus         = - 1;

                pszDemangleName = abi::__cxa_demangle(dlinfo.dli_sname, NULL, NULL, &iStatus);
                if (NULL != pszDemangleName && 0 == iStatus) {
                    pcszSymName = pszDemangleName;
                } else {
                    pcszSymName = dlinfo.dli_sname;
                }

                sStackLine = CxString::sFormat(xT("%u: %s    %p    %s"), iFramesNum - i - 1, dlinfo.dli_fname, dlinfo.dli_fbase, pcszSymName);

                xBUFF_FREE(pszDemangleName);
            }

            vsStack.push_back(sStackLine);
        }
    #elif defined(xOS_FREEBSD)
        //TODO: CxStackTrace::bGet
    #endif
#endif

    std::reverse(vsStack.begin(), vsStack.end());

    std::swap(*pvsStack, vsStack);

    return TRUE;
}
//---------------------------------------------------------------------------
std::string_t
CxStackTrace::sGet(
    const std::string_t &csLinesSeparator /* = xT("\n") */
)
{
    std::string_t sRes;

    std::vector<std::string_t> vsStack;

    BOOL bRes = bGet(&vsStack);
    if (FALSE == bRes) {
        sRes.clear();
    } else {
        sRes = CxString::sJoin(vsStack, csLinesSeparator);
    }

    return sRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
