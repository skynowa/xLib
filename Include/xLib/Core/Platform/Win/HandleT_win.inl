/**
 * \file  HandleT.inl
 * \brief handle
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>


xNAMESPACE_BEGIN2(xl, core)

//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
ulong_t
HandleT<T, valueT>::info() const
{
    xTEST_EQ(isValid(), true);

    DWORD flags = 0UL;

    BOOL blRes = ::GetHandleInformation(_handle, &flags);
    xTEST_DIFF(blRes, FALSE);
    xTEST_DIFF(flags, 0UL);

    return flags;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
void_t
HandleT<T, valueT>::setInfo(
    culong_t &a_mask,
    culong_t &a_flags
)
{
    xTEST_EQ(isValid(), true);
    xTEST_NA(a_mask);
    xTEST_NA(a_flags);

    BOOL blRes = ::SetHandleInformation(_handle, a_mask, a_flags);
    xTEST_DIFF(blRes, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
