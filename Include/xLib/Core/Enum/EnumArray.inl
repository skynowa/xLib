/**
 * \file   EnumArray.inl
 * \brief  EnumArray
 */


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
inline
EnumArray<T, N>::EnumArray(
	const std::array<T, N> &a_values
) :
    std::array<T, N>(a_values)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
bool_t
EnumArray<T, N>::isValid(
	const ::ssize_t a_value
) const
{
	return std::find(this->begin(), this->end(), static_cast<T>(a_value)) != this->end();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)

//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
inline std::tostream_t &
operator << (
	std::tostream_t                          &a_os,
	const typename xl::core::EnumArray<T, N> &a_values
)
{
    /// a_os << "EnumArray (" << a_values.size() << "):\n";

	for (size_t i = 0; i < a_values.size(); ++ i) {
		const auto &it_value = a_values[i];

		/// a_os << xl::core::Enum::name(it_value);
		a_os << xl::core::Enum::value(it_value);

		if (i < (a_values.size() - 1)) {
			a_os << ",";
		}
	}

    return a_os;
}
//-------------------------------------------------------------------------------------------------