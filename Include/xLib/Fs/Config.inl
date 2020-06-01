/**
 * \file  Config.inl
 * \brief config file
 */


xNAMESPACE_BEGIN2(xl, fs)

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
    if (it == _config.end()) {
    	return a_defaultValue;
    }

    const auto &_value = it->second;

    if      constexpr (std::is_same_v<T, bool_t>) {
    	return String::castBool(_value);
    }
    else if constexpr (std::is_same_v<T, ctchar_t *>) {
    	return _value.c_str();
    }
    else if constexpr (std::is_same_v<T, std::tstring_t>) {
    	return String::cast<T>(_value);
    }
    else if constexpr (std::is_same_v<T, std::ustring_t>) {
		std::ctstring_t hex = String::cast(_value, 16);

		return T{hex.cbegin(), hex.cend()};
    }
    else {
    	return String::cast<T>(_value);
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

    std::tstring_t _value;

	if      constexpr (std::is_integral_v<T>) {
	    _value = std::to_string(a_value);
	}
    else if constexpr (std::is_same_v<T, bool_t>) {
    	_value = String::castBool(a_value);
    }
	else if constexpr (std::is_floating_point_v<T>) {
	    _value = std::to_string(a_value);
	}
	else if constexpr (std::is_same_v<T, ctchar_t *>) {
		_value = a_value;
	}
	else if constexpr (std::is_same_v<T, std::tstring_t>) {
		_value = a_value;
	}
	else if constexpr (std::is_same_v<T, std::ustring_t>) {
		_value = String::cast( std::tstring_t(a_value.cbegin(), a_value.cend()), 16);
	}
	else {
		Cout() << xTRACE_VAR(a_value);

	    _config[a_key] = a_value;
	}

	_config[a_key] = _value;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
