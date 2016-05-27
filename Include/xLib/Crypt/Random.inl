/**
 * \file  Random.cpp
 * \brief random generator
 */


xNAMESPACE_BEGIN2(xlib, crypt)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename RandomValue, class SeedPolicy>
Random<RandomValue, SeedPolicy>::Random() :
    _randMax( (std::numeric_limits<RandomValue>::max)() )
{
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValue, class SeedPolicy>
bool_t
Random<RandomValue, SeedPolicy>::nextBool()
{
    return (0 == (_policy.next() % 2));
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValue, class SeedPolicy>
template<typename T>
T
Random<RandomValue, SeedPolicy>::nextChar()
{
    clong_t min = (std::numeric_limits<T>::min)();
    clong_t max = (std::numeric_limits<T>::max)();

    return static_cast<T>( nextInt(min, max) );
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValue, class SeedPolicy>
template<typename T>
T
Random<RandomValue, SeedPolicy>::nextInt(
    const T &min,
    const T &max
)
{
    clong_t width = static_cast<long_t>(max - min) + 1;

    return static_cast<T>(_policy.next() % width) + min;
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValue, class SeedPolicy>
template<typename T>
T
Random<RandomValue, SeedPolicy>::nextFloat(
    const T &min,
    const T &max
)
{
    const T factor = (max - min) / static_cast<T>(_randMax);

    return static_cast<T>( _policy.next() ) * factor + min;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
