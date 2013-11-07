/**
 * \file  CxType.inl
 * \brief type info
 */


#include <xLib/Core/CxUtils.h>

#if xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
/* static */
std::tstring_t
CxType::rawName(
    const T &a_objT
)
{
    xTEST_NA(a_objT);

    std::tstring_t sRv;
    std::string    className;

    className.assign( typeid(a_objT).name() );
    sRv = xS2TS(className);

    return sRv;
}
//------------------------------------------------------------------------------
template<class T>
/* static */
std::tstring_t
CxType::name(
    const T &a_objT
)
{
    xTEST_NA(a_objT);

    std::tstring_t sRv;
    std::string    className;

#if xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status = - 1;

    char *realName = abi::__cxa_demangle(typeid(a_objT).name(), NULL, NULL, &status);
    className = (NULL != realName) ? realName : CxConst::strUnknownA();

    xBUFF_FREE(realName);
#else
    className.assign( typeid(a_objT).name() );

    // or use UnDecorateSymbolName
#endif

    sRv = xS2TS(className);

    return sRv;
}
//------------------------------------------------------------------------------
template<class T1, class T2>
/* static */
bool_t
CxType::isEquals(
    const T1 &a_obj1T,
    const T2 &a_obj2T
)
{
    xTEST_NA(a_obj1T);
    xTEST_NA(a_obj2T);

    return ( rawName(a_obj1T) == rawName(a_obj2T) );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
