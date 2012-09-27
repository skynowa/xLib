/**
 * \file  CxMacros.inl
 * \brief functions like macroses
 */


#include <xLib/Debug/xDebug.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class T>
/* static */ inline
void
CxMacros::ptrDeleteT(
    T * &a_pPtrT
)
{
    if (NULL != a_pPtrT) {
        delete a_pPtrT; a_pPtrT = NULL;
    }
}
//---------------------------------------------------------------------------
template<class T>
/* static */ inline
void
CxMacros::arrayDeleteT(
    T * &a_pPtrT
)
{
    if (NULL != a_pPtrT) {
        delete [] a_pPtrT;  a_pPtrT = NULL;
    }
}
//---------------------------------------------------------------------------
template<class T>
/* static */ inline
void
CxMacros::ptrAssignT(
    T *     &a_pPtrT, 
    const T &a_valueT
)
{
    if (NULL != a_pPtrT) { 
        *a_pPtrT = a_valueT;
    }
}
//---------------------------------------------------------------------------
template <typename ArrayT, const size_t cuiArraySize>
/* static */ inline
size_t
CxMacros::arraySizeT(
    const ArrayT (&)[cuiArraySize]
)
{
    return cuiArraySize;
}
//---------------------------------------------------------------------------
template <class T>
/* static */ inline
const T &
CxMacros::maxT(
    const T &a_cValue1T, 
    const T &a_cValue2T
)
{
    return (a_cValue1T > a_cValue2T) ? a_cValue1T : a_cValue2T;
}
//---------------------------------------------------------------------------
template <class T>
/* static */ inline
const T &
CxMacros::minT(
    const T &a_cValue1T, 
    const T &a_cValue2T
)
{
    return (a_cValue1T < a_cValue2T) ? a_cValue1T : a_cValue2T;
}
//---------------------------------------------------------------------------
template <class T>
/* static */ inline
void
CxMacros::swapT(
    T &a_value1T, 
    T &a_value2T
) 
{
    T temp = a_value1T;

    a_value1T = a_value2T;
    a_value2T = temp;
}
//---------------------------------------------------------------------------
//TODO: numericLimitsCheckT
template <class T>
/* static */ inline
bool
CxMacros::numericLimitsCheckT(
    const T &a_cValueT
)
{
    bool bRv = ((std::numeric_limits<T>::min)() <= a_cValueT) &&
               ((std::numeric_limits<T>::max)() >= a_cValueT);

    return bRv;
}
//---------------------------------------------------------------------------
template <class ToT, class FromT>
/* static */ inline
ToT
CxMacros::reinterpretCastT(
    const FromT &a_pPtrT
)
{
    void *pvVoidCast = static_cast<void *>( a_pPtrT );
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT(NULL != pvVoidCast);
#elif xOS_ENV_UNIX
    /*DEBUG*/// TODO: xASSERT(NULL != pvVoidCast);
#endif

    ToT ResT = static_cast<ToT>( pvVoidCast );

    return ResT;
}
//---------------------------------------------------------------------------
/* static */ inline
double
CxMacros::round(
    const double &a_cdValue
)
{
    return ::floor(a_cdValue + 0.5);
}
//---------------------------------------------------------------------------
template <class T1, class T2>
/* static */ inline
double
CxMacros::safeDivT(
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
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
