/**
 * \file   CxCommandLine.cpp
 * \brief
 */


#include <xLib/Common/CxCommandLine.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/ std::vector<std::tstring> CxCommandLine::_ms_vsArgs;
//--------------------------------------------------------------------------
LONG
CxCommandLine::liGetArgsMax() {
    LONG liRes = 0L;

#if xOS_ENV_WIN
    liRes = 32L * 1024L;
#elif xOS_ENV_UNIX
    liRes = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring::value_type);
    /*DEBUG*/xASSERT_RET(- 1 != liRes, 0L);
#endif

    return liRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxCommandLine::sGet() {
    /*DEBUG*/// n/a

    std::tstring sRes;

#if xOS_ENV_WIN
    LPCTSTR pcszRes = ::GetCommandLine();
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, std::tstring());

    sRes.assign( CxString::sTrimSpace(pcszRes) );
#elif xOS_ENV_UNIX
    sRes.assign( CxString::sJoin(_ms_vsArgs, CxConst::xSPACE) );
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCommandLine::bGetArgs(
    std::vector<std::tstring> *pvsArgs
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsArgs, false);

    xCHECK_DO(true == _ms_vsArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    (*pvsArgs).assign(_ms_vsArgs.begin(), _ms_vsArgs.end());

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCommandLine::bSetArgs(
    const int  ciArgsCount,
    tchar     *paszArgs[]
)
{
    /*DEBUG*/// n/a (because we'll have a recursion)

    std::vector<std::tstring> vsArgs;

    for (int i = 0; i < ciArgsCount; ++ i) {
        vsArgs.push_back(paszArgs[i]);
    }

    //out
    std::swap(_ms_vsArgs, vsArgs);

    xCHECK_DO(true == _ms_vsArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCommandLine::CxCommandLine() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxCommandLine::~CxCommandLine() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
