/**
 * \file  Random.cpp
 * \brief random generator
 */


xNAMESPACE_BEGIN2(xl, crypt)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
Random<RandomValueT, SeedPolicyT>::Random() :
    _randMax( (std::numeric_limits<RandomValueT>::max)() )
{
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
bool_t
Random<RandomValueT, SeedPolicyT>::nextBool()
{
    return (0 == (_policy.next() % 2));
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
template<typename T>
T
Random<RandomValueT, SeedPolicyT>::nextChar()
{
    clong_t min = (std::numeric_limits<T>::min)();
    clong_t max = (std::numeric_limits<T>::max)();

    return static_cast<T>( nextInt(min, max) );
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
template<typename T>
T
Random<RandomValueT, SeedPolicyT>::nextInt(
    const T &min,
    const T &max
)
{
    clong_t width = static_cast<long_t>(max - min) + 1;

    return static_cast<T>(_policy.next() % width) + min;
}
//-------------------------------------------------------------------------------------------------
template<typename RandomValueT, class SeedPolicyT>
template<typename T>
T
Random<RandomValueT, SeedPolicyT>::nextFloat(
    const T &min,
    const T &max
)
{
    const T factor = (max - min) / static_cast<T>(_randMax);

    return static_cast<T>( _policy.next() ) * factor + min;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, crypt)
