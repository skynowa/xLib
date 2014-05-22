/**
 * \file  CxDll.inl
 * \brief dynamic linking loader
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>

// lib: -ldl, -lc (FreeBSD)


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxDll::CxDll() :
    _handle(xPTR_NULL)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxDll::~CxDll()
{
    _destruct();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDll::isLoaded() const
{
    xTESTS_NA;

    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDll::load(
    std::ctstring_t &a_dllPath
)
{
    xTESTS_NA;
    xTEST_EQ(a_dllPath.empty(), false);

    _destruct();

#if 1
    _handle = ::dlopen(a_dllPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    xTEST_PTR(_handle);
#endif
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

#if 1
    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    (void_t)::dlsym(_handle, a_procName.c_str());

    error = ::dlerror();
    xCHECK_RET(error != xPTR_NULL, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline CxDll::proc_address_t
CxDll::procAddress(
    std::ctstring_t &a_procName
) const
{
    xTEST_PTR(_handle);

    proc_address_t paRv = xPTR_NULL;

#if 1
    const char *error = xPTR_NULL;

    error = ::dlerror();
    xTEST_PTR_FAIL(error);

    paRv = ::dlsym(_handle, a_procName.c_str());
    xTEST_NA(paRv)

    error = ::dlerror();
    xTEST_PTR_FAIL(error);
#endif

    return paRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxDll::_destruct()
{
    xTESTS_NA;

    xCHECK_DO(!isLoaded(), return);

#if 1
    int_t iRv = ::dlclose(_handle);
    xTEST_EQ(iRv, 0);
#endif

    _handle = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
