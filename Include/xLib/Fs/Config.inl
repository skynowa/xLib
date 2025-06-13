/**
 * \file  Config.inl
 * \brief config file
 */


#include <xLib/Core/String.h>
#include <xLib/Log/LogStream.h>

namespace xl::fs
{

//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Config::value(
	std::ctstring_t &a_key,
	const T          a_defaultValue
)
{
    xTEST(!a_key.empty());
    xTEST_NA(a_defaultValue);

    const auto it = _config.find(a_key);
    if (it == _config.cend()) {
    	return a_defaultValue;
    }

    const auto &value = it->second;

    if      constexpr (std::is_same_v<T, bool_t>) {
    	return String::castBool(value);
    }
    else if constexpr (std::is_same_v<T, ctchar_t *>) {
    	return value.c_str();
    }
    else if constexpr (std::is_same_v<T, std::tstring_t>) {
    	return String::cast<T>(value);
    }
    else if constexpr (std::is_same_v<T, std::ustring_t>) {
		std::ctstring_t hex = String::cast(value, 16);

		return T{hex.cbegin(), hex.cend()};
    }
    else {
    	return String::cast<T>(value);
    }
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Config::setValue(
	std::ctstring_t &a_key,
	const T          a_value
)
{
    xTEST(!a_key.empty());
    xTEST_NA(a_value);

    std::tstring_t value;

	if      constexpr (std::is_integral_v<T>) {
		value = std::to_string(a_value);
	}
    else if constexpr (std::is_same_v<T, bool_t>) {
    	value = String::castBool(a_value);
    }
	else if constexpr (std::is_floating_point_v<T>) {
		value = std::to_string(a_value);
	}
	else if constexpr (std::is_same_v<T, ctchar_t *>) {
		value = a_value;
	}
	else if constexpr (std::is_same_v<T, std::tstring_t>) {
		value = a_value;
	}
	else if constexpr (std::is_same_v<T, std::ustring_t>) {
		value = String::cast( std::tstring_t(a_value.cbegin(), a_value.cend()), 16);
	}
	else {
		LogCout() << xTRACE_VAR(a_value);

		value = a_value;
	}

	// [out]
	_config[a_key] = value;
}
//-------------------------------------------------------------------------------------------------

} // namespace
