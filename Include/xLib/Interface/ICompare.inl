/**
 * \file  ICompare.inl
 * \brief
 */


namespace xl::interface
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
ICompare<T>::operator == (
	const T &a_value
) const
{
	return !compare(a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
ICompare<T>::operator != (
	const T &a_value
) const
{
	return compare(a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
ICompare<T>::operator < (
	const T &a_value
) const
{
	return compare(a_value) < 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
ICompare<T>::operator <= (
	const T &a_value
) const
{
	return compare(a_value) <= 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
ICompare<T>::operator > (
	const T &a_value
) const
{
	return compare(a_value) > 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
ICompare<T>::operator >= (
	const T &a_value
) const
{
	return compare(a_value) >= 0;
}
//-------------------------------------------------------------------------------------------------

} // namespace
