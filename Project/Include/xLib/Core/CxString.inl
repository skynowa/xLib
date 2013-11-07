/**
 * \file  CxString.inl
 * \brief string utils
 */


#include <xLib/Core/xFunctors.h>
#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   casting
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value
)
{
    xTEST_NA(a_value);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << a_value;

        sRv = oss.str();
    } catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value,
    cint_t  &a_base
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
    } catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline T
CxString::cast(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    T ResT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> ResT;
    } catch (std::ctistringstream_t::failure &) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline T
CxString::cast(
    std::ctstring_t &a_str,
    cint_t          &a_base
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_base);

    T ResT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> std::setbase(a_base) >> ResT;
    } catch (std::ctistringstream_t::failure &) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::castA(
    std::cwstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::string asRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(asRv), SNarrow());

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::castW(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::wstring wsRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(wsRv), SWiden());

    return wsRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
