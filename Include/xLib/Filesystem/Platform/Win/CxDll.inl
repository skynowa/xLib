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

#if xPLATFORM_IMPL
    _handle = ::LoadLibrary(a_dllPath.c_str());
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

#if xPLATFORM_IMPL
    proc_address_t paRv = ::GetProcAddress(_handle, xTS2S(a_procName).c_str());
    xCHECK_RET(paRv == xPTR_NULL, false);
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

#if xPLATFORM_IMPL
    paRv = ::GetProcAddress(_handle, xTS2S(a_procName).c_str());
    xTEST_PTR(paRv);
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

#if xPLATFORM_IMPL
    BOOL blRv = ::FreeLibrary(_handle);
    xTEST_DIFF(blRv, FALSE);
#endif

    _handle = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
