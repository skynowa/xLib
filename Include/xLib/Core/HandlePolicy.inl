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
	if      constexpr (type == HandlePolicyType::Native ||
					   type == HandlePolicyType::NativeInvalid ||
					   type == HandlePolicyType::Dll ||
					   type == HandlePolicyType::StdFile)
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
	else if constexpr (type == HandlePolicyType::MySqlConn) {
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
	else if constexpr (type == HandlePolicyType::MySqlResult) {
		// TODO: [skynowa] MySqlResult
	    return 0;
	}
	else if constexpr (type == HandlePolicyType::Curl) {
	    return static_cast<std::size_t>(CURLOPT_MAXCONNECTS);
	}
	else if constexpr (type == HandlePolicyType::FindDir) {
	#if   xENV_WIN
		cint_t iRv = _getmaxstdio();
		xTEST_GR(iRv, 0);

		return static_cast<std::size_t>(iRv);
	#elif xENV_UNIX
		// TODO: [skynowa] FindDir
		return 0;
	#endif
	}
	else if constexpr (type == HandlePolicyType::Socket) {
	#if   xENV_WIN
		cint_t iRv = _getmaxstdio();
		xTEST_GR(iRv, 0);

		return static_cast<std::size_t>(iRv);
	#elif xENV_UNIX
		// TODO: [skynowa] FindDir
		return 0;
	#endif
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
T
HandlePolicy<T, type>::_clone_impl(const T a_handle)
{
	if      constexpr (type == HandlePolicyType::Native) {
	#if   xENV_WIN
		T hRv = null();

		BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
			DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		xTEST_DIFF(blRes, FALSE);

		return hRv;
	#elif xENV_UNIX
		// TODO: [skynowa] Native
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::NativeInvalid) {
	#if   xENV_WIN
		T hRv = null();

		BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
			DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		xTEST_DIFF(blRes, FALSE);

		return hRv;
	#elif xENV_UNIX
		// TODO: [skynowa] NativeInvalid
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::Dll) {
	#if   xENV_WIN
		// TODO: [skynowa] Dll
		return a_handle;
	#elif xENV_UNIX
		// TODO: [skynowa] Dll
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::StdFile) {
	    int_t handleDup {};

	    int_t handle = ::fileno(a_handle);
	    xTEST_DIFF(handle, -1);

		int_t iRv = xDUP2(handle, handleDup);
		xTEST_DIFF(iRv, -1);

	    return static_cast<T>(xTFDOPEN(handleDup, xT("r+")));  // TODO: [skynowa] clone - open mode
	}
	else if constexpr (type == HandlePolicyType::MySqlConn) {
	    return a_handle;
	}
	else if constexpr (type == HandlePolicyType::MySqlResult) {
	    return a_handle;
	}
	else if constexpr (type == HandlePolicyType::Curl) {
	    return ::curl_easy_duphandle(a_handle);
	}
	else if constexpr (type == HandlePolicyType::FindDir) {
	#if   xENV_WIN
		// TODO: [skynowa] FindDir
		return a_handle;
	#elif xENV_UNIX
		// TODO: [skynowa] FindDir
		return a_handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::Socket) {
	#if   xENV_WIN
		// TODO: [skynowa] Socket
		return a_handle;
	#elif xENV_UNIX
		// TODO: [skynowa] Socket
		return a_handle;
	#endif
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
bool_t
HandlePolicy<T, type>::_isValid_impl(const T a_handle)
{
#if xENV_WIN
	if constexpr (type == HandlePolicyType::NativeInvalid) {
		// created but not initialised
		cbool_t cond1 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xCDCDCDCD) ));
		// uninitialized locals in VC6 when you compile w/ /GZ
		cbool_t cond2 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xCCCCCCCC) ));
		// indicate an uninitialized variable
		cbool_t cond3 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xBAADF00D) ));
		// no man's land (normally outside of a process)
		cbool_t cond4 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xFDFDFDFD) ));
		// freed memory set by NT's heap manager
		cbool_t cond5 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xFEEEFEEE) ));
		// deleted
		cbool_t cond6 = (a_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xDDDDDDDD) ));
		// compare with error handle value
		cbool_t cond7 = (a_handle != null());

		return (cond1 && cond2 && cond3 && cond4 && cond5 && cond6 && cond7);
	}
	else if constexpr (type == HandlePolicyType::Socket) {
		return (a_handle >= 0);
	}
	else {
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
	if      constexpr (type == HandlePolicyType::Native ||
					   type == HandlePolicyType::NativeInvalid)
	{
	#if   xENV_WIN
		BOOL blRes = ::CloseHandle(a_handle);
		xTEST_DIFF(blRes, FALSE);
	#elif xENV_UNIX
		int_t iRv = ::close(a_handle);
		xTEST_DIFF(iRv, -1);
	#endif
	}
	else if constexpr (type == HandlePolicyType::Dll) {
	#if   xENV_WIN
		BOOL blRv = ::FreeLibrary(a_handle);
		xTEST_DIFF(blRv, FALSE);
	#elif xENV_UNIX
		int_t iRv = ::dlclose(a_handle);
		xTEST_EQ(iRv, 0);
	#endif
	}
	else if constexpr (type == HandlePolicyType::StdFile) {
	    int_t iRv = std::fclose(a_handle);
	    xTEST_DIFF(iRv, xTEOF);
	}
	else if constexpr (type == HandlePolicyType::MySqlConn) {
	    (void_t)::mysql_close(a_handle);
	}
	else if constexpr (type == HandlePolicyType::MySqlResult) {
	    (void_t)::mysql_free_result(a_handle);
	}
	else if constexpr (type == HandlePolicyType::Curl) {
	    (void_t)::curl_easy_cleanup(a_handle);
	}
	else if constexpr (type == HandlePolicyType::FindDir) {
	#if   xENV_WIN
		BOOL blRv = ::FindClose(a_handle);
		xTEST_DIFF(blRv, FALSE);
	#elif xENV_UNIX
		int_t iRv = ::closedir(a_handle);
		xTEST_DIFF(iRv, -1);
	#endif
	}
	else if constexpr (type == HandlePolicyType::Socket) {
	#if   xENV_WIN
		int_t iRv = ::shutdown(a_handle, SD_BOTH);
		xTEST_DIFF(iRv, xSOCKET_ERROR);

		iRv = ::closesocket(a_handle);
		xTEST_DIFF(iRv, xSOCKET_ERROR);
	#elif xENV_UNIX
		int_t iRv = ::shutdown(a_handle, SHUT_RDWR);
		xTEST_DIFF(iRv, xSOCKET_ERROR);

		iRv = ::close(a_handle);
		xTEST_DIFF(iRv, xSOCKET_ERROR);
	#endif
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
