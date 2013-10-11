/**
 * \file   CxCommandLine.cpp
 * \brief  command line
 */


#include <xLib/Core/CxCommandLine.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//--------------------------------------------------------------------------
/* static */ std::vec_tstring_t CxCommandLine::_ms_vsArgs;
//--------------------------------------------------------------------------
long_t
CxCommandLine::argsMax() {
    long_t liRv = 0L;

#if xOS_ENV_WIN
    liRv = 32L * 1024L;
#else
    liRv = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring_t::value_type);
    xTEST_DIFF(- 1L, liRv);
#endif

    return liRv;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxCommandLine::get() {
    // n/a

    std::tstring_t sRv;

#if xOS_ENV_WIN
    LPCTSTR pcszRes = ::GetCommandLine();
    xTEST_PTR(pcszRes);

    sRv = CxString::trimSpace(pcszRes);
#else
    sRv = CxString::join(_ms_vsArgs, CxConst::xSPACE);
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxCommandLine::args(
    std::vec_tstring_t *a_pvsArgs
)
{
    xTEST_PTR(a_pvsArgs);

    xCHECK_DO(_ms_vsArgs.empty(),
        CxTracer() << xT("::: xLib: warning (command line is empty) :::"));

    *a_pvsArgs = _ms_vsArgs;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxCommandLine::setArgs(
    cint_t  &a_ciArgsCount,
    tchar_t *a_paszArgs[]
)
{
    // n/a (because we'll have a recursion)

    std::vec_tstring_t vsArgs;

    for (int_t i = 0; i < a_ciArgsCount; ++ i) {
        vsArgs.push_back(a_paszArgs[i]);
    }

    // out
    _ms_vsArgs.swap(vsArgs);

    xCHECK_DO(_ms_vsArgs.empty(),
        CxTracer::write(xT("xLib: warning (command line is empty)")));
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxCommandLine::CxCommandLine() {

}
//------------------------------------------------------------------------------
/* virtual */
CxCommandLine::~CxCommandLine() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
