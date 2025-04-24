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
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>


namespace xl::core
{

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
Handle<T, typeT>::Handle() :
    _handle( null() )
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
Handle<T, typeT>::Handle(
    const T &a_handle
) :
    _handle(a_handle)
{
    xTEST_NA(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
Handle<T, typeT>::Handle(
    const Handle &a_handle
) :
    _handle( null() )
{
    xTEST_NA(a_handle);

    _handle = a_handle.clone();
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
Handle<T, typeT>::~Handle()
{
    close();
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    operators
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
Handle<T, typeT> &
Handle<T, typeT>::operator = (
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    // Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_handle == a_handle, *this);

    /// TODO: [skynowa] disabled (for remove) - file wasn't close
    ///-- close();

    _handle = a_handle;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
Handle<T, typeT> &
Handle<T, typeT>::operator = (
    const Handle &a_handle
)
{
    xTEST_NA(a_handle);

    xCHECK_RET(this == &a_handle, *this);

    close();

    _handle = a_handle.clone();
    xTEST_NA(_handle);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
T
Handle<T, typeT>::get() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
void_t
Handle<T, typeT>::set(
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
T
Handle<T, typeT>::clone() const
{
    xCHECK_RET(!isValid(), null());

    // Impl
	{
		if      constexpr (typeT == HandleType::Native) {
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
		else if constexpr (typeT == HandleType::NativeInvalid) {
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
		else if constexpr (typeT == HandleType::Dll) {
		#if   xENV_WIN
			// TODO: [skynowa] Dll
			return _handle;
		#elif xENV_UNIX
			// TODO: [skynowa] Dll
			return _handle;
		#endif
		}
		else if constexpr (typeT == HandleType::StdFile) {
			int_t handle = ::fileno(_handle);
			xTEST_DIFF(handle, -1);

			int_t handleDup {};
			int_t iRv = xDUP2(handle, handleDup);
			xTEST_DIFF(iRv, -1);

			return static_cast<T>(xTFDOPEN(handleDup, xT("r+")));  // TODO: [skynowa] clone - open mode
		}
		else if constexpr (typeT == HandleType::MySqlConn) {
			return _handle;
		}
		else if constexpr (typeT == HandleType::MySqlResult) {
			return _handle;
		}
		else if constexpr (typeT == HandleType::Curl) {
			return ::curl_easy_duphandle(_handle);
		}
		else if constexpr (typeT == HandleType::FindDir) {
		#if   xENV_WIN
			// TODO: [skynowa] FindDir
			return _handle;
		#elif xENV_UNIX
			// TODO: [skynowa] FindDir
			return _handle;
		#endif
		}
		else if constexpr (typeT == HandleType::Socket) {
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
	} // Impl
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
bool_t
Handle<T, typeT>::isValid() const
{
#if xENV_WIN
	if constexpr (typeT == HandleType::NativeInvalid) {
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
	else if constexpr (typeT == HandleType::Socket) {
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
template<typename T, HandleType typeT>
void_t
Handle<T, typeT>::attach(
    const T &a_handle
)
{
    xTEST_NA(a_handle);
    xCHECK_DO(!isValid(), return);

    close();

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
T
Handle<T, typeT>::detach()
{
    T hRv = _handle;

    _handle = null();

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
void_t
Handle<T, typeT>::close()
{
    if ( !isValid() ) {
        _handle = null();
        return;
    }

    // Impl
    {
		if      constexpr (typeT == HandleType::Native ||
						   typeT == HandleType::NativeInvalid)
		{
		#if   xENV_WIN
			BOOL blRes = ::CloseHandle(_handle);
			xTEST_DIFF(blRes, FALSE);
		#elif xENV_UNIX
			int_t iRv = ::close(_handle);
			xTEST_DIFF(iRv, -1);
		#endif
		}
		else if constexpr (typeT == HandleType::Dll) {
		#if   xENV_WIN
			BOOL blRv = ::FreeLibrary(_handle);
			xTEST_DIFF(blRv, FALSE);
		#elif xENV_UNIX
			int_t iRv = ::dlclose(_handle);
			xTEST_EQ(iRv, 0);
		#endif
		}
		else if constexpr (typeT == HandleType::StdFile) {
			int_t iRv {};

			iRv = std::fflush(_handle);
			xTEST_DIFF(iRv, xTEOF);

			iRv = std::fclose(_handle);
			xTEST_DIFF(iRv, xTEOF);
		}
		else if constexpr (typeT == HandleType::MySqlConn) {
			(void_t)::mysql_close(_handle);
		}
		else if constexpr (typeT == HandleType::MySqlResult) {
			(void_t)::mysql_free_result(_handle);
		}
		else if constexpr (typeT == HandleType::Curl) {
			(void_t)::curl_easy_cleanup(_handle);
		}
		else if constexpr (typeT == HandleType::FindDir) {
		#if   xENV_WIN
			BOOL blRv = ::FindClose(_handle);
			xTEST_DIFF(blRv, FALSE);
		#elif xENV_UNIX
			int_t iRv = ::closedir(_handle);
			xTEST_DIFF(iRv, -1);
		#endif
		}
		else if constexpr (typeT == HandleType::Socket) {
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
    } // Impl

    _handle = null();
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
void_t
Handle<T, typeT>::setCloseOnExec(
	cbool_t a_flag
)
{
   /**
	* Dealing with Duplicate file Descriptors from Sub-Processes
	*
	* https://oroboro.com/file-handle-leaks-server/
	*
	* When you spawn subprocesses they inherit all the open file descriptors of the parent process
	* unless those descriptors have been specifically flagged as FD_CLOEXEC
	*
	* This is because the operating system doesn’t know which file descriptors will be used by the
	* subprocess for inter-process communication. Or if the subprocess will be the one that will
	* handle an open network socket.
	*
	* Normally when you spawn subprocesses the only file descriptors that need to stay open are
	* the pipes that are connected to STDIN, STDOUT, and STDERR of the child process. But every
	* subprocess is different.
	*
	* Right before your server calls fork() or exec(), call showFdInfo() to make sure that all file
	* descriptors are labeled FD_CLOEXEC except for the ones you need to be duplicated.
	*/

	_setCloseOnExec_impl(a_flag);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
/* static */
T
Handle<T, typeT>::null()
{
	if      constexpr (typeT == HandleType::Native) {
		return xNATIVE_HANDLE_NULL;
	}
	else if constexpr (typeT == HandleType::NativeInvalid) {
		return xNATIVE_HANDLE_INVALID;
	}
	else if constexpr (typeT == HandleType::Dll) {
		return nullptr;
	}
	else if constexpr (typeT == HandleType::StdFile) {
		return nullptr;
	}
	else if constexpr (typeT == HandleType::MySqlConn) {
		return nullptr;
	}
	else if constexpr (typeT == HandleType::MySqlResult) {
		return nullptr;
	}
	else if constexpr (typeT == HandleType::Curl) {
		return nullptr;
	}
	else if constexpr (typeT == HandleType::FindDir) {
		return xFIND_DIR_HANDLE_NULL;
	}
	else if constexpr (typeT == HandleType::Socket) {
		return xSOCKET_HANDLE_INVALID;
	}
	else {
		// n/a - as compile-time test
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
/* static */
std::size_t
Handle<T, typeT>::openMax()
{
	if constexpr (typeT == HandleType::Native ||
				  typeT == HandleType::NativeInvalid ||
				  typeT == HandleType::Dll ||
				  typeT == HandleType::StdFile)
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
	else if constexpr (typeT == HandleType::MySqlConn) {
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
	else if constexpr (typeT == HandleType::MySqlResult) {
		// TODO: [skynowa] MySqlResult
		return 0;
	}
	else if constexpr (typeT == HandleType::Curl) {
		return static_cast<std::size_t>(CURLOPT_MAXCONNECTS);
	}
	else if constexpr (typeT == HandleType::FindDir) {
	#if   xENV_WIN
		cint_t iRv = _getmaxstdio();
		xTEST_GR(iRv, 0);

		return static_cast<std::size_t>(iRv);
	#elif xENV_UNIX
		// TODO: [skynowa] FindDir
		return 0;
	#endif
	}
	else if constexpr (typeT == HandleType::Socket) {
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
