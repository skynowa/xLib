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
/*static*/ std::vector<std::string_t> CxCommandLine::_ms_vsArgs;
//--------------------------------------------------------------------------
LONG
CxCommandLine::liGetArgsMax() {
    LONG liRes = 0L;

#if xOS_ENV_WIN
    liRes = 32L * 1024L;
#elif xOS_ENV_UNIX
    liRes = ::sysconf(_SC_ARG_MAX) / sizeof(std::string_t::value_type);
    /*DEBUG*/xASSERT_RET(- 1 != liRes, 0L);
#endif

    return liRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxCommandLine::sGet() {
    /*DEBUG*/// n/a

    std::string_t sRes;

#if xOS_ENV_WIN
    LPCTSTR pcszRes = ::GetCommandLine();
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, std::string_t());

    sRes.assign( CxString::sTrimSpace(pcszRes) );
#elif xOS_ENV_UNIX
    sRes.assign( CxString::sJoin(_ms_vsArgs, CxConst::xSPACE) );
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxCommandLine::bGetArgs(
    std::vector<std::string_t> *pvsArgs
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsArgs, FALSE);

    xCHECK_DO(true == _ms_vsArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    (*pvsArgs).assign(_ms_vsArgs.begin(), _ms_vsArgs.end());

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxCommandLine::bSetArgs(
    const int  ciArgsCount,
    char_t     *paszArgs[]
)
{
    /*DEBUG*/// n/a (because we'll have a recursion)

    std::vector<std::string_t> vsArgs;

    for (int i = 0; i < ciArgsCount; ++ i) {
        vsArgs.push_back(paszArgs[i]);
    }

    //out
    std::swap(_ms_vsArgs, vsArgs);

    xCHECK_DO(true == _ms_vsArgs.empty(), CxDebugger::bTrace(xT("xLib: warning (command line is empty)")));

    return TRUE;
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
