/**
 * \file  CxUtils.h
 * \brief functions like macros
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxUtils :
    private CxNonCopyable
    /// help macros
{
public:
    template <class T>
    static inline void_t    ptrDeleteT(T * &ptr);
        ///< delete object by pointer

    template <class T>
    static inline void_t    arrayDeleteT(T * &ptr);
        ///< delete array by pointer

    template <class T>
    static inline void_t    ptrAssignT(T * &ptr, const T &value);
        ///< assign pointer

    template <class T, std::csize_t cuiArraySize>
    static inline size_t    arraySizeT(const T (&)[cuiArraySize]) xWARN_UNUSED_RV;
        ///< get array size

    static inline void_t    memoryZero(void_t *ptr, std::csize_t &sizeBytes);
        ///< zero memory

    template <class T, std::csize_t cuiArraySize>
    static inline void_t    arrayZeroT(T (&arrayT)[cuiArraySize]);
        ///< array zero

    template <class T>
    static inline void_t    structZeroT(T &object);
        ///< zero buffer memory

    template <class T>
    static inline void_t    bufferFreeT(T * &ptr);
        ///< free buffer memory

    static inline void_t    fileClose(FILE * &fileHandle);
        ///< close file stream (FILE *)

    template <class T>
    static inline bool_t    intToBoolT(const T &value) xWARN_UNUSED_RV;
        ///< convert int_t to bool_t

    template <class T>
    static inline const T & maxT(const T &value1 , const T &value2) xWARN_UNUSED_RV;
        ///< get max value

    template <class T>
    static inline const T & minT(const T &value1 , const T &value2) xWARN_UNUSED_RV;
        ///< get min value

    template <class T>
    static inline void_t    swapT(T &value1, T &value2);
        ///< swap variables

    template <class ToT, class FromT>
    static inline ToT       reinterpretCastT(const FromT &ptr) xWARN_UNUSED_RV;
        ///< allows any pointer to be converted into any other pointer type

    static inline bool      doubleIsEqual(const double &x, const double &y);
        ///< compare double values

    static inline double    roundDouble(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to the integer part

    template <class T>
    static inline T         roundIntT(cdouble_t &value) xWARN_UNUSED_RV;
        ///< round double value to long_t

    template <class T1, class T2>
    static inline double    safeDivT(const T1 &value1, const T2 &value2) xWARN_UNUSED_RV;
        ///< safe division

    template <class T>
    static inline T         enumIncT(const T &value) xWARN_UNUSED_RV;
        ///< increment enumerator

    template <class T>
    static inline T         enumDecT(const T &value) xWARN_UNUSED_RV;
        ///< decrement enumerator

private:
                            CxUtils();
        ///< constructor
                           ~CxUtils();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include "CxUtils.inl"

#if xXLIB_HEADER_ONLY

#endif
