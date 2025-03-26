/**
 * \file  String.inl
 * \brief string utils
 */


#if 0
	#include <xLib/Test/Test.h>
	#include <xLib/Debug/Debug.h>
	#include <xLib/Debug/NativeError.h>
	#include <xLib/Debug/SourceInfo.h>
	#include <xLib/Debug/ErrorReport.h>
	#include <xLib/Debug/Debugger.h>
	#include <xLib/Debug/StackTrace.h>
#else
	#include <xLib/Test/TestMsg.h>
#endif


namespace xl::core
{

/***************************************************************************************************
*   casting
*
***************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
T
String::castTo(
    std::ctstring_t &a_value
)
{
    T rv {};

    try {
        // bool_t
        if      (std::is_same<T, bool_t>::value) {
            rv = static_cast<T>( std::stoul(a_value) );
        }

        // tchar_t
        else if (std::is_same<T, tchar_t>::value ||
                 std::is_same<T, uchar_t>::value)
        {
            if ( a_value.size() > 0) {
                rv = static_cast<T>(a_value[0]);
            }
        }

        // short_t
        else if (std::is_same<T, short_t>::value) {
            rv = static_cast<T>( std::stoi(a_value) );
        }
        else if (std::is_same<T, ushort_t>::value) {
            rv = static_cast<T>( std::stoul(a_value) );
        }

        // int_t
        else if (std::is_same<T, int_t>::value) {
            rv = static_cast<T>( std::stoi(a_value) );
        }
        else if (std::is_same<T, uint_t>::value) {
            rv = static_cast<T>( std::stoul(a_value) );
        }

        // long_t
        else if (std::is_same<T, long_t>::value) {
            rv = static_cast<T>( std::stol(a_value) );
        }
        else if (std::is_same<T, ulong_t>::value) {
            rv = static_cast<T>( std::stoul(a_value) );
        }

        // longlong_t
        else if (std::is_same<T, longlong_t>::value) {
            rv = static_cast<T>( std::stoll(a_value) );
        }
        else if (std::is_same<T, ulonglong_t>::value) {
            rv = static_cast<T>( std::stoull(a_value) );
        }

        // float_t
        else  if (std::is_same<T, float_t>::value) {
            rv = static_cast<T>( std::stof(a_value) );
        }
        else if (std::is_same<T, double_t>::value) {
            rv = static_cast<T>( std::stod(a_value) );
        }
        else if (std::is_same<T, longdouble_t>::value) {
            rv = static_cast<T>( std::stold(a_value) );
        }

        // enum
        else if (std::is_enum<T>::value) {
            rv = static_cast<T>( std::stoll(a_value) );
        }

        // other
        else {
            static_assert(true, "Unknown type");
            xTEST_FAIL_MSG(xT("Unknown type"));
        }
    }
    catch (const std::exception &a_exp) {
        xTEST_FAIL_MSG( std::tstring_t(a_exp.what()) );

        rv = {};
    }
    catch (...) {
        xTEST_FAIL_MSG(xT("Unknown exception"));

        rv = {};
    }

    return rv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
std::tstring_t
String::cast(
    const T &a_value    ///< source value
)
{
    xTEST_NA(a_value);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << a_value;

        sRv = oss.str();
    }
    catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    }
    catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
std::tstring_t
String::cast(
    const T &a_value,   ///< source value
    cint_t   a_base     ///< valid values: 8, 10, 16
)
{
    xTEST_NA(a_value);
    xTEST_NA(a_base);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << std::setbase(a_base) << std::uppercase << a_value;  // std::showbase

        sRv = oss.str();
    }
    catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    }
    catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
T
String::cast(
    std::ctstring_t &a_str  ///< source string
)
{
    xTEST_NA(a_str);

    T rvT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> rvT;
    }
    catch (std::ctistringstream_t::failure &) {
        return T();
    }
    catch (...) {
        return T();
    }

    return rvT;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<typename T>
T
String::cast(
    std::ctstring_t &a_str, ///< source string
    cint_t           a_base ///< valid values: 8, 10, 16
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_base);

    T rvT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> std::setbase(a_base) >> rvT;
    }
    catch (std::ctistringstream_t::failure &) {
        return T();
    }
    catch (...) {
        return T();
    }

    return rvT;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
void_t
String::split(
	std::ctstring_t &a_str,			///< string
	std::ctstring_t &a_sepLine,		///< separator line
	std::ctstring_t &a_sepKeyValue,	///< separator key value
	T               *a_map			///< [out] result
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sepLine);
    xTEST_NA(a_sepKeyValue);
    xTEST_NA(a_map);

    xCHECK_DO(a_map != nullptr, a_map->clear());

    xCHECK_DO(a_str.empty(), return);
    xCHECK_DO(a_sepLine.empty(), return);
    xCHECK_DO(a_sepKeyValue.empty(), return);
    xCHECK_DO(a_map == nullptr, return);

    std::vec_tstring_t lines;
    split(a_str, a_sepLine, &lines);

	for (const auto &it_line : lines) {
		xCHECK_DO(it_line.empty(), continue);

		std::csize_t pos = it_line.find(a_sepKeyValue);
		xCHECK_DO(pos == std::tstring_t::npos, continue);

		std::ctstring_t &key   = it_line.substr(0, pos);
		std::ctstring_t &value = it_line.substr(pos + a_sepKeyValue.size(), std::tstring_t::npos);

		// [out]
		a_map->insert( {key, value} );
	}
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
String::join(
	const T         &a_map,			///<
	std::ctstring_t &a_sepLine,		///<
	std::ctstring_t &a_sepKeyValue	///<
)
{
    xTEST_NA(a_map);
    xTEST_NA(a_sepLine);
    xTEST_NA(a_sepKeyValue);

    std::tstring_t sRv;

    for (const auto &[key, value] : a_map) {
        sRv += key + a_sepKeyValue + value + a_sepLine;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
