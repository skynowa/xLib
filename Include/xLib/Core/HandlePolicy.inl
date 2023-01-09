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

//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
HandlePolicy<T, type>::HandlePolicy(
	const T a_handle
) :
	_handle{a_handle}
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
T
HandlePolicy<T, type>::clone() const
{
	if      constexpr (type == HandlePolicyType::Native) {
	#if   xENV_WIN
		T hRv = null();

		BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &hRv,
			DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		xTEST_DIFF(blRes, FALSE);

		return hRv;
	#elif xENV_UNIX
		int_t handleDup {};
		int_t iRv = xDUP2(_handle, handleDup);
		xTEST_DIFF(iRv, -1);

		return handleDup;
	#endif
	}
	else if constexpr (type == HandlePolicyType::NativeInvalid) {
	#if   xENV_WIN
		T hRv = null();

		BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &hRv,
			DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		xTEST_DIFF(blRes, FALSE);

		return hRv;
	#elif xENV_UNIX
		int_t handleDup {};
		int_t iRv = xDUP2(_handle, handleDup);
		xTEST_DIFF(iRv, -1);

		return handleDup;
	#endif
	}
	else if constexpr (type == HandlePolicyType::Dll) {
	#if   xENV_WIN
		// TODO: [skynowa] Dll
		return _handle;
	#elif xENV_UNIX
		// TODO: [skynowa] Dll
		return _handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::StdFile) {
		int_t handle = ::fileno(_handle);
		xTEST_DIFF(handle, -1);

		int_t handleDup {};
		int_t iRv = xDUP2(handle, handleDup);
		xTEST_DIFF(iRv, -1);

		return static_cast<T>(xTFDOPEN(handleDup, xT("r+")));  // TODO: [skynowa] clone - open mode
	}
	else if constexpr (type == HandlePolicyType::MySqlConn) {
		return _handle;
	}
	else if constexpr (type == HandlePolicyType::MySqlResult) {
		return _handle;
	}
	else if constexpr (type == HandlePolicyType::Curl) {
		return ::curl_easy_duphandle(_handle);
	}
	else if constexpr (type == HandlePolicyType::FindDir) {
	#if   xENV_WIN
		// TODO: [skynowa] FindDir
		return _handle;
	#elif xENV_UNIX
		// TODO: [skynowa] FindDir
		return _handle;
	#endif
	}
	else if constexpr (type == HandlePolicyType::Socket) {
	#if   xENV_WIN
		// TODO: [skynowa] Socket
		return _handle;
	#elif xENV_UNIX
		// TODO: [skynowa] Socket
		return _handle;
	#endif
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
bool_t
HandlePolicy<T, type>::isValid() const
{
#if xENV_WIN
	if constexpr (type == HandlePolicyType::NativeInvalid) {
		// created but not initialised
		cbool_t cond1 = (_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xCDCDCDCD) ));
		// uninitialized locals in VC6 when you compile w/ /GZ
		cbool_t cond2 = (_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xCCCCCCCC) ));
		// indicate an uninitialized variable
		cbool_t cond3 = (_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xBAADF00D) ));
		// no man's land (normally outside of a process)
		cbool_t cond4 = (_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xFDFDFDFD) ));
		// freed memory set by NT's heap manager
		cbool_t cond5 = (_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xFEEEFEEE) ));
		// deleted
		cbool_t cond6 = (_handle != reinterpret_cast<T>( static_cast<intptr_t>(0xDDDDDDDD) ));
		// compare with error handle value
		cbool_t cond7 = (_handle != null());

		return (cond1 && cond2 && cond3 && cond4 && cond5 && cond6 && cond7);
	}
	else if constexpr (type == HandlePolicyType::Socket) {
		return (_handle >= 0);
	}
	else {
		return (_handle != null());
	}
#elif xENV_UNIX
	return (_handle != null());
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
void_t
HandlePolicy<T, type>::close() const
{
	if      constexpr (type == HandlePolicyType::Native ||
					   type == HandlePolicyType::NativeInvalid)
	{
	#if   xENV_WIN
		BOOL blRes = ::CloseHandle(_handle);
		xTEST_DIFF(blRes, FALSE);
	#elif xENV_UNIX
		int_t iRv = ::close(_handle);
		xTEST_DIFF(iRv, -1);
	#endif
	}
	else if constexpr (type == HandlePolicyType::Dll) {
	#if   xENV_WIN
		BOOL blRv = ::FreeLibrary(_handle);
		xTEST_DIFF(blRv, FALSE);
	#elif xENV_UNIX
		int_t iRv = ::dlclose(_handle);
		xTEST_EQ(iRv, 0);
	#endif
	}
	else if constexpr (type == HandlePolicyType::StdFile) {
		int_t iRv = std::fclose(_handle);
		xTEST_DIFF(iRv, xTEOF);
	}
	else if constexpr (type == HandlePolicyType::MySqlConn) {
		(void_t)::mysql_close(_handle);
	}
	else if constexpr (type == HandlePolicyType::MySqlResult) {
		(void_t)::mysql_free_result(_handle);
	}
	else if constexpr (type == HandlePolicyType::Curl) {
		(void_t)::curl_easy_cleanup(_handle);
	}
	else if constexpr (type == HandlePolicyType::FindDir) {
	#if   xENV_WIN
		BOOL blRv = ::FindClose(_handle);
		xTEST_DIFF(blRv, FALSE);
	#elif xENV_UNIX
		int_t iRv = ::closedir(_handle);
		xTEST_DIFF(iRv, -1);
	#endif
	}
	else if constexpr (type == HandlePolicyType::Socket) {
	#if   xENV_WIN
		int_t iRv = ::shutdown(_handle, SD_BOTH);
		xTEST_DIFF(iRv, xSOCKET_ERROR);

		iRv = ::closesocket(_handle);
		xTEST_DIFF(iRv, xSOCKET_ERROR);
	#elif xENV_UNIX
		int_t iRv = ::shutdown(_handle, SHUT_RDWR);
		xTEST_DIFF(iRv, xSOCKET_ERROR);

		iRv = ::close(_handle);
		xTEST_DIFF(iRv, xSOCKET_ERROR);
	#endif
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
T
HandlePolicy<T, type>::null()
{
	if      constexpr (type == HandlePolicyType::Native) {
		return xNATIVE_HANDLE_NULL;
	}
	else if constexpr (type == HandlePolicyType::NativeInvalid) {
		return xNATIVE_HANDLE_INVALID;
	}
	else if constexpr (type == HandlePolicyType::Dll) {
		return nullptr;
	}
	else if constexpr (type == HandlePolicyType::StdFile) {
		return nullptr;
	}
	else if constexpr (type == HandlePolicyType::MySqlConn) {
		return nullptr;
	}
	else if constexpr (type == HandlePolicyType::MySqlResult) {
		return nullptr;
	}
	else if constexpr (type == HandlePolicyType::Curl) {
		return nullptr;
	}
	else if constexpr (type == HandlePolicyType::FindDir) {
		return xFIND_DIR_HANDLE_NULL;
	}
	else if constexpr (type == HandlePolicyType::Socket) {
		return xSOCKET_HANDLE_INVALID;
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType type>
std::size_t
HandlePolicy<T, type>::openMax()
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

} // namespace
