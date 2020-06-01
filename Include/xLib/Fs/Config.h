/**
 * \file  Config.h
 * \brief config file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Config
    /// config file
{
public:
                      Config();
        ///< constructor, exe-file path
    explicit          Config(std::ctstring_t &filePath);
        ///< constructor, file path
    virtual          ~Config();
        ///< destructor

///@name Creations
///@{
    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< get file path
    void_t            setPath(std::ctstring_t &filePath);
        ///< set file path
    std::map_tstring_t & get() xWARN_UNUSED_RV;
        ///< get inner local_storage_t, may be used with bFlush

    void_t            read();
        ///< parse file
    void_t            save() const;
        ///< save
    void_t            saveDefault(std::cmap_tstring_t &content);
        ///< save default file
    void_t            clear();
        ///< clear content
    void_t            remove();
        ///< delete
///@}

///@name Key's actions
///@{
    bool_t            keyIsExists(std::ctstring_t &key) const xWARN_UNUSED_RV;
        ///< is exists
    void_t            keyClear(std::ctstring_t &key);
        ///< clear value
    void_t            keyDelete(std::ctstring_t &key);
        ///< delete key and value
///@}

///@name Get/set values
///@{
    template<typename T>
    T                 value(std::ctstring_t &key, const T defaultValue);
    template<typename T>
    void_t            setValue(std::ctstring_t &key, const T value);


#if 0
	std::tstring_t    value(std::ctstring_t &key, cptr_ctchar_t defaultValue)
						  xWARN_UNUSED_RV;
	void_t            setValue(std::ctstring_t &key, cptr_ctchar_t value);

	std::tstring_t    value(std::ctstring_t &key, std::ctstring_t &defaultValue)
						  xWARN_UNUSED_RV;
	void_t            setValue(std::ctstring_t &key, std::ctstring_t &value);

	long_t            value(std::ctstring_t &key, clong_t &defaultValue) xWARN_UNUSED_RV;
	void_t            setValue(std::ctstring_t &key, clong_t &value);

	double            value(std::ctstring_t &key, cdouble_t &defaultValue)
						  xWARN_UNUSED_RV;
	void_t            setValue(std::ctstring_t &key, cdouble_t &value);

	bool_t            value(std::ctstring_t &key, cbool_t &defaultValue) xWARN_UNUSED_RV;
	void_t            setValue(std::ctstring_t &key, cbool_t &value);

	std::ustring_t    value(std::ctstring_t &key, std::custring_t &defaultValue)
						  xWARN_UNUSED_RV;
	void_t            setValue(std::ctstring_t &key, std::custring_t &value);
#endif
///@}

private:
    std::ctstring_t    _separator;  ///< separator between key and value
    std::ctstring_t    _fileExt;    ///< file extension

    std::tstring_t     _filePath;   ///< file path to file
    std::map_tstring_t _config;     ///< std::map of keys and values

    xNO_COPY_ASSIGN(Config)
};
//-------------------------------------------------------------------------------------------------
template<typename T>
inline T
Config::value(std::ctstring_t &a_key, const T a_defaultValue)
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
		// hex string
		std::ctstring_t sRv = String::cast(_value, 16);

		return {sRv.begin(), sRv.end()};
    }
    else {
    	return String::cast<T>(_value);
    }
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
Config::setValue(std::ctstring_t &a_key, const T a_value)
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
		_value = String::cast( std::tstring_t(a_value.begin(), a_value.end()), 16);
	}
	else {
		Cout() << xTRACE_VAR(a_value);

	    _config[a_key] = a_value;
	}

	_config[a_key] = _value;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
