/**
 * \file  Utils.h
 * \brief functions like macros
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Utils
    /// help utils
{
public:
    template <class T>
    static
    inline void_t    ptrDeleteT(T * &ptr);
        ///< delete object by pointer

    template <class T>
    static
    inline void_t    arrayDeleteT(T * &ptr);
        ///< delete array by pointer

    template <class T>
    static
    inline void_t    ptrAssignT(T * &ptr, const T &value);
        ///< assign pointer

    template <class T, std::csize_t arraySize>
    static
    inline size_t    arraySizeT(const T (&)[arraySize]) xWARN_UNUSED_RV;
        ///< get array size

    static
    inline void_t    memoryZero(void_t *ptr, std::csize_t &sizeBytes);
        ///< zero memory

    template <class T, std::csize_t arraySize>
    static
    inline void_t    arrayZeroT(T (&arrayT)[arraySize]);
        ///< array zero

    template <class T>
    static
    inline void_t    structZeroT(T &object);
        ///< zero buffer memory

    template <class T>
    static
    inline void_t    bufferFreeT(T * &ptr);
        ///< free buffer memory

    static
    inline void_t    fileClose(FILE * &fileHandle);
        ///< close file stream (FILE *)

    template <class T>
    static
    inline bool_t    intToBoolT(const T &value) xWARN_UNUSED_RV;
        ///< convert int_t to bool_t

    template <class T>
    static
    inline const T & maxT(const T &value1 , const T &value2) xWARN_UNUSED_RV;
        ///< get max value

    template <class T>
    static
    inline const T & minT(const T &value1 , const T &value2) xWARN_UNUSED_RV;
        ///< get min value

    template <class T>
    static
    inline void_t    swapT(T &value1, T &value2);
        ///< swap variables

    template <class ToT, class FromT>
    static
    inline ToT       reinterpretCastT(const FromT &ptr) xWARN_UNUSED_RV;
        ///< allows any pointer to be converted into any other pointer type

    static
    inline bool_t    doubleIsEqual(const double &x, const double &y);
        ///< compare double values

    static
    inline double    roundDouble(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to the integer part

    template <class T>
    static
    inline T         roundIntT(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to long_t

    template <class T1, class T2>
    static
    inline double    safeDivT(const T1 &value1, const T2 &value2) xWARN_UNUSED_RV;
        ///< safe division

    // TODO: enumIncT - depreciated
    template <class T>
    static
    inline T         enumIncT(const T &value) xWARN_UNUSED_RV;
        ///< increment enumerator

    // TODO: enumIncT - depreciated
    template <class T>
    static
    inline T         enumDecT(const T &value) xWARN_UNUSED_RV;
        ///< decrement enumerator

private:
                     Utils();
        ///< constructor
                    ~Utils();
        ///< destructor

    xNO_COPY_ASSIGN(Utils)
};

template <class T>
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

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Utils.inl"
