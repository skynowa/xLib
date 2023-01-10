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
template<typename T, HandleType typeT>
void_t
Handle<T, valueT>::_setCloseOnExec_impl(
	cbool_t a_flag
)
{
	const DWORD flags = a_flag ? 0 : 1;

	BOOL blRv = setInfo(HANDLE_FLAG_INHERIT, flags);
	xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
ulong_t
Handle<T, valueT>::info() const
{
    xTEST(isValid());

    DWORD flags {};

    BOOL blRes = ::GetHandleInformation(_handle, &flags);
    xTEST_DIFF(blRes, FALSE);
    xTEST_DIFF(flags, 0UL);

    return flags;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
void_t
Handle<T, valueT>::setInfo(
    culong_t a_mask,
    culong_t a_flags
)
{
	xTEST(isValid());
    xTEST_NA(a_mask);
    xTEST_NA(a_flags);

    BOOL blRes = ::SetHandleInformation(_handle, a_mask, a_flags);
    xTEST_DIFF(blRes, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
