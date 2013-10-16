/**
 * \file  CxLastError.cpp
 * \brief system last error
 */


#include <xLib/Debug/CxLastError.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

xNAMESPACE_ANONYM_BEGIN

#if xOS_ENV_WIN
    culong_t g_culCodeSuccess = ERROR_SUCCESS;
#else
    culong_t g_culCodeSuccess = 0;
#endif

xNAMESPACE_ANONYM_END

//------------------------------------------------------------------------------
/* static */
bool_t
CxLastError::isSuccess()
{
    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = (g_culCodeSuccess == ::GetLastError());
#else
    bRv = (g_culCodeSuccess == static_cast<ulong_t>( errno ));
#endif

    return bRv;
}
//------------------------------------------------------------------------------
/* static */
ulong_t
CxLastError::get()
{
    ulong_t ulCode = g_culCodeSuccess;

#if xOS_ENV_WIN
    ulCode = ::GetLastError();
#else
    ulCode = static_cast<ulong_t>( errno );
#endif

    reset();

    return ulCode;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxLastError::set(
    culong_t &a_code
)
{
#if xOS_ENV_WIN
    (void_t)::SetLastError(a_code);
#else
    errno = static_cast<int_t>( a_code );
#endif
}
//------------------------------------------------------------------------------
/* static */
void_t
CxLastError::reset()
{
    set(g_culCodeSuccess);
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxLastError::format()
{
    return format( get() );
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxLastError::format(
    culong_t &a_code
)
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%lu - "), a_code);

#if xOS_ENV_WIN
    DWORD  dwRv   = 0UL;
    LPVOID pvBuff = NULL;

    dwRv = ::FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    a_code,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    reinterpret_cast<LPTSTR>( &pvBuff ),
                    0UL,
                    NULL);

    xCHECK_RET(ERROR_MR_MID_NOT_FOUND == get(), sRv.append(xT("Unknown error")));
    xCHECK_RET(0UL                    == dwRv,  sRv.append(xT("[Cann't format error message]")));

    std::tstring_t sMessage;

    sMessage.assign( static_cast<LPCTSTR>( pvBuff ), dwRv );
    sMessage = CxString::removeEol(sMessage);
    sMessage = CxString::trimRightChars(sMessage, CxConst::xDOT);

    sRv.append(sMessage);

    (void_t)::LocalFree(pvBuff);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        char szBuff[64 + 1] = {0};

        ctchar_t *pcszError = ::strerror_r(static_cast<int_t>( a_code ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xOS_FREEBSD
        char szBuff[64 + 1] = {0};

        int_t iRv = ::strerror_r(static_cast<int_t>( a_code ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(- 1 == iRv, sRv.append(xT("[Cann't format error message]")));

        sRv.append(&szBuff[0]);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxLastError::CxLastError()
{
}
//------------------------------------------------------------------------------
/* virtual */
CxLastError::~CxLastError()
{
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
