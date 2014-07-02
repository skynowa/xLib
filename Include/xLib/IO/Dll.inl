/**
 * \file  Dll.inl
 * \brief dynamic linking loader
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/LastError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Dll_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/Dll_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/Dll_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/Dll_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
Dll::Dll() :
    _handle(xPTR_NULL)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
Dll::~Dll()
{
    _destruct();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Dll::isLoaded() const
{
    xTESTS_NA;

    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Dll::load(
    std::ctstring_t &a_dllPath
)
{
    xTESTS_NA;
    xTEST_EQ(a_dllPath.empty(), false);

    _destruct();

    _load_impl(a_dllPath);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Dll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    return _isProcExists_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------
inline Dll::proc_address_t
Dll::procAddress(
    std::ctstring_t &a_procName
) const
{
    return _procAddress_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
Dll::_destruct()
{
    xTESTS_NA;

    xCHECK_DO(!isLoaded(), return);

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
