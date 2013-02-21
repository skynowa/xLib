/**
 * \file  CxUtils.inl
 * \brief functions like macros
 */


#include <xLib/Debug/xDebug.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void
CxUtils::ptrDeleteT(
    T * &a_pPtrT
)
{
    delete a_pPtrT; a_pPtrT = NULL;
}
//------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void
CxUtils::arrayDeleteT(
    T * &a_pPtrT
)
{
    delete [] a_pPtrT;  a_pPtrT = NULL;
}
//------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void
CxUtils::ptrAssignT(
    T *     &a_pPtrT,
    const T &a_valueT
)
{
    xCHECK_DO(NULL == a_pPtrT, return);

    *a_pPtrT = a_valueT;
}
//------------------------------------------------------------------------------
template <typename T, const size_t cuiArraySize>
/* static */ inline
size_t
CxUtils::arraySizeT(
    const T (&)[cuiArraySize]
)
{
    return cuiArraySize;
}
//------------------------------------------------------------------------------
/* static */ inline
void
CxUtils::memoryZero(
    void         *a_pPtr,
    const size_t &a_sizeBytes
)
{
    xCHECK_DO(NULL == a_pPtr, return);

    (void *)std::memset(a_pPtr, 0, a_sizeBytes);
}
//------------------------------------------------------------------------------
template<class T, const size_t cuiArraySize>
/* static */ inline
void
CxUtils::arrayZeroT(
    T (&a_arrayT)[cuiArraySize]
)
{
    (void)std::fill_n(&a_arrayT[0], cuiArraySize, T());
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
void
CxUtils::structZeroT(
    T &a_structT
)
{
    (void *)std::memset(&a_structT, 0, sizeof(a_structT));
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
void
CxUtils::bufferFreeT(
    T * &a_pPtrT
)
{
    xCHECK_DO(NULL == a_pPtrT, return);

    std::free(a_pPtrT);
    a_pPtrT = NULL;
}
//------------------------------------------------------------------------------
/* static */ inline
void
CxUtils::fileClose(
    FILE * &a_pFile
)
{
    xCHECK_DO(NULL == a_pFile, return);

    std::fclose(a_pFile);
    a_pFile = NULL;
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
bool
CxUtils::intToBoolT(
    const T &a_valueT
)
{
    return (0 == a_valueT) ? false : true;
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
const T &
CxUtils::maxT(
    const T &a_cValue1T,
    const T &a_cValue2T
)
{
    return (a_cValue1T > a_cValue2T) ? a_cValue1T : a_cValue2T;
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
const T &
CxUtils::minT(
    const T &a_cValue1T,
    const T &a_cValue2T
)
{
    return (a_cValue1T < a_cValue2T) ? a_cValue1T : a_cValue2T;
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
void
CxUtils::swapT(
    T &a_value1T,
    T &a_value2T
)
{
    T temp = a_value1T;

    a_value1T = a_value2T;
    a_value2T = temp;
}
//------------------------------------------------------------------------------
template <typename ToT, typename FromT>
/* static */ inline
ToT
CxUtils::reinterpretCastT(
    const FromT &a_pPtrT
)
{
    void *pvVoidCast = static_cast<void *>( a_pPtrT );
    ToT   ResT       = static_cast<ToT>( pvVoidCast );

    return ResT;
}
//------------------------------------------------------------------------------
/* static */ inline
double
CxUtils::roundDouble(
    const double &a_cdValue
)
{
    xTEST_NA(a_cdValue);

    double dRv = 0.0;

    if (a_cdValue > 0.0) {
        dRv = ::floor(a_cdValue + 0.5);
    } else {
        dRv = ::ceil(a_cdValue - 0.5);
    }

    return dRv;
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline
T
CxUtils::roundIntT(
    const double &a_cdValue
)
{
    assert(a_cdValue >= (std::numeric_limits<T>::min)() - 0.5);
    assert(a_cdValue <= (std::numeric_limits<T>::max)() + 0.5);

    T iRv = 0;

    if (a_cdValue > 0.0) {
        iRv = static_cast<T>( a_cdValue + 0.5 );
    } else {
        iRv = static_cast<T>( a_cdValue - 0.5 );
    }

    return iRv;
}
//------------------------------------------------------------------------------
template <typename T1, typename T2>
/* static */ inline
double
CxUtils::safeDivT(
    const T1 &a_cValue1T,
    const T2 &a_cValue2T
)
{
    double dRv = 0.0;

    if (static_cast<T2>( 0 ) == a_cValue2T) {
        dRv = 0.0;
    } else {
        dRv = static_cast<double>( a_cValue1T ) / static_cast<double>( a_cValue2T );
    }

    return dRv;
}
//------------------------------------------------------------------------------
template <typename T>
/* static */ inline T
CxUtils::enumIncT(
    const T &a_valueT
)
{
    return static_cast<T>( static_cast<long_t>( a_valueT ) + 1 );
}
//------------------------------------------------------------------------------
template <typename T>
/* static */  inline T
CxUtils::enumDecT(
    const T &a_valueT
)
{
    return static_cast<T>( static_cast<long_t>( a_valueT ) - 1 );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
