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
    size_t    arraySizeT(const T (&)[arraySize]) xWARN_UNUSED_RV;
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
    void_t    freeT(T * &ptr, F func, N null = xPTR_NULL);
        ///< free pointer
    template<typename T>
    static
    void_t    bufferFreeT(T * &ptr);
        ///< free buffer memory
    static
    void_t    fileClose(FILE * &fileHandle);
        ///< close file stream (FILE *)

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

    static
    bool_t    doubleIsEqual(const double &x, const double &y);
        ///< compare double values

    static
    double    roundDouble(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to the integer part

    template<typename T>
    static
    T         roundIntT(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to long_t

    template<typename T1, class T2>
    static
    double    safeDivT(const T1 &value1, const T2 &value2) xWARN_UNUSED_RV;
        ///< safe division

    // TODO: [skynowa] enumIncT - depreciated
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
                     Utils();
        ///< constructor
                    ~Utils();
        ///< destructor

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

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Utils.inl"
