/**
 * \file  CxUtils.inl
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
CxUtils::ptrDeleteT(
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
CxUtils::arrayDeleteT(
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
CxUtils::ptrAssignT(
    T *     &a_pPtrT,
    const T &a_valueT
)
{
    if (NULL != a_pPtrT) {
        *a_pPtrT = a_valueT;
    }
}
//---------------------------------------------------------------------------
template <typename T, const size_t cuiArraySize>
/* static */ inline
size_t
CxUtils::arraySizeT(
    const T (&)[cuiArraySize]
)
{
    return cuiArraySize;
}
//---------------------------------------------------------------------------
template <typename T, const size_t cuiArraySize>
/* static */ inline
void
CxUtils::bufferZeroT(
    T (&a_bufferT)[cuiArraySize]
)
{
    (void *)std::memset(&a_bufferT[0], 0, cuiArraySize);
}
//---------------------------------------------------------------------------
template <typename T>
/* static */ inline
void
CxUtils::structZeroT(
    T &a_structT
)
{
    (void *)std::memset(&a_structT, 0, sizeof(a_structT));
}
//---------------------------------------------------------------------------
template <typename T>
/* static */ inline
void
CxUtils::bufferFreeT(
    T * &a_pPtrT
)
{
    if (NULL != a_pPtrT) { 
        std::free(a_pPtrT); 
        a_pPtrT = NULL; 
    } 
}
//---------------------------------------------------------------------------
/* static */ inline
void
CxUtils::fileClose(
    FILE * &a_pFile
)
{
    if (NULL != a_pFile) { 
        std::fclose(a_pFile); 
        a_pFile = NULL; 
    }
}
//---------------------------------------------------------------------------
template <typename T>
/* static */ inline 
bool
CxUtils::intToBool(
    const T &a_valueT
)
{
    return ( (0 == a_valueT) ? false : true );
}
//---------------------------------------------------------------------------
template <class T>
/* static */ inline
const T &
CxUtils::maxT(
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
CxUtils::minT(
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
CxUtils::swapT(
    T &a_value1T,
    T &a_value2T
)
{
    T temp = a_value1T;

    a_value1T = a_value2T;
    a_value2T = temp;
}
//---------------------------------------------------------------------------
template <class ToT, class FromT>
/* static */ inline
ToT
CxUtils::reinterpretCastT(
    const FromT &a_pPtrT
)
{
    void *pvVoidCast = static_cast<void *>( a_pPtrT );
#if   xOS_ENV_WIN
    /*DEBUG*/// xASSERT(NULL != pvVoidCast);
#elif xOS_ENV_UNIX
    /*DEBUG*/// TODO: xASSERT(NULL != pvVoidCast);
#endif

    ToT ResT = static_cast<ToT>( pvVoidCast );

    return ResT;
}
//---------------------------------------------------------------------------
/* static */ inline
double
CxUtils::round(
    const double &a_cdValue
)
{
    return ::floor(a_cdValue + 0.5);
}
//---------------------------------------------------------------------------
template <class T1, class T2>
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
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
