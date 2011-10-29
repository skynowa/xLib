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

void printStack( void ) {
     unsigned int   i;
     void         * stack[ 100 ];
     unsigned short frames;
     SYMBOL_INFO  * symbol;
     HANDLE         process;

     process = GetCurrentProcess();

     SymInitialize( process, NULL, TRUE );

     frames               = CaptureStackBackTrace( 0, 100, stack, NULL );
     symbol               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
     symbol->MaxNameLen   = 255;
     symbol->SizeOfStruct = sizeof( SYMBOL_INFO );

     for( i = 0; i < frames; i++ )  {
         SymFromAddr( process, ( DWORD64 )( stack[ i ] ), 0, symbol );

         printf( "%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address );
     }

     free( symbol );
}
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

    psiSymbol               = new SYMBOL_INFO[ sizeof( SYMBOL_INFO ) + (255UL + 1) * sizeof(TCHAR) ];
    memset(psiSymbol, 0, sizeof(* psiSymbol));

    psiSymbol->MaxNameLen   = 255UL;
    psiSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    
    for (USHORT i = 1U; i < usFramesNum; ++ i) {
        std::tstring sStackLine;

        bRes = ::SymFromAddr(hProcess, reinterpret_cast<DWORD64>( pvStack[i] ), NULL, psiSymbol);
        if (FALSE == bRes) {
            sStackLine = xT("[Unknown]");        
        } else {
        #if 0
            //TODO: I don't know, why this code not work, so it's temporary disable (maybe CxString::sFormat fail)
            sStackLine = CxString::sFormat(xT("%u: 0x%p    %s"), usFramesNum - i - 1U, psiSymbol->Address, psiSymbol->Name);
        #else
            sStackLine = CxString::sFormat(xT("%u: %s    0x%p"), usFramesNum - i - 1U, psiSymbol->Name, psiSymbol->Address);
        #endif
        }

        vsStack.push_back(sStackLine);
    }

    (VOID)::SymCleanup(hProcess);

    xARRAY_DELETE(psiSymbol);
#elif defined(xOS_ENV_UNIX)
    VOID *pvStack[_m_culMaxFrames] = {0};

    INT iFramesNum  = backtrace(pvStack, _m_culMaxFrames);
    xCHECK_RET(iFramesNum <= 0, FALSE);

    TCHAR **ppszSymbols = backtrace_symbols(pvStack, iFramesNum);
    xCHECK_RET(NULL == ppszSymbols, FALSE);

    for (INT i = 1; i < iFramesNum; ++ i) {
        std::tstring sStackLine;

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

            sStackLine = CxString::sFormat(xT("%u: %s    %p    %s"), iFramesNum - i - 1, dlinfo.dli_fname, dlinfo.dli_fbase, pcszSymName);

            xBUFF_FREE(pszDemangleName);
        }

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
