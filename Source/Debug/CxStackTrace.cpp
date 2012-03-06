/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
 *         http://idlebox.net/
 */


#include <xLib/Debug/CxStackTrace.h>

#include <xLib/Sync/CxCurrentProcess.h>

#if xOS_ENV_WIN
    #ifdef xUNICODE
        #define DBGHELP_TRANSLATE_TCHAR
    #endif

    #if !xCOMPILER_MINGW32
        #include <DbgHelp.h>
        #pragma comment(lib, "DbgHelp.Lib")
    #endif

#elif xOS_ENV_UNIX
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
#if xOS_FREEBSD

int backtrace( void **buffer, int max_frames )
{
    struct frame *fp;
    jmp_buf ctx;
    int i;
    /* get stack- and framepointer */
    setjmp(ctx);
    fp = (struct frame*)(((size_t*)(ctx))[FRAME_PTR_OFFSET]);
    for ( i=0; (i<FRAME_OFFSET) && (fp!=0); i++)
        fp = fp->fr_savfp;

    /* iterate through backtrace */
    for (i=0; fp && fp->fr_savpc && i<max_frames; i++)
    {
        /* store frame */
        *(buffer++) = (void *)fp->fr_savpc;
        /* next frame */
        fp=fp->fr_savfp;
    }

    return i;
}

#endif
//---------------------------------------------------------------------------
bool
CxStackTrace::bGet(
    std::vector<std::tstring_t> *pvsStack
)
{
    std::vector<std::tstring_t> vsStack;

#if xOS_ENV_WIN
    #if   xCOMPILER_MINGW32
        //TODO: CxStackTrace::bGet
    #elif xCOMPILER_MS
        void        *pvStack[_m_culMaxFrames] = {0};
        SYMBOL_INFO *psiSymbol                = NULL;
        HANDLE       hProcess                 = NULL;

        hProcess = CxCurrentProcess::hGetHandle();

        BOOL blRes = ::SymInitialize(hProcess, NULL, true);
        xCHECK_RET(FALSE == blRes, false);

        ushort_t usFramesNum = ::CaptureStackBackTrace(0UL, _m_culMaxFrames, pvStack, NULL);
        xCHECK_RET(usFramesNum == 0U, false);

        psiSymbol               = new SYMBOL_INFO [ sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t) ];
        psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        psiSymbol->MaxNameLen   = 255UL;

        for (ushort_t i = 1U; i < usFramesNum; ++ i) {
            std::tstring_t sStackLine;

            blRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);
            if (FALSE == blRes) {
                sStackLine = xUNKNOWN_STRING;
            } else {
                const ULONG64       ullAddress = psiSymbol->Address;
                const std::tstring_t csName    = std::tstring_t(psiSymbol->Name);

                //sStackLine = CxString::sFormat(xT("%i: %s - 0x%0X"), usFramesNum - i - 1, psiSymbol->Name, psiSymbol->Address);
                sStackLine = CxString::sFormat(xT("%u: %p    %s"), usFramesNum - i - 1U, ullAddress, csName.c_str());
            }

            vsStack.push_back(sStackLine);
        }

        xARRAY_DELETE(psiSymbol);

        (void)::SymCleanup(hProcess);
    #elif xCOMPILER_CODEGEAR
        //TODO: CxStackTrace::bGet
    #endif
#elif xOS_ENV_UNIX
    //--#if xOS_LINUX
        void *pvStack[_m_culMaxFrames] = {0};

        int iFramesNum  = ::backtrace(pvStack, _m_culMaxFrames);
        xCHECK_RET(iFramesNum <= 0, false);

        tchar_t **ppszSymbols = ::backtrace_symbols(pvStack, iFramesNum);
        xCHECK_RET(NULL == ppszSymbols, false);

        for (int i = 1; i < iFramesNum; ++ i) {
            std::tstring_t sStackLine;

            Dl_info dlinfo = {0};

            int iRes = ::dladdr(pvStack[i], &dlinfo);
            if (0 == iRes) {
                sStackLine = CxString::sFormat(xT("%u: %s"), iFramesNum - i - 1, ppszSymbols[i]);
            } else {
                const tchar_t *pcszSymName     = NULL;
                tchar_t       *pszDemangleName = NULL;
                int            iStatus         = - 1;

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
    //--#elif xOS_FREEBSD
        //TODO: CxStackTrace::bGet
    //--#endif
#endif

    std::reverse(vsStack.begin(), vsStack.end());

    std::swap(*pvsStack, vsStack);

    return true;
}
//---------------------------------------------------------------------------
std::tstring_t
CxStackTrace::sGet(
    const std::tstring_t &csLinesSeparator /* = xT("\n") */
)
{
    std::tstring_t sRes;

    std::vector<std::tstring_t> vsStack;

    bool bRes = bGet(&vsStack);
    if (false == bRes) {
        sRes.clear();
    } else {
        sRes = CxString::sJoin(vsStack, csLinesSeparator);
    }

    return sRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
