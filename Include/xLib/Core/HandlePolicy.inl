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
*    public - HandlePolicy Std
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
std::size_t
HandlePolicy<T, type>::_openMax_impl()
{
	if      constexpr (type == HandlePolicyType::hvNative ||
					   type == HandlePolicyType::hvNativeInvalid ||
					   type == HandlePolicyType::hvDll ||
					   type == HandlePolicyType::hvStdFile)
	{
		rlimit limit {};

		int_t iRv = ::getrlimit(RLIMIT_NOFILE, &limit);
		xTEST_EQ(iRv, 0);
		xTEST_GR(static_cast<std::size_t>(limit.rlim_cur), 0UL);

		return static_cast<std::size_t>( limit.rlim_cur );
	}
	else if constexpr (type == HandlePolicyType::hvMySqlConn) {
		// TODO: [skynowa] _openMax_impl

	   /**
		* show variables like "max_connections"
		*
	    * +-----------------+-------+
	    * | Variable_name   | Value |
	    * +-----------------+-------+
	    * | max_connections | 100   |
	    * +-----------------+-------+
	    *
	    * set global max_connections = 200;
	    */

	    return 0;
	}
	else if constexpr (type == HandlePolicyType::hvMySqlResult) {
		// TODO: [skynowa] _openMax_impl

	    return 0;
	}
	else if constexpr (type == HandlePolicyType::hvCurl) {
	    return static_cast<std::size_t>(CURLOPT_MAXCONNECTS);
	}
	else if constexpr (type == HandlePolicyType::hvFindDir) {
		// TODO: [skynowa] hvFindDir

	    return 0;
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
		// TODO: [skynowa] hvSocket

	    return 0;
	}
	else {
		/// static_assert(false);
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
T
HandlePolicy<T, type>::_clone_impl(const T a_handle)
{
	if      constexpr (type == HandlePolicyType::hvNative) {

	}
	else if constexpr (type == HandlePolicyType::hvNativeInvalid) {

	}
	else if constexpr (type == HandlePolicyType::hvDll) {

	}
	else if constexpr (type == HandlePolicyType::hvStdFile) {
	    int_t handleDup{};

	    int_t handle = ::fileno(a_handle);
	    xTEST_DIFF(handle, -1);

	    int_t iRv = ::dup2(handle, handleDup);
	    xTEST_DIFF(iRv, -1);

	    return static_cast<T>(xTFDOPEN(handleDup, xT("r+")));  // TODO: [skynowa] clone - open mode
	}
	else if constexpr (type == HandlePolicyType::hvMySqlConn) {
	    return a_handle;
	}
	else if constexpr (type == HandlePolicyType::hvMySqlResult) {
	    return a_handle;
	}
	else if constexpr (type == HandlePolicyType::hvCurl) {
	    return ::curl_easy_duphandle(a_handle);
	}
	else if constexpr (type == HandlePolicyType::hvFindDir) {
		// TODO: hvFindDir - impl
		return a_handle;
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
		// TODO: hvSocket - impl
		return a_handle;
	}
	else {
		/// static_assert(false);
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
bool_t
HandlePolicy<T, type>::_isValid_impl(const T a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
void_t
HandlePolicy<T, type>::_close_impl(T &a_handle)
{
	if      constexpr (type == HandlePolicyType::hvNative) {

	}
	else if constexpr (type == HandlePolicyType::hvNativeInvalid) {

	}
	else if constexpr (type == HandlePolicyType::hvDll) {

	}
	else if constexpr (type == HandlePolicyType::hvStdFile) {
	    int_t iRv = std::fclose(a_handle);
	    xTEST_DIFF(iRv, xTEOF);

	    a_handle = null();
	}
	else if constexpr (type == HandlePolicyType::hvMySqlConn) {
	    (void_t)::mysql_close(a_handle);

	    a_handle = null();
	}
	else if constexpr (type == HandlePolicyType::hvMySqlResult) {
	    (void_t)::mysql_free_result(a_handle);

	    a_handle = null();
	}
	else if constexpr (type == HandlePolicyType::hvCurl) {
	    (void_t)::curl_easy_cleanup(a_handle);

	    a_handle = null();
	}
	else if constexpr (type == HandlePolicyType::hvFindDir) {
		// TODO: hvFindDir - impl
		a_handle = null();
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
		// TODO: hvSocket - impl
		a_handle = null();
	}
	else {
		/// static_assert(false);
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
