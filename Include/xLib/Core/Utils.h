/**
 * \file  Utils.h
 * \brief functions like macros
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Utils
    /// help utils
{
public:
    template<typename T>
    static
    void_t    ptrDeleteT(T * &ptr);
        ///< delete object by pointer

    template<typename T>
    static
    void_t    arrayDeleteT(T * &ptr);
        ///< delete array by pointer

    template<typename T>
    static
    void_t    ptrAssignT(T * &ptr, const T &value);
        ///< assign pointer

    template<typename T, std::csize_t arraySize>
    static
    constexpr size_t arraySizeT(const T (&)[arraySize]) xWARN_UNUSED_RV;
        ///< get array size

    static
    void_t    memoryZero(void_t *ptr, std::csize_t &sizeBytes);
        ///< zero memory

    template<typename T, std::csize_t arraySize>
    static
    void_t    arrayZeroT(T (&arrayT)[arraySize]);
        ///< array zero

    template<typename T>
    static
    void_t    structZeroT(T &object);
        ///< zero buffer memory

    template<typename T, typename F, typename N>
    static
    void_t    freeT(T * &ptr, F func, N null = nullptr);
        ///< free pointer
    template<typename T>
    static
    void_t    bufferFreeT(T * &ptr);
        ///< free buffer memory

    template<typename T>
    static
    const T & maxT(const T &value1 , const T &value2) xWARN_UNUSED_RV;
        ///< get max value

    template<typename T>
    static
    const T & minT(const T &value1 , const T &value2) xWARN_UNUSED_RV;
        ///< get min value

    template<typename T>
    static
    void_t    swapT(T &value1, T &value2);
        ///< swap variables

    template<typename ToT, class FromT>
    static
    ToT       reinterpretCastT(const FromT &ptr) xWARN_UNUSED_RV;
        ///< allows any pointer to be converted into any other pointer type

    template<typename T>
    static
    T         roundIntT(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to long_t

    template<typename T>
    static
    T         intSafeDiv(const T &value1, const T &value2) xWARN_UNUSED_RV;
        ///< safe division

    template<typename T>
    static
    T         enumIncT(const T &value) xWARN_UNUSED_RV;
        ///< increment enumerator

    // TODO: [skynowa] enumIncT - depreciated
    template<typename T>
    static
    T         enumDecT(const T &value) xWARN_UNUSED_RV;
        ///< decrement enumerator

private:
    xNO_INSTANCE(Utils)
    xNO_COPY_ASSIGN(Utils)
};

template<typename T>
class ConstCast
    ///< make constant variable
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
    const T &_value;
};

// TEST: implicitCast
template<typename To, typename From>
inline To
implicitCast(const From &a_from)
{
    return a_from;
}
	///< https://www.boost.org/doc/libs/1_64_0/boost/implicit_cast.hpp

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Utils.inl"
