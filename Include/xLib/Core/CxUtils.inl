/**
 * \file  CxUtils.inl
 * \brief functions like macros
 */


#include <xLib/Debug/xDebug.h>
#include <xLib/Test/xTest.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
/* static */ inline
void_t
CxUtils::ptrDeleteT(
    T * &a_ptr
)
{
    delete a_ptr; a_ptr = NULL;
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */ inline
void_t
CxUtils::arrayDeleteT(
    T * &a_ptr
)
{
    delete [] a_ptr;  a_ptr = NULL;
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */ inline
void_t
CxUtils::ptrAssignT(
    T *     &a_ptr,
    const T &a_value
)
{
    xCHECK_DO(NULL == a_ptr, return);

    *a_ptr = a_value;
}
//-------------------------------------------------------------------------------------------------
template <class T, std::csize_t cuiArraySize>
/* static */ inline
size_t
CxUtils::arraySizeT(
    const T (&)[cuiArraySize]
)
{
    return cuiArraySize;
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
void_t
CxUtils::memoryZero(
    void_t       *a_ptr,
    std::csize_t &a_sizeBytes
)
{
    xCHECK_DO(NULL == a_ptr, return);

    void_t *pvRv = std::memset(a_ptr, 0, a_sizeBytes);
    xUNUSED(pvRv);
}
//-------------------------------------------------------------------------------------------------
template<class T, std::csize_t cuiArraySize>
/* static */ inline
void_t
CxUtils::arrayZeroT(
    T (&a_arrayT)[cuiArraySize]
)
{
    (void_t)std::fill_n(&a_arrayT[0], cuiArraySize, T());
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
void_t
CxUtils::structZeroT(
    T &a_object
)
{
    void_t *pvRv = std::memset(&a_object, 0, sizeof(a_object));
    xUNUSED(pvRv);
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
void_t
CxUtils::bufferFreeT(
    T * &a_ptr
)
{
    xCHECK_DO(NULL == a_ptr, return);

    std::free(a_ptr);
    a_ptr = NULL;
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
void_t
CxUtils::fileClose(
    FILE * &a_fileHandle
)
{
    xCHECK_DO(NULL == a_fileHandle, return);

    std::fclose(a_fileHandle);
    a_fileHandle = NULL;
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
bool_t
CxUtils::intToBoolT(
    const T &a_value
)
{
    return (0 == a_value) ? false : true;
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
const T &
CxUtils::maxT(
    const T &a_value1,
    const T &a_value2
)
{
    return (a_value1 > a_value2) ? a_value1 : a_value2;
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
const T &
CxUtils::minT(
    const T &a_value1,
    const T &a_value2
)
{
    return (a_value1 < a_value2) ? a_value1 : a_value2;
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
void_t
CxUtils::swapT(
    T &a_value1,
    T &a_value2
)
{
    T temp = a_value1;

    a_value1 = a_value2;
    a_value2 = temp;
}
//-------------------------------------------------------------------------------------------------
template <class ToT, class FromT>
/* static */ inline
ToT
CxUtils::reinterpretCastT(
    const FromT &a_ptr
)
{
    void_t *pvVoidCast = static_cast<void_t *>( a_ptr );
    ToT   ResT         = static_cast<ToT>( pvVoidCast );

    return ResT;
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
bool
CxUtils::doubleIsEqual(
    const double &x,
    const double &y
)
{
    const double epsilon = std::numeric_limits<double>::epsilon();

    return ::abs(x - y) <= epsilon * ::abs(x);
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
double
CxUtils::roundDouble(
    cdouble_t &a_value
)
{
    xTEST_NA(a_value);

    double dRv = 0.0;

    if (a_value > 0.0) {
        dRv = ::floor(a_value + 0.5);
    } else {
        dRv = ::ceil(a_value - 0.5);
    }

    return dRv;
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline
T
CxUtils::roundIntT(
    cdouble_t &a_value
)
{
    assert(a_value >= static_cast<cdouble_t>( (std::numeric_limits<T>::min)() ) - 0.5);
    assert(a_value <= static_cast<cdouble_t>( (std::numeric_limits<T>::max)() ) + 0.5);

    T iRv = 0;

    if (a_value > 0.0) {
        iRv = static_cast<T>( a_value + 0.5 );
    } else {
        iRv = static_cast<T>( a_value - 0.5 );
    }

    return iRv;
}
//-------------------------------------------------------------------------------------------------
template <class T1, class T2>
/* static */ inline
double
CxUtils::safeDivT(
    const T1 &a_value1,
    const T2 &a_value2
)
{
    double dRv = 0.0;

    if (static_cast<T2>( 0 ) == a_value2) {
        dRv = 0.0;
    } else {
        dRv = static_cast<double>( a_value1 ) / static_cast<double>( a_value2 );
    }

    return dRv;
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */ inline T
CxUtils::enumIncT(
    const T &a_value
)
{
    return static_cast<T>( static_cast<long_t>( a_value ) + 1 );
}
//-------------------------------------------------------------------------------------------------
template <class T>
/* static */  inline T
CxUtils::enumDecT(
    const T &a_value
)
{
    return static_cast<T>( static_cast<long_t>( a_value ) - 1 );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
