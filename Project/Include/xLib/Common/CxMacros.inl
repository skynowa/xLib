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
    T * &pPtrT
)
{
    if (NULL != pPtrT) {
        delete pPtrT; pPtrT = NULL;
    }
}
//---------------------------------------------------------------------------
template<class T>
/* static */ inline
void
CxMacros::arrayDeleteT(
    T * &pPtrT
)
{
    if (NULL != pPtrT) {
        delete [] pPtrT;  pPtrT = NULL;
    }
}
//---------------------------------------------------------------------------
template<class T>
/* static */ inline
void
CxMacros::ptrAssignT(
    T *     &pPtrT, 
    const T &valueT
)
{
    if (NULL != pPtrT) { 
        *pPtrT = valueT;
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
    const T &x, 
    const T &y
)
{
    return (x > y) ? x : y;
}
//---------------------------------------------------------------------------
template <class T>
/* static */ inline
const T &
CxMacros::minT(
    const T &x, 
    const T &y
)
{
    return (x < y) ? x : y;
}
//---------------------------------------------------------------------------
template <class T>
/* static */ inline
void
CxMacros::swapT(
    T &a, 
    T &b
) 
{
    T temp = a;
    a = b;
    b = temp;
}
//---------------------------------------------------------------------------
//TODO: numericLimitsCheckT
template <class T>
/* static */ inline
bool
CxMacros::numericLimitsCheckT(
    const T &x
)
{
    bool bRv = ((std::numeric_limits<T>::min)() <= x) &&
               ((std::numeric_limits<T>::max)() >= x);

    return bRv;
}
//---------------------------------------------------------------------------
template <class ToT, class FromT>
/* static */ inline
ToT
CxMacros::reinterpretCastT(
    const FromT &pPtrT
)
{
    void *pvVoidCast = static_cast<void *>( pPtrT );
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
    const double &cdValue
)
{
    return ::floor(cdValue + 0.5);
}
//---------------------------------------------------------------------------
template <class T1, class T2>
/* static */ inline
double
CxMacros::safeDivT(
    const T1 &cVal1T, 
    const T2 &cVal2T
)
{
    double dRv = 0.0;

    if (static_cast<T2>( 0 ) == cVal2T) {
        dRv = 0.0;
    } else {
        dRv = static_cast<double>( cVal1T ) / static_cast<double>( cVal2T );
    }

    return dRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
