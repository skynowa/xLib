/**
 * \file  String.inl
 * \brief string utils
 */


xNAMESPACE_BEGIN2(xlib, core)

/*******************************************************************************
*   casting
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
xINLINE std::tstring_t
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
template<class T>
xINLINE std::tstring_t
String::cast(
    const T &a_value,   ///< source value
    cint_t  &a_base     ///< valid values: 8, 10, 16
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
template<class T>
xINLINE T
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
template<class T>
xINLINE T
String::cast(
    std::ctstring_t &a_str, ///< source string
    cint_t          &a_base ///< valid values: 8, 10, 16
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

xNAMESPACE_END2(xlib, core)
