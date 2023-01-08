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
	#if   xENV_WIN
		cint_t iRv = _getmaxstdio();
		xTEST_GR(iRv, 0);

		return static_cast<std::size_t>(iRv);
	#elif xENV_UNIX
		rlimit limit {};

		int_t iRv = ::getrlimit(RLIMIT_NOFILE, &limit);
		xTEST_EQ(iRv, 0);
		xTEST_GR(static_cast<std::size_t>(limit.rlim_cur), 0UL);

		return static_cast<std::size_t>( limit.rlim_cur );
	#endif
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
		// TODO: [skynowa] hvMySqlResult
	    return 0;
	}
	else if constexpr (type == HandlePolicyType::hvCurl) {
	    return static_cast<std::size_t>(CURLOPT_MAXCONNECTS);
	}
	else if constexpr (type == HandlePolicyType::hvFindDir) {
	#if   xENV_WIN
		cint_t iRv = _getmaxstdio();
		xTEST_GR(iRv, 0);

		return static_cast<std::size_t>(iRv);
	#elif xENV_UNIX
		// TODO: [skynowa] hvFindDir
		return 0;
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
	#if   xENV_WIN
		cint_t iRv = _getmaxstdio();
		xTEST_GR(iRv, 0);

		return static_cast<std::size_t>(iRv);
	#elif xENV_UNIX
		// TODO: [skynowa] hvFindDir
		return 0;
	#endif
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
	#if   xENV_WIN
		T hRv = null();

		BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
			DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		xTEST_DIFF(blRes, FALSE);

		return hRv;
	#elif xENV_UNIX
		// TODO: [skynowa] hvNative
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvNativeInvalid) {
	#if   xENV_WIN
		T hRv = null();

		BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
			DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		xTEST_DIFF(blRes, FALSE);

		return hRv;
	#elif xENV_UNIX
		// TODO: [skynowa] hvNativeInvalid
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvDll) {
	#if   xENV_WIN
		// TODO: [skynowa] hvDll
		return a_handle;
	#elif xENV_UNIX
		// TODO: [skynowa] hvDll
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvStdFile) {
	    int_t handleDup{};

	    int_t handle = ::fileno(a_handle);
	    xTEST_DIFF(handle, -1);

	#if   xENV_WIN
		int_t iRv = ::_dup2(handle, handleDup);
		xTEST_DIFF(iRv, -1);
	#elif xENV_UNIX
		int_t iRv = ::dup2(handle, handleDup);
		xTEST_DIFF(iRv, -1);
	#endif

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
	#if   xENV_WIN
		// TODO: [skynowa] hvFindDir
		return a_handle;
	#elif xENV_UNIX
		// TODO: [skynowa] hvFindDir
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
	#if   xENV_WIN
		// TODO: [skynowa] hvSocket
		return a_handle;
	#elif xENV_UNIX
		// TODO: [skynowa] hvSocket
		return a_handle;
	#endif
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
#if xENV_WIN
	if constexpr (type == HandlePolicyType::hvNativeInvalid) {
		bool_t bRv {};

		// created but not initialised
		bool_t cond1 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xCDCDCDCD) ));
		// uninitialized locals in VC6 when you compile w/ /GZ
		bool_t cond2 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xCCCCCCCC) ));
		// indicate an uninitialized variable
		bool_t cond3 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xBAADF00D) ));
		// no man's land (normally outside of a process)
		bool_t cond4 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xFDFDFDFD) ));
		// freed memory set by NT's heap manager
		bool_t cond5 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xFEEEFEEE) ));
		// deleted
		bool_t cond6 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xDDDDDDDD) ));
		//
		bool_t cond7 = (a_handle != null());

		bRv = cond1 && cond2 && cond3 && cond4 && cond5 && cond6 && cond7;

		return bRv;
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
		return (a_handle >= 0);
	}
	else {
		/// TODO: _isValid_impl
		return (a_handle != null());
	}
#elif xENV_UNIX
	return (a_handle != null());
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
void_t
HandlePolicy<T, type>::_close_impl(T &a_handle)
{
	if      constexpr (type == HandlePolicyType::hvNative) {
	#if   xENV_WIN
		BOOL blRes = ::CloseHandle(a_handle);
		xTEST_DIFF(blRes, FALSE);

		a_handle = null();
	#elif xENV_UNIX
		// TODO: hvNative - impl
		a_handle = null();
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvNativeInvalid) {
	#if   xENV_WIN
		BOOL blRes = ::CloseHandle(a_handle);
		xTEST_DIFF(blRes, FALSE);

		a_handle = null();
	#elif xENV_UNIX
		// TODO: hvNativeInvalid - impl
		a_handle = null();
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvDll) {
	#if   xENV_WIN
		BOOL blRv = ::FreeLibrary(a_handle);
		xTEST_DIFF(blRv, FALSE);

		a_handle = null();
	#elif xENV_UNIX
		// TODO: hvDll - impl
		a_handle = null();
	#endif
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
	#if   xENV_WIN
		BOOL blRv = ::FindClose(a_handle);
		xTEST_DIFF(blRv, FALSE);

		a_handle = null();
	#elif xENV_UNIX
		// TODO: hvFindDir - impl
		a_handle = null();
	#endif
	}
	else if constexpr (type == HandlePolicyType::hvSocket) {
	#if   xENV_WIN
		int_t iRv = shutdown(a_handle, SD_BOTH);
		xTEST_DIFF(iRv, xSOCKET_ERROR);

		iRv = ::closesocket(a_handle);
		xTEST_DIFF(iRv, xSOCKET_ERROR);

		a_handle = null();
	#elif xENV_UNIX
		// TODO: hvSocket - impl
		a_handle = null();
	#endif
	}
	else {
		/// static_assert(false);
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
