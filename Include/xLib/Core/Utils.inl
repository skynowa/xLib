/**
 * \file  Utils.inl
 * \brief functions like macros
 */


#include <xLib/Debug/Debug.h>
#include <xLib/Test/Test.h>


xNAMESPACE_BEGIN2(xl, core)

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::ptrDeleteT(
    T * &a_ptr
)
{
    T* tmp = xPTR_NULL;
    std::swap(a_ptr, tmp);

    delete tmp; tmp = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::arrayDeleteT(
    T * &a_ptr
)
{
    T* tmp = xPTR_NULL;
    std::swap(a_ptr, tmp);

    delete [] tmp; tmp = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::ptrAssignT(
    T *     &a_ptr,
    const T &a_value
)
{
    xCHECK_DO(a_ptr == xPTR_NULL, return);

    *a_ptr = a_value;
}
//-------------------------------------------------------------------------------------------------
template<typename T, std::csize_t arraySize>
/* static */ inline
size_t
Utils::arraySizeT(
    const T (&)[arraySize]
)
{
    return arraySize;
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
void_t
Utils::memoryZero(
    void_t       *a_ptr,
    std::csize_t &a_sizeBytes
)
{
    xCHECK_DO(a_ptr == xPTR_NULL, return);

    void_t *pvRv = std::memset(a_ptr, 0, a_sizeBytes);
    xUNUSED(pvRv);
}
//-------------------------------------------------------------------------------------------------
template<typename T, std::csize_t arraySize>
/* static */ inline
void_t
Utils::arrayZeroT(
    T (&a_arrayT)[arraySize]
)
{
    (void_t)std::fill_n(&a_arrayT[0], arraySize, T());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::structZeroT(
    T &a_object
)
{
    void_t *pvRv = std::memset(&a_object, 0, sizeof(a_object));
    xUNUSED(pvRv);
}
//-------------------------------------------------------------------------------------------------
template<typename T, typename F>
/* static */ inline
void_t
Utils::freeT(
    T * &a_ptr,
    F    a_func
)
{
    xCHECK_DO(a_ptr == xPTR_NULL, return);

    a_func(a_ptr);
    a_ptr = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::bufferFreeT(
    T * &a_ptr
)
{
    freeT(a_ptr, std::free);
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
void_t
Utils::fileClose(
    FILE * &a_fileHandle
)
{
    freeT(a_fileHandle, std::fclose);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
const T &
Utils::maxT(
    const T &a_value1,
    const T &a_value2
)
{
    return (a_value1 > a_value2) ? a_value1 : a_value2;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
const T &
Utils::minT(
    const T &a_value1,
    const T &a_value2
)
{
    return (a_value1 < a_value2) ? a_value1 : a_value2;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
void_t
Utils::swapT(
    T &a_value1,
    T &a_value2
)
{
    T temp = a_value1;

    a_value1 = a_value2;
    a_value2 = temp;
}
//-------------------------------------------------------------------------------------------------
template<typename ToT, class FromT>
/* static */ inline
ToT
Utils::reinterpretCastT(
    const FromT &a_ptr
)
{
    void_t *pvVoidCast = static_cast<void_t *>( a_ptr );
    ToT   ResT         = static_cast<ToT>( pvVoidCast );

    return ResT;
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
bool_t
Utils::doubleIsEqual(
    const double &x,
    const double &y
)
{
    cdouble_t epsilon = std::numeric_limits<double>::epsilon();

    return std::abs(x - y) <= (epsilon * std::abs(x));
}
//-------------------------------------------------------------------------------------------------
/* static */ inline
double
Utils::roundDouble(
    cdouble_t &a_value
)
{
    xTEST_NA(a_value);

    double dRv = 0.0;

    if (a_value > 0.0) {
        dRv = std::floor(a_value + 0.5);
    } else {
        dRv = std::ceil(a_value - 0.5);
    }

    return dRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */ inline
T
Utils::roundIntT(
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
template<typename T1, class T2>
/* static */ inline
double
Utils::safeDivT(
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
template<typename T>
/* static */ inline T
Utils::enumIncT(
    const T &a_value
)
{
    return static_cast<T>( static_cast<longlong_t>( a_value ) + 1 );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */  inline T
Utils::enumDecT(
    const T &a_value
)
{
    return static_cast<T>( static_cast<longlong_t>( a_value ) - 1 );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
