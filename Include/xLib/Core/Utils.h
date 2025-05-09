/**
 * \file  Utils.h
 * \brief Utils functions
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class Utils
    /// help utils
{
public:
///\name ctors, dtor
///\{
	xNO_DEFAULT_CONSTRUCT(Utils);
	xNO_COPY_ASSIGN(Utils);
///\}

///\name Delete
///\{
	template<typename T>
	static void_t    ptrDeleteT(T * &ptr);
		///< delete object by pointer
	template<typename T>
	static void_t    arrayDeleteT(T * &ptr);
		///< delete array by pointer
///\}

///\name Etc
///\{
	template<typename T>
	static void_t    ptrAssignT(T * &ptr, const T &value);
		///< assign pointer
	template<typename T, std::csize_t arraySize>
	static constexpr size_t arraySizeT(const T (&)[arraySize]);
		///< get array size
///\}

///\name Zero
///\{
	static void_t    memoryZero(void_t *ptr, std::csize_t sizeBytes);
		///< zero memory
	template<typename T, std::csize_t arraySize>
	static void_t    arrayZeroT(T (&arrayT)[arraySize]);
		///< array zero
///\}

///\name Free
///\{
	template<typename T, typename F, typename N>
	static void_t    freeT(T * &ptr, F func, N null = nullptr);
		///< free pointer
	template<typename T>
	static void_t    bufferFreeT(T * &ptr);
        ///< free buffer memory
///\}

///\name Algos
///\{
	template<typename T>
	static const T & maxT(const T &value1 , const T &value2);
		///< get max value
	template<typename T>
	static const T & minT(const T &value1 , const T &value2);
		///< get min value
	template<typename T>
	static void_t    swapT(T &value1, T &value2);
		///< swap variables
///\}

///\name Cast
///\{
	template<typename ToT, typename FromT>
	static ToT       c_cast(const FromT &value);
		///< C-style cast
	template<typename ToT, class FromT>
	static ToT       reinterpretCastT(const FromT &ptr);
		///< allows any pointer to be converted into any other pointer type
	// TEST: implicitCast
	template<typename To, typename From>
	static To        implicitCast(const From &a_from);
		///< https://www.boost.org/doc/libs/1_64_0/boost/implicit_cast.hpp
///\}

///\name Math operations
///\{
	template<typename T>
	static T         roundIntT(cdouble_t value);
		///< round double value to long_t
	template<typename T>
	static T         intSafeDiv(const T &value1, const T &value2);
		///< safe division
///\}

///\name Enum
///\{
	template<typename T>
	static T         enumIncT(const T &value);
		///< increment enumerator
	// TODO: [skynowa] enumIncT - depreciated
	template<typename T>
	static T         enumDecT(const T &value);
		///< decrement enumerator
///\}
};
//-------------------------------------------------------------------------------------------------
template<typename T>
class ConstCast
    /// make constant variable
{
public:
    explicit ConstCast(const T &a_value) :
        _value(a_value)
    {
    }

    const T &
    get() const
    {
        return _value;
    }

private:
    const T _value;
};
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
* Auto functions
*
**************************************************************************************************/

///\name type aliases
///\{
//-------------------------------------------------------------------------------------------------
using file_unique_ptr_t = std::unique_ptr<std::FILE, int (*)(std::FILE *)>;

#if xENV_UNIX
using dll_unique_ptr_t  = std::unique_ptr<void,      int (*)(void *)>;
using dir_unique_ptr_t  = std::unique_ptr<::DIR,     int (*)(::DIR *)>;
using pipe_unique_ptr_t = std::unique_ptr<std::FILE, int (*)(std::FILE *)>;
#endif
//-------------------------------------------------------------------------------------------------
template<class HandleT, class FunctorT, class DeleterT>
HandleT makeUnique(FunctorT functor, DeleterT deleter);
//-------------------------------------------------------------------------------------------------
file_unique_ptr_t autoFile(std::ctstring_t &filePath, cptr_cchar_t flags);

#if xENV_UNIX
pipe_unique_ptr_t autoPipe(std::ctstring_t &cmdLine, cptr_cchar_t flags);
dll_unique_ptr_t  autoDll(std::ctstring_t &dllPath, cint_t flags);
dir_unique_ptr_t  autoDir(std::ctstring_t &dirPath);
#endif
///\}

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Utils.inl"

/**
 * TODO:
 *
 * - assert - rm
 * - Utils in xlib global ns
 */
