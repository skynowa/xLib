/**
 * \file  Handle.inl
 * \brief handle
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>


namespace xl::core
{

/**************************************************************************************************
*    public - HandlePolicy<T, hvNativeInvalid>
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, HandlePolicyType::hvNativeInvalid>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, HandlePolicyType::hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandleDll
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, HandlePolicyType::hvDll>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, HandlePolicyType::hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvFindDir
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, HandlePolicyType::hvFindDir>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, HandlePolicyType::hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvSocket
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, HandlePolicyType::hvSocket>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, HandlePolicyType::hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------

} // namespace
