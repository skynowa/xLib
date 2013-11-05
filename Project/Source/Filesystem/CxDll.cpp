/**
 * \file  CxDll.cpp
 * \brief dynamic linking loader
 */


#include <xLib/Filesystem/CxDll.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>

#if xOS_ENV_WIN
    // lib: n/a
#else
    // lib: -ldl, -lc (FreeBSD)
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxDll::CxDll() :
    _dll(NULL)
{
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxDll::~CxDll()
{
    _destruct();
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDll::isLoaded() const
{
    xTESTS_NA;

    return (NULL != _dll);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDll::load(
    std::ctstring_t &a_dllPath
)
{
    xTESTS_NA;
    xTEST_EQ(false, a_dllPath.empty());

    _destruct();

#if xOS_ENV_WIN
    _dll = ::LoadLibrary(a_dllPath.c_str());
    xTEST_PTR(_dll);
#else
    _dll = ::dlopen(a_dllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_dll);
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_dll);

#if xOS_ENV_WIN
    proc_address_t fpRes = ::GetProcAddress(_dll, xTS2S(a_procName).c_str());
    xCHECK_RET(NULL == fpRes, false);
#else
    const char *error = NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    (void_t)::dlsym(_dll, a_procName.c_str());

    error = ::dlerror();
    xCHECK_RET(NULL != error, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO CxDll::proc_address_t
CxDll::procAddress(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_dll);

    proc_address_t fpRes = NULL;

#if xOS_ENV_WIN
    fpRes = ::GetProcAddress(_dll, xTS2S(a_procName).c_str());
    xTEST_PTR(fpRes);
#else
    const char *error = NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    fpRes = ::dlsym(_dll, a_procName.c_str());
    xTEST_NA(fpRes)

    error = ::dlerror();
    xTEST_PTR_FAIL(error);
#endif

    return fpRes;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDll::_destruct()
{
    xTESTS_NA;

    xCHECK_DO(!isLoaded(), return);

#if   xOS_ENV_WIN
    BOOL blRes = ::FreeLibrary(_dll);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::dlclose(_dll);
    xTEST_EQ(0, iRv);
#endif

    _dll = NULL;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
