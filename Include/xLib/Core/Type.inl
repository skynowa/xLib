/**
 * \file  Type.inl
 * \brief type info
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>

#if xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN2(xlib, core)

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
Type::rawName(
    const T &a_objT
)
{
    std::tstring_t sRv;
    std::string    className;

    className.assign( typeid(a_objT).name() );
    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
Type::name(
    const T &a_objT
)
{
    std::tstring_t sRv;
    std::string    className;

#if xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status = - 1;

    char *realName = abi::__cxa_demangle(typeid(a_objT).name(), xPTR_NULL, xPTR_NULL, &status);
    className = (realName == xPTR_NULL) ? Const::strUnknownA() : realName;

    xBUFF_FREE(realName);
#else
    className.assign( typeid(a_objT).name() );

    // or use UnDecorateSymbolName
#endif

    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
bool_t
Type::isEquals(
    const T1 &a_obj1T,
    const T2 &a_obj2T
)
{
    return ( rawName(a_obj1T) == rawName(a_obj2T) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
