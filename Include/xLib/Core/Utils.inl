/**
 * \file  Utils.inl
 * \brief Utils functions
 */


#include <xLib/Debug/Debug.h>
#include <xLib/Test/Test.h>

#if xENV_UNIX
	#include <xLib/Fs/FileInfo.h>
	#include <xLib/Fs/Path.h>
#endif

namespace xl::core
{

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::ptrDeleteT(
    T * &a_ptr
)
{
    T* tmp {};
    std::swap(a_ptr, tmp);

    delete tmp; tmp = nullptr;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::arrayDeleteT(
    T * &a_ptr
)
{
    T* tmp {};
    std::swap(a_ptr, tmp);

    delete [] tmp; tmp = nullptr;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::ptrAssignT(
    T *     &a_ptr,
    const T &a_value
)
{
    xCHECK_DO(a_ptr == nullptr, return);

    *a_ptr = a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T, std::csize_t arraySize>
/* static */ inline
constexpr size_t
Utils::arraySizeT(
    const T (&)[arraySize]
)
{
    return arraySize;
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
void_t
Utils::memoryZero(
    void_t       *a_ptr,
    std::csize_t  a_sizeBytes
)
{
    xCHECK_DO(a_ptr == nullptr, return);

    void_t *pvRv = std::memset(a_ptr, 0, a_sizeBytes);
    xUNUSED(pvRv);
}
//-------------------------------------------------------------------------------------------------
template<typename T, std::csize_t arraySize>
/* static */ inline
void_t
Utils::arrayZeroT(
    T (&a_arrayT)[arraySize]
)
{
    (void_t)std::fill_n(&a_arrayT[0], arraySize, T{});
}
//-------------------------------------------------------------------------------------------------
template<typename T, typename F, typename N>
/* static */ inline
void_t
Utils::freeT(
    T * &a_ptr,
    F    a_func,
    N    a_null /* = nullptr */
)
{
    xCHECK_DO(a_ptr == a_null, return);

    a_func(a_ptr);
    a_ptr = a_null;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::bufferFreeT(
    T * &a_ptr
)
{
    freeT(a_ptr, ::free, nullptr);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
const T &
Utils::maxT(
    const T &a_value1,
    const T &a_value2
)
{
    return (a_value1 > a_value2) ? a_value1 : a_value2;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
const T &
Utils::minT(
    const T &a_value1,
    const T &a_value2
)
{
    return (a_value1 < a_value2) ? a_value1 : a_value2;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::swapT(
    T &a_value1,
    T &a_value2
)
{
    T temp = a_value1;

    a_value1 = a_value2;
    a_value2 = temp;
}
//-------------------------------------------------------------------------------------------------
template<typename ToT, class FromT>
/* static */ inline
ToT
Utils::reinterpretCastT(
    const FromT &a_ptr
)
{
    void_t *pvVoidCast = static_cast<void_t *>( a_ptr );
    ToT     ResT       = static_cast<ToT>( pvVoidCast );

    return ResT;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
T
Utils::roundIntT(
    cdouble_t a_value
)
{
    assert(a_value >= static_cast<cdouble_t>( (std::numeric_limits<T>::min)() ) - 0.5);
    assert(a_value <= static_cast<cdouble_t>( (std::numeric_limits<T>::max)() ) + 0.5);

    T iRv {};

    if (a_value > 0.0) {
        iRv = static_cast<T>( a_value + 0.5 );
    } else {
        iRv = static_cast<T>( a_value - 0.5 );
    }

    return iRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
T
Utils::intSafeDiv(
    const T &a_value1,
    const T &a_value2
)
{
	static_assert(std::is_integral<T>::value, "");

    if (a_value2 == 0) {
        return 0;
    }

    return a_value1 / a_value2;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline T
Utils::enumIncT(
    const T &a_value
)
{
    return static_cast<T>( static_cast<longlong_t>( a_value ) + 1 );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */  inline T
Utils::enumDecT(
    const T &a_value
)
{
    return static_cast<T>( static_cast<longlong_t>( a_value ) - 1 );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* Auto functions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class HandleT, class FunctorT, class DeleterT>
inline HandleT
makeUnique(FunctorT a_functor, DeleterT a_deleter)
{
	return HandleT(a_functor, a_deleter);
}
//-------------------------------------------------------------------------------------------------
inline file_unique_ptr_t
autoFile(
	std::ctstring_t &a_filePath,
	cptr_cchar       a_flags
)
{
	return makeUnique<file_unique_ptr_t>(std::fopen(xT2A(a_filePath).c_str(), a_flags), std::fclose);
}
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

inline dir_unique_ptr_t
autoDir(
	std::ctstring_t &a_dirPath
)
{
	return makeUnique<dir_unique_ptr_t>(::opendir(xT2A(a_dirPath).c_str()), ::closedir);
}
//-------------------------------------------------------------------------------------------------
inline dll_unique_ptr_t
autoDll(
	std::ctstring_t &a_dllPath,
	cint_t           a_flags
)
{
	return makeUnique<dll_unique_ptr_t>(::dlopen(xT2A(a_dllPath).c_str(), a_flags), ::dlclose);
}

#endif
//-------------------------------------------------------------------------------------------------

} // namespace
