/**
 * \file   CxCommandLine.cpp
 * \brief  command line
 */


#include <xLib/Common/CxCommandLine.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/ std::vec_tstring_t CxCommandLine::_ms_vsArgs;
//--------------------------------------------------------------------------
long_t
CxCommandLine::liGetArgsMax() {
    long_t liRv = 0L;

#if xOS_ENV_WIN
    liRv = 32L * 1024L;
#elif xOS_ENV_UNIX
    liRv = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring_t::value_type);
    /*DEBUG*/xASSERT_RET(- 1 != liRv, 0L);
#endif

    return liRv;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxCommandLine::sGet() {
    /*DEBUG*/// n/a

    std::tstring_t sRv;

#if xOS_ENV_WIN
    LPCTSTR pcszRes = ::GetCommandLine();
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, std::tstring_t());

    sRv = CxString::sTrimSpace(pcszRes);
#elif xOS_ENV_UNIX
    sRv = CxString::sJoin(_ms_vsArgs, CxConst::xSPACE);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCommandLine::bGetArgs(
    std::vec_tstring_t *pvsArgs
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsArgs, false);

    xCHECK_DO(true == _ms_vsArgs.empty(),
              CxTracer::bWrite(xT("::: xLib: warning (command line is empty) :::")));

    (*pvsArgs) = _ms_vsArgs;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCommandLine::bSetArgs(
    const int  ciArgsCount,
    tchar_t   *paszArgs[]
)
{
    /*DEBUG*/// n/a (because we'll have a recursion)

    std::vec_tstring_t vsArgs;

    for (int i = 0; i < ciArgsCount; ++ i) {
        vsArgs.push_back(paszArgs[i]);
    }

    //out
    std::swap(_ms_vsArgs, vsArgs);

    xCHECK_DO(true == _ms_vsArgs.empty(), CxTracer::bWrite(xT("xLib: warning (command line is empty)")));

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
